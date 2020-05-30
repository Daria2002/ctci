#include <iostream>
#include <vector>
#include <memory>
#include <array>

enum JobTitle {
    Respondent = 0, Manager = 1, Director = 2
};

class Employee;
class CallHandler;

class Caller {
    public:
        int phone_number;
};

class Call {
    public:
        Call(Caller c) : caller(c), title(JobTitle::Respondent) {}
        Caller caller;
        void set_handler(std::shared_ptr<Employee> e) {
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
        std::shared_ptr<Employee> handler;
        JobTitle title;
};

class Employee {
    public:
        int id;
        Employee() = default;
        Employee(JobTitle t, int i, std::shared_ptr<CallHandler> h) : job_title(t), id(i), handler(h) {}
        JobTitle job_title;
        std::shared_ptr<Call> current_call;
        std::shared_ptr<CallHandler> handler;
        bool is_free() {
            return current_call == nullptr;
        }
        void start_call(std::shared_ptr<Call> call) {
            std::cout << "call started\n";
        }
        void finish_call() {
            std::cout << "call finished\n";
            current_call = nullptr;
        }
        bool receive_call(std::shared_ptr<Call> call) {
            current_call = call;
            return is_free();  
        }
        void escalate_and_reassign();
};

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

std::vector<Employee> get_employees(const int, const int, const int, std::shared_ptr<CallHandler>);

class CallHandler : public std::enable_shared_from_this<CallHandler> {
    public:
        CallHandler() {
            employees = get_employees(num_of_repondents, num_of_managers, num_of_directors, shared_from_this());
        }
        static constexpr auto num_of_repondents = 10;
        static constexpr auto num_of_managers = 4;
        static constexpr auto num_of_directors = 2;
        static constexpr auto levels = 3;
        std::vector<Employee> employees;
        std::array<std::vector<Call>, levels> call_queues;

        bool get_handler_for_call(std::shared_ptr<Call> call, Employee em) {
            for(int i = 0; i < employees.size(); i++) {
                if(employees[i].is_free()) {
                    em = employees[i];
                    return true;
                }
            }
            return false;
        }    

        // routes the call to an available employee, or saves in a queue if no employee is available
        void dispatch_call(std::shared_ptr<Call> call) {
            Employee em;
            if(get_handler_for_call(call, em)) {
                em.receive_call(call);
                std::shared_ptr<Employee> em_ptr = std::make_shared<Employee>(em);
                (*call).set_handler(em_ptr);
            } else {
                // no employee is available
                (*call).reply("Please wait for free employee to reply.\n");
                call_queues[(*call).get_title()].push_back((*call));
            }
        } 

        // An employee got free. Look for a waiting call that employee can serve. 
        // Return true if we assigned a call, false otherwise.
        bool assign_call(Employee& emp) {
            for(Call& call : call_queues[emp.job_title]) {
                emp.receive_call(std::make_shared<Call>(call));
                return true;
            }
            return false;
        } 
};

std::vector<Employee> get_employees(const int num_of_repondents, const int num_of_managers, 
                                    const int num_of_directors, std::shared_ptr<CallHandler> handler) {
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
void Employee::escalate_and_reassign() {
    (*current_call).increment_title();
    finish_call();
    (*handler).dispatch_call(current_call);
    current_call = nullptr;
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
    CallHandler ch();
}
