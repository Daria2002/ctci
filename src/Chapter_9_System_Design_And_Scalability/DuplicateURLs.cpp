#include <iostream>

/**
 * You have 10 billion URLs. How do you detect the duplicate documents? 
 * In this case, assume duplicate means that the URLs are identical.
*/
int main() {
    std::cout << "Space: 10 billion URLs = 10 * 10^9 URLs\n"
                 "1 URL = 100 characters, 1 character = 4 bytes(Unicode)\n"
                 "10 billion URLs = 4 terabytes\n"
                 "Solution #1: Disk Storage\n"
                 "  Store all data on one machine. First pass split the list\n"
                 "  of URLs into 4000 chunks of 1 GB each. Each URL is stored in\n"
                 "  a file named <x>.txt where x = hash(u) % 4000. In the second pass:\n"
                 "  load each file, create a hash table of the URLs (key = URL,\n"
                 "  value = false if URL was not already in db, otherwise true)\n"
                 "  and look for duplicates.\n"
                 "Solution #2: Multiple Machines\n"
                 "  Instead of saving URL to x file, it's saved in machine x.\n"
                 "  Pro of using multiple machines is that we can parallelize the\n"
                 "  operation, such that all 4000 chunks are processed simultaneously\n"
                 "  which can result in a faster solution for large amounts of data.\n"
                 "  Con of using multiple machines is that we are relying on 4000 different\n"
                 "  machines to operate perfectly. That may not be realistic and there should be\n"
                 "  considered how to handle failture. The complexity of the system have\n"
                 "  increased by involving so many machines.\n";
}
