#include <iostream>

class MyMutex {
    public:
        MyMutex() {}
        void lock() {}
        void unlock() {}
};

class MySemaphore {
    public:
        // num specifies the initial count (the number of threads
        // that can access a shared resource at any one time)
        MySemaphore(int num) : count(num) {}
        void acquire() {}
        void release() {}
        int count;
};

class FooBad {
    public:
        int pause_time = 100;
        MyMutex m1, m2;
        FooBad() {
            try
            {   
                m1.lock();
                m2.lock();
            }
            catch(const std::exception& e)
            {
            }
        }
        void first() {
            try
            {
                // do the work
                m1.unlock(); // mark finished with first()
            }
            catch(const std::exception& e)
            {
            }
        }
        void second() {
            try
            {
                m1.lock(); // wait until finished with first()
                m1.unlock();
                // do the work
                m2.unlock(); // mark finished with first()
            }
            catch(const std::exception& e)
            {
            }
        }
        void third() {
            try
            {
                m2.lock(); // wait until finished with second();
                m2.unlock();
                // do the work
            }
            catch(const std::exception& e)
            {
            }
        }
};

class Foo {
    public:
        MySemaphore s1 = MySemaphore(1);
        MySemaphore s2 = MySemaphore(1);
        Foo() {
            
        }
        void first() {}
        void second() {}
        void third() {}
};

/**
 * Call In Order: Suppose we have the following code: 
 * public class Foo {
 *  public Foo() {...}
 *  public void first() {...}
 *  public void second() {...}
 *  public void third() {...}
 * } 
 * The same instace of Foo will be passed to three different threads. ThreadA willl
 * call first, threadB will call second, threadC will call third. Design a mechanism
 * to ensure that first is called before second and second is called before third.
*/
int main() {
    std::cout << "The general logic is to check if first() has completed before\n"
                 "executing second(), and if second() has completed before calling\n"
                 "third(). Because we need to be very careful about thread safety,\n"
                 "simple boolean flags won't do the job. What about using lock? i.e.\n"
                 "FooBad class. That code won't work due to the concept of lock ownership.\n"
                 "One thread is actually performing the lock (in the FooBad constructor),\n"
                 "but different threads attempt to unlock the locks. This is not allowed,\n"
                 "and your code will raise an exception. A lock in Java is owned by the same\n"
                 "thread which locked it. Instead, we can replicate this behavior with\n"
                 "semaphores like it's used in Foo class. The logic is identical.\n";
}
