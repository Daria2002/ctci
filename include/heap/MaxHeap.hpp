#include <iostream>
#include <vector>
#include <algorithm>
 
class MaxHeap 
{
    private:
        std::vector<int> elements;
    
        inline int parent_index(const int i) const
        { 
            return (i - 1) / 2; 
        }
    
        inline int left_index(const int i) const
        { 
            return (2 * i + 1); 
        }
     
        inline int right_index(const int i) const
        { 
            return (2 * i + 2); 
        }
    
        // Recursive Heapify-down algorithm the node at index i and its two direct children
        // violates the heap property
        void heapify_down(const int i)
        {
            // get left and right child of node at index i
            int left = left_index(i);
            int right = right_index(i);
            int largest = i;
            // compare A[i] with its left and right child and find largest value
            if (left < size() && elements[left] > elements[i]) largest = left;
            if (right < size() && elements[right] > elements[largest]) largest = right;
            // swap with child having greater value and call heapify-down on the child
            if (largest != i) {
                std::swap(elements[i], elements[largest]);
                heapify_down(largest);
            }
        }
    
        // Recursive Heapify-up algorithm
        void heapify_up(const int i)
        {
            // check if node at index i and its parent violates the heap property
            if (i && (elements[parent_index(i)] < elements[i])) 
            {
                // swap the two if heap property is violated
                std::swap(elements[i], elements[parent_index(i)]);
                // call Heapify-up on the parent
                heapify_up(parent_index(i));
            }
        }
        
    public:
        // return size of the heap
        inline unsigned int size() const
        {
            return elements.size();
        }

        // function to check if heap is empty or not
        inline bool empty() const
        {
            return size() == 0;
        }

        // insert key into the heap
        void push(const int key)
        {
            // insert the new element to the end of the vector
            elements.push_back(key);
            // get element index and call heapify-up procedure
            int index = size() - 1;
            heapify_up(index);
        }
    
        // function to remove element with highest priority (present at root)
        void pop()
        {
            // replace the root of the heap with the last element of the vector
            elements[0] = elements.back();
            elements.pop_back();
            // call heapify-down on root node
            heapify_down(0);
        }
    
        // function to return element with highest priority (present at root)
        inline int top() const
        {
            return elements.at(0);
        }
};