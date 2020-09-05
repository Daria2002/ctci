#include <iostream>

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
}