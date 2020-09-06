#include <iostream>
#include <thread>
#include <vector>

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
    std::cout << "FizzBuzz\n";
}

void Number(bool div_3, bool div_5, int max) {
    std::cout << "Number\n";
}

void FB(bool div_3, bool div_5, int max, std::string to_print) {
    // TODO: change params
    std::cout << "FB\n";
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
    std::cout << "SingleThreaded solution\n";
    fizzbuzz_single_threaded(10);
    std::cout << "Multithreaded solution will be implemented using two approaches: 1) two types of threads\n"
                 "(FizzBuzzThread and NumberThread) or 2) using one type of thread (FBThread)\n";
    std::cout << "If you want to solve it using 1st approach enter 1, otherwise any other number:\n";
    int method;
    std::cin >> method;
    const int max = 10;
    std::vector<std::thread> threads;
    if(method == 1) {
        threads.push_back(std::thread(FizzBuzz, true, true, max, "FizzBuzz"));
        threads.push_back(std::thread(FizzBuzz, true, false, max, "Fizz"));
        threads.push_back(std::thread(FizzBuzz, false, true, max, "Buzz"));
        threads.push_back(std::thread(Number, true, true, max));
    } else {
        threads.push_back(std::thread(FB, true, true, max, "FizzBuzz"));
    }
    for(std::thread& th : threads) if(th.joinable()) th.join();
}