#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <functional>

// a mutex is a lockable object that is designed to signal when critical sections of code need exclusive
// access, preventing other threads with the same protection from executing concurrently and access the
// same memory locations. 
std::mutex current_mutex;
int current = 1;

void fizzbuzz_single_threaded(int n) {
    for(int i = 1; i <= n; i++) {
        if(i % 3 == 0 && i % 5 == 0) {
            std::cout << "FizzBuzz\n";
        } else if(i % 3 == 0) {
            std::cout << "Fizz\n";
        } else if(i % 5 == 0) {
            std::cout << "Buzz\n";
        } else {
            std::cout << i << '\n';
        }   
    }
}

void FizzBuzz(bool div_3, bool div_5, int max, std::string to_print) {
    while(true) {
        // a lock_guard guarantees the mutex object is properly unlocked in case an exception is thrown
        std::lock_guard<std::mutex> lck(current_mutex);
        if(current > max) {
            return;
        }
        if((current % 3 == 0) == div_3 && (current % 5 == 0) == div_5) {
            std::cout << to_print << '\n';
            current++;
        }
    }
}

void Number(bool div_3, bool div_5, int max) {
    while(true) {
        std::lock_guard<std::mutex> lck(current_mutex);
        if(current > max) {
            return;
        }
        if((current % 3 == 0) == div_3 && (current % 5 == 0) == div_5) {
            std::cout << current << '\n';
            current++;
        }
    }
}

void FB(const std::function<bool(int)>& compare_f, const std::function<void()>& print_f, int max) {
    while (true)
    {
        std::lock_guard<std::mutex> lck(current_mutex);
        if(current > max) {
            return;
        }
        if(compare_f(current)) {
            print_f();
            current++;
        }
    }
}

/**
 * In the classic problem FizzBuzz, you are told to print the numbers
 * from 1 to n. However, when the number is divisible by 3, print "Fizz".
 * When it is divisible by 5, print "Buzz". When it is divisible by 3
 * and 5, print "FizzBuzz". In this problem, you are asked to do this
 * in a multithreaded way. Implement a multithreaded version of FizzBuzz
 * with four threads. One thread checks for divisibility of 3 and prints
 * "Fizz". Another thread is responsible for divisibility of 5 and prints
 * "Buzz". A third thread is responsible for divisibility of 3 and 5 and
 * prints "FizzBuzz". A fourth thread does the numbers.
 */ 
int main() {
    const int max = 15;
    std::cout << "SingleThreaded solution\n";
    fizzbuzz_single_threaded(max);
    std::cout << "Multithreaded solution will be implemented using two approaches: 1) two types of threads\n"
                 "(FizzBuzzThread and NumberThread) or 2) using one type of thread (FBThread)\n";
    std::cout << "If you want to solve it using 1st approach enter 1, otherwise any other number:\n";
    int method;
    std::cin >> method;
    std::vector<std::thread> threads;
    if(method == 1) {
        threads.push_back(std::thread(FizzBuzz, true, true, max, "FizzBuzz"));
        threads.push_back(std::thread(FizzBuzz, true, false, max, "Fizz"));
        threads.push_back(std::thread(FizzBuzz, false, true, max, "Buzz"));
        threads.push_back(std::thread(Number, false, false, max));
    } else {
        threads.push_back(std::thread(FB, [](int a){return a % 3 == 0 && a % 5 == 0;}, [](){std::cout << "FizzBuzz\n";}, max));
        threads.push_back(std::thread(FB, [](int a){return a % 3 == 0 && a % 5 != 0;}, [](){std::cout << "Fizz\n";}, max));
        threads.push_back(std::thread(FB, [](int a){return a % 3 != 0 && a % 5 == 0;}, [](){std::cout << "Buzz\n";}, max));
        threads.push_back(std::thread(FB, [](int a){return a % 3 != 0 && a % 5 != 0;}, [](){std::cout << current << '\n';}, max));
    }
    for(std::thread& th : threads) if(th.joinable()) th.join();
}