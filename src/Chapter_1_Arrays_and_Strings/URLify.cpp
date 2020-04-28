#include <iostream>

int count_characters(const std::string&, const char&);
std::string char_arr_to_string(const char*, const int& size);

/**
 * Write a method to replace all spaces in string with '%20'. You may assume that the string
 * has sufficient space at the end to hold the additional characters, and that you are given the
 * "true" length of the string.
 */
int main() {
    const std::string replacement_string = "%20";
    std::cout << "Enter string: " << std::endl;
    char input[100];
    std::cin.getline(input, sizeof(input));
    std::string str_size;
    std::cout << "Enter string size: " << std::endl;
    std::cin >> str_size;
    int size = std::stoi(str_size);
    std::string str = char_arr_to_string(input, size);

    int number_of_spaces = count_characters(str, ' ');
    if(number_of_spaces == 0) {
        std::cout << "String is not modified, because it doesn't contain space." << std::endl;
        return 0;
    }
    // replacement_string.size() - 1 because we replace one ' ' with %20,
    // that is replacement_string.size() - 1 extra space
    int new_index = (size - 1) + number_of_spaces * (replacement_string.size() - 1); 

    str.resize(new_index + 1);

    for(int old_index = size - 1; old_index >= 0; old_index--) {
        if(str[old_index] == ' ') {
            str[new_index] = '0';
            str[new_index - 1] = '2';
            str[new_index - 2] = '%';
            new_index -= replacement_string.size();
        } else {
            str[new_index] = str[old_index];
            new_index--;
        }
    }

    std::cout << "Modified string: " << str << std::endl;
}

std::string char_arr_to_string(const char* arr, const int& size) {
    std::string str = "";
    for(int i = 0; i < size; i++) {
        str += arr[i];
    }
    return str;
}

int count_characters(const std::string& str, const char& character) {
    int counter = 0;
    for(int i = 0; i < str.size(); i++) {
        if(str[i] == character) {
            counter++;
        }
    }
    return counter;
}