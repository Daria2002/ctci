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
        std::shared_ptr<CallHandler> handler;
        bool free = true;
        bool start_call(Call&);
        void finish_call();
        bool receive_call(std::shared_ptr<Call>&);
        void escalate_and_reassign(std::shared_ptr<Call>&);
        void set_current_call(std::shared_ptr<Call>&);
    private: 
        std::shared_ptr<Call> current_call;
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
    std::time_t end_time = now + rand() % 5; // increase random num of seconds in range [0, 5]
    return end_time;
}

class Call : public std::enable_shared_from_this<Call> {
    public:
        Call(Caller c) : caller(c), title(JobTitle::Respondent){
            call_oder = order;
            order++;
        }
        Caller caller;
        int call_oder;
        static int order;
        Employee handler;
        void set_handler(Employee& e) {
            handler = e;
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

int Call::order = 0;

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

bool Employee::start_call(Call& call) {
    if(call.caller.challenging_level > job_title) {
        std::shared_ptr<Call> tmp = current_call;
        finish_call();
        std::cout << "Call redirection.\n";
        escalate_and_reassign(tmp);
        return false;
    } else {
        time_t end_call = call_end_time();
        bool printed = false;
        while(time(0) < end_call) {
            if (!printed) {
                std::cout << "Employee with id " << call.handler.id << " is talking.\n";
                printed = true;
            }
        }
        std::cout << "Employee with id " << call.handler.id << " is not talking anymore.\n";
    }
    finish_call();
    return true;
}
void Employee::finish_call() {
    current_call = nullptr;
    free = true;
}
bool Employee::receive_call(std::shared_ptr<Call>& call) {
    if(free) {
        current_call = call;
        std::cout << "Employee " << id << " will try to handle " << call -> call_oder << '\n';
        free = false;
        return true;
    }
    return false;
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

        bool get_handler_for_call(Call& call) {
            for(Employee& em : employees) {
                if(!em.free) {
                    std::cout << "Employee " << em.id << " is not free\n";
                }
                if(em.job_title < call.get_title()) {
                    std::cout << "Employee title is not matching a call title\n";
                    std::cout << "Employee title is " << em.job_title << '\n';
                    std::cout << "Call title is " << call.get_title() << '\n';
                }

                if(em.free && em.job_title >= call.get_title()) {
                    call.set_handler(em);
                    std::shared_ptr<Call> tmp = std::make_shared<Call>(call);
                    em.receive_call(tmp);
                    if(em.start_call(call) == false) {
                        // em.free = true;
                        continue;
                    } else {
                        // em.free = true;
                        return true;
                    }
                }
            }
            std::cout << "There is no available handler.\n";
            return false;
        }  

        // routes the call to an available employee, or saves in a queue if no employee is available
        void dispatch_call(std::shared_ptr<Call>& call) {
            if(get_handler_for_call(*call)) {
                call -> handler.receive_call(call);
                call -> set_handler(call -> handler);
                call -> handler.start_call(*call);
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

void Employee::escalate_and_reassign(std::shared_ptr<Call>& call) {
    call -> increment_title();
}

std::vector<Call> get_random_calls() {
    std::vector<Call> calls;
    constexpr auto num_of_calls = 40;
    int challenging_level;
    constexpr int num_of_challenging_levels = 3;
    srand(time(NULL));
    for(int i = 0; i < num_of_calls; i++) {
        challenging_level = rand() % num_of_challenging_levels;
        std::cout << "Call order = " << i << ", challenging level = " << challenging_level << '\n';
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
        std::cout << "===== start handling call " << call.call_oder << " =====\n";
        call_handler -> get_handler_for_call(call);
    }
    return 0;
}
