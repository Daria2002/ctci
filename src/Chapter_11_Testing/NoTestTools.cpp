#include <iostream>

/**
 * How would you load test a webpage without using any test tools? 
 */
int main() {
    std::cout << "Load testing is used to identify a web app maximum operating capacity and\n"
    "bottlenecks that may interfere with its performance. It can check how system\n"
    "responds in variations in load. To perform load testing, user must identify\n"
    "critical scenarious and the metrics which fulfill performance objectives.\n"
    "Typical criteria include response time, throughput, resource utilitation, max\n"
    "load that the system can bear. Design tests to simulate the load and measure each\n"
    "of these criteria. In the absence of formal testing tools we can create our own\n"
    "generating thousands of wirtual users simulating concurrent users. We would write\n"
    "a multi-threaded program with thousands of threads, where each thread acts as a real\n"
    "world user loading the page. For each of those virual users we would programmatically\n"
    "measure response time, data I/O, etc. Data gathered during the tests are compared with\n"
    "accepted values.\n";
}
