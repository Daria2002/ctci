#include <iostream>

void* aligned_malloc(std::size_t required_bytes, std::size_t alignement) {
    void* p1; // initial block;
    void* p2; // aligned block inside initial block;
    // extra space for pointer containing info where the full mem block begins
    int offset = alignement - 1 + sizeof(void*); 
    // initialize p1
    if((p1 = (void*)malloc(required_bytes + offset)) == NULL) return NULL;
    // alignment - 1 set 1 on every bit after the last 1 and set last 1 to 0
    // ~ will turn all 1s to 0s and all 0s to 1s
    p2 = (void*)malloc(((std::size_t)(p1) + offset) & ~(alignement - 1));
    // if we treat p2 as a void** (array of void*s), just look at index - 1 to retrieve p1
    ((void**)p2)[-1] = p1;
    return p2;
}

void aligned_free(void** p2) {
    // the address of where the full memory block begins is stored just
    // before the aligned memory block, so we take index - 1 to get the
    // address of where the full memory block starts
    void* p1 = ((void**)p2)[-1];
    // free all allocated memory, including extra 15 bytes
    // and ptr with start of the block address
    free(p1); // by freeing p1 we deallocate the whole mem block
}

/**
 * Write an aligned malloc and free function that supports allocating memory such that the
 * memory address returned is divisible by a specific power of two.
 * EXAMPLE:
 * align_malloc(1000, 128) will return a memory address that is a multiple of 128 and that points
 * to memory of size 1000 bytes.
 * aligned_free() will free memory allocated by align_malloc. 
 */
int main() {
    std::cout << "With malloc we don't have a control over where the memory is allocated\n"
                 "within the heap. We need to return a memory address which is divisible\n"
                 "by the desired value. i.e. we request 100-byte chunk of mem and want to\n"
                 "start at a mem address that is multiple of 16. We would need extra 15 bytes\n"
                 "plus another 100 bytes right after that sequence, so we could be sure that\n"
                 "we have a memory address divisible by 16 with space for 100 bytes. We use\n"
                 "void* because it can be casted in pointer of any type.\n";
    void* ptr = aligned_alloc(4, 2);
    std::cout << "ptr address = " << ptr << '\n';
    aligned_free(&ptr);
}
