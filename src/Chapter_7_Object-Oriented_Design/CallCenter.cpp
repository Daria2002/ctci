#include <iostream>
#include <vector>
#include <memory>

enum JobTitle {
    Respondent = 0, Manager = 1, Director = 2
};

class Call;

class Employee {
    public:
        Employee() = default;
        Employee(JobTitle t) : job_title(t) {}
        JobTitle job_title;
        std::shared_ptr<Call> current_call;
        bool is_free() {
            return current_call == nullptr;
        }
        void start_call(std::shared_ptr<Call> call) {
            current_call = call;
        }
        void finish_call() {
            current_call = nullptr;
        }
};

class Caller {
    public:
        int phone_number;
};

class Call {
    public:
        Call(Caller c) : caller(c), title(JobTitle::Respondent) {}
        Caller caller;
        void set_handler(Employee e) {
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
        void increment_title(JobTitle t) {
            title = JobTitle(title + 1);
        }
        void disconnect() {
            
        }
    private:
        Employee handler;
        JobTitle title;
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

std::vector<Employee> get_employees(int resp, int man, int dir) {
   
}

class CallHandler {
    public:
        const int levels = 3;
        const int num_of_repondents = 10;
        const int num_of_managers = 4;
        const int num_of_directors = 2;
        std::vector<Employee> employees = get_employees(num_of_repondents, num_of_managers, num_of_directors);
        void dispatch_call() {

        }       
};



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

}
