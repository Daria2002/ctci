#include <iostream>
#include <vector>
#include <memory>

class Box {
    public:
        int w, h, d;
        Box() = default;
        Box(int _w, int _h, int _d) : w(_w), h(_h), d(_d) {}
        bool smaller_than(std::shared_ptr<Box> box) const {
            return d < box->d && h < box->h && w < box->w;
        }
};

int tallest_height_experiment(std::vector<Box> boxes, int bottom_index) {
    int total_height = 0; 
    Box box = boxes[bottom_index];
    for(int i = bottom_index + 1; i < boxes.size(); i++) {
        if(boxes[i].smaller_than(std::make_shared<Box>(box))) {
            int height = tallest_height_experiment(boxes, i);
            if(height > total_height) {
                total_height = height;
            }
        }
    }
    total_height += box.h;
    return total_height;
}

int tallest_height_experiment(std::vector<Box> boxes) {
    int max = 0; 
    for(int i = 0; i < boxes.size(); i++) {
        int height = tallest_height_experiment(boxes, i);
        if(height > max) {
            max = height;
        }
    }
    return max;
}

int tallest_height_experiment_cache(std::vector<Box> boxes,
int bottom_index, std::vector<int>& stack_map) {
    if(bottom_index < boxes.size() && stack_map[bottom_index] > 0) {
        return stack_map[bottom_index];
    }
    Box bottom = boxes[bottom_index];
    int max_height = 0; 
    for(int i = bottom_index + 1; i < boxes.size(); i++) {
        if(boxes[i].smaller_than(std::make_shared<Box>(bottom))) {
            int height = tallest_height_experiment_cache(boxes, i, stack_map);
            if(height > max_height) max_height = height;
        }
    }
    max_height += bottom.h;
    stack_map[bottom_index] = max_height;
    return max_height;
}

int tallest_height_experiment_cache(std::vector<Box> boxes) {
    int max_height = 0; 
    std::vector<int> stack_map;
    for(int i = 0; i < boxes.size(); i++) stack_map.push_back(0);
    for(int i = 0; i < boxes.size(); i++) {
        int height = tallest_height_experiment_cache(boxes, i, stack_map);
        if(height > max_height) max_height = height;
    }
    return max_height;
}

int tallest_height_making_choice(std::vector<Box> boxes,
std::shared_ptr<Box> bottom, int offset, std::vector<int> stack_map) {
    if(offset >= boxes.size()) return 0;
    // take this box
    Box new_bottom = boxes[offset];
    int height_with_bottom = 0;
    if(bottom == nullptr || new_bottom.smaller_than(bottom)) {
        if(stack_map[offset] == 0) {
            stack_map[offset] = tallest_height_making_choice(boxes, std::make_shared<Box>(new_bottom), offset + 1, stack_map);
            stack_map[offset] += new_bottom.h;
        }
        height_with_bottom += stack_map[offset];
    }
    // don't take this box
    int height_without_bottom = tallest_height_making_choice(boxes, bottom, offset + 1, stack_map);
    return height_with_bottom > height_without_bottom ? height_with_bottom : height_without_bottom;
}

int tallest_height_making_choice(std::vector<Box> boxes) {
    std::vector<int> stack_map;
    for(int i = 0; i < boxes.size(); i++) stack_map.push_back(0);
    return tallest_height_making_choice(boxes, nullptr, 0, stack_map);
}

std::vector<Box> get_boxes() {
    std::vector<Box> boxes;
    boxes.push_back(Box(2, 12, 3));
    boxes.push_back(Box(7, 4, 11));
    boxes.push_back(Box(19, 13, 16));
    boxes.push_back(Box(13, 3, 9));
    boxes.push_back(Box(2, 2, 1));
    return boxes;
}

void merge(std::vector<Box>& boxes, int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 = r - m; 
    std::vector<Box> L;
    std::vector<Box> R;

    for (i = 0; i < n1; i++) 
        L.push_back(boxes[l + i]); 
    for (j = 0; j < n2; j++) 
        R.push_back(boxes[m + 1 + j]); 

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) { 
        if (L[i].h >= R[j].h) { // descending order
            boxes[k] = L[i]; 
            i++; 
        } 
        else { 
            boxes[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    // Copy the remaining elements of L[], if there are any
    while (i < n1) { 
        boxes[k] = L[i]; 
        i++; 
        k++; 
    } 
    // Copy the remaining elements of R[], if there are any
    while (j < n2) { 
        boxes[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
  
/* l is for left index and r is right index of the 
   sub-array of arr to be sorted */
void mergeSort(std::vector<Box>& boxes, int l, int r) 
{ 
    if (l < r) {
        int m = l + (r - l) / 2;  
        mergeSort(boxes, l, m); 
        mergeSort(boxes, m + 1, r); 
        merge(boxes, l, m, r); 
    } 
} 

void sort_boxes(std::vector<Box>& boxes) {
    mergeSort(boxes, 0, boxes.size());
}

/**
 * You have a stack of n boxes, with widths w_i heights h_i and depths d_i. The boxes
 * cannot be rotated and can only be stacked on top of one another if each box in the stack is strictly
 * larger than the box above sit in width, height. and depth. Implement a method to compute the
 * height of the tallest possible stack. The height of a stack is the sum of the heights of each box.
 */
int main() {
    int method;
    std::cout << "Enter 1 to solve using experiment method, "
    "enter 2 to solve using experiment method with cache, "
    "otherwise any other number to solve making a choice.\n";
    std::cin >> method;
    std::vector<Box> boxes = get_boxes();
    sort_boxes(boxes);
    int tallest_height;
    switch (method)
    {
    case 1:
        tallest_height = tallest_height_experiment(boxes);
        break;
    case 2:
        tallest_height = tallest_height_experiment_cache(boxes);
        break;
    default:
        tallest_height = tallest_height_making_choice(boxes);
        break;
    }
    std::cout << "Tallest possible stack has a height = " << tallest_height << '\n';
}
