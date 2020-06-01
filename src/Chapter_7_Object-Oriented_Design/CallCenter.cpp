#include <iostream>
#include <vector>
#include <memory>
#include <ctime>
#include <cstdlib>
#include <array>
#include <thread>

enum JobTitle {
    Respondent = 0, Manager = 1, Director = 2
};

class CallHandler;
class Call;

class Employee {
    public:
        int id;
        Employee() = default;
        Employee(JobTitle t, int i, std::shared_ptr<CallHandler> h) : job_title(t), id(i), handler(h) { }
        JobTitle job_title;
        std::shared_ptr<Call> current_call;
        std::shared_ptr<CallHandler> handler;
        bool is_free();
        void start_call(Call&);
        void finish_call();
        bool receive_call(std::shared_ptr<Call>&);
        bool receive_call(Call&);
        void escalate_and_reassign();
};

class Caller {
    public:
        Caller(int cl) : challenging_level(cl) {}
        // normal caller = 0, not so easy going caller = 1, hard caller = 2
        int challenging_level;
};

time_t call_end_time() {
    std::time_t now = time(0); // current date/time based on current system
    char* dt = ctime(&now);
    srand(time(NULL));
    std::time_t end_time = now + rand() % 10; // increase random num of seconds in range [0, 10]
    return end_time;
}

class Call : public std::enable_shared_from_this<Call> {
    public:
        Call(Caller c) : caller(c), title(JobTitle::Respondent){}
        Caller caller;
        Employee handler;
        void set_handler(Employee& e) {
            handler = e;
            e.receive_call(*this);
        }
        void reply(std::string m) {
        }
        JobTitle get_title() {
            return title;
        }
        void set_title(JobTitle t) {
            title = t;
        }
        void increment_title() {
            title = JobTitle(title + 1);
        }
        void disconnect() {
            
        }
    private:
        JobTitle title; // target_title
};

bool Employee::is_free() {
    return current_call == nullptr;
}

std::string str_title(const JobTitle& jt) {
    std::string title;
    switch (jt)
    {
    case JobTitle::Respondent:
        title = "respondent";
        break;
    case JobTitle::Manager:
        title = "manager";
        break;
    case JobTitle::Director:
        title = "director";
        break;
    default:
        break;
    }
    return title;
}

void Employee::start_call(Call& call) {
    std::string title = str_title(call.get_title());
    std::cout << "Started call with " << title << '\n';
    if(call.caller.challenging_level != job_title) {
        std::cout << "Call redirected.\n";
    } else {
        time_t end_call = call_end_time();
        while(time(0) < end_call) {
            std::cout << "Employee with id " << call.handler.id << " is talking.\n";
        }
    }
}
void Employee::finish_call() {
    std::cout << "Finished call with ";
    current_call = nullptr;
}
bool Employee::receive_call(std::shared_ptr<Call>& call) {
    current_call = call;
    return is_free();  
}
bool Employee::receive_call(Call& call) {
    current_call = std::make_shared<Call>(call);
    return is_free();  
}

class Respondent : Employee {
    Respondent() {
        job_title = JobTitle::Respondent;
    }
};

class Manager : Employee {
    Manager() {
        job_title = JobTitle::Manager;
    }
};

class Director : Employee {
    Director() {
        job_title = JobTitle::Director;
    }
};

std::vector<Employee> get_employees(const int, const int, const int, std::shared_ptr<CallHandler>&);

class CallHandler : public std::enable_shared_from_this<CallHandler> {
    public:
        void initialize_employees() {
            std::shared_ptr<CallHandler> this_ptr = shared_from_this();
            employees = get_employees(num_of_repondents, num_of_managers, num_of_directors, this_ptr);
        }

        static constexpr auto num_of_repondents = 10;
        static constexpr auto num_of_managers = 4;
        static constexpr auto num_of_directors = 2;
        static constexpr auto levels = 3;
        std::vector<Employee> employees;
        std::array<std::vector<Call>, levels> call_queues;

        bool get_handler_for_call(std::shared_ptr<Call>& call) {
            for(Employee& em : employees) {
                if(em.is_free()) {
                    call -> set_handler(em);
                    return true;
                }
            }
            return false;
        }    

        bool get_handler_for_call(Call& call) {
            for(Employee& em : employees) {
                if(em.is_free() && em.job_title == call.get_title()) {
                    call.set_handler(em);
                    std::cout << "Handler id = " << call.handler.id << '\n';
                    em.receive_call(call);
                    em.start_call(call);
                    return true;
                }
            }
            std::cout << "There is no available handler.\n";
            return false;
        }  

        // routes the call to an available employee, or saves in a queue if no employee is available
        void dispatch_call(std::shared_ptr<Call> call) {
            if(get_handler_for_call(call)) {
                call -> handler.receive_call(call);
                call -> set_handler(call -> handler);
            } else {
                // no employee is available
                call -> reply("Please wait for free employee to reply.\n");
                call_queues[call -> get_title()].push_back((*call));
            }
        } 

        // An employee got free. Look for a waiting call that employee can serve. 
        // Return true if we assigned a call, false otherwise.
        bool assign_call(Employee& emp) {
            for(Call& call : call_queues[emp.job_title]) {
                std::shared_ptr<Call> call_ptr = std::make_shared<Call>(call);
                emp.receive_call(call_ptr);
                emp.start_call(call);
                return true;
            }
            return false;
        } 
    private: 
        std::vector<Employee> get_employees(const int num_of_repondents, const int num_of_managers, 
                                            const int num_of_directors, std::shared_ptr<CallHandler>& handler) {
            std::vector<Employee> employees;
            for(int i = 0; i < num_of_repondents; i++) {
                employees.push_back(Employee(JobTitle::Respondent, i, handler));
            }
            for(int i = 0; i < num_of_managers; i++) {
                employees.push_back(Employee(JobTitle::Manager, i + num_of_repondents, handler));
            }
            for(int i = 0; i < num_of_directors; i++) {
                employees.push_back(Employee(JobTitle::Director, i + num_of_repondents + num_of_managers, handler));
            }
            return employees;
        }
};

void Employee::escalate_and_reassign() {
    current_call -> increment_title();
    finish_call();
    finish_call();
    handler -> dispatch_call(current_call);
}

std::vector<Call> get_random_calls() {
    std::vector<Call> calls;
    constexpr auto num_of_calls = 25;
    int challenging_level;
    constexpr int num_of_challenging_levels = 3;
    srand(time(NULL));
    for(int i = 0; i < num_of_calls; i++) {
        challenging_level = rand() % num_of_challenging_levels;
        Caller caller(challenging_level);
        Call call(caller);
        calls.push_back(call);
    }
    return calls;
}

/**
 * Imagine you have a call center with three levels of employees: respondent, 
 * manager and director. An incoming telephone call must be first allocated to 
 * a respondent who is free. If the respondent can't handle the call, he or she
 * must escalate the call to a manager. If the manager is not free or not able
 * to handle it, then the call should be escalated to a director. Design the classes
 * and data structures for this problem. Implement a method dispatchCall() which
 * assigns a call to the first available employee.
 */
int main() {
    std::cout << "===================\n"
                 "Call center program\n"
                 "===================\n";
    std::shared_ptr<CallHandler> call_handler = std::make_shared<CallHandler>();
    call_handler -> initialize_employees();
    std::vector<Call> calls = get_random_calls();
    for(Call& call : calls) {
        call_handler -> get_handler_for_call(call);
    }
    return 0;
}
