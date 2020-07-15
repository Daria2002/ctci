#include <iostream>

/**
 * Imagine you have a 20 GB file with one string per line. Explain how you would sort the file. 
 */
int main() {
    std::cout << "20 GB represents a lot of data, so probably we don't\n"
                 "want to bring all the data into memory. It's better to\n"
                 "put only part of the data into memory. The file should\n"
                 "be divided into chunks, which are x megabytes each,\n"
                 "where x is the amount of memory we have available. Each\n"
                 "chunk is sorted using merge sort seperately and then those\n"
                 "sorted chunks are merged and saved back to the file system\n"
                 "At the end, we have a fully sorted file. This algorithm is\n"
                 "know as external sort.\n";
}
