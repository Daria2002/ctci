#include <iostream>
#include <vector>
#include <string>
#include <list>

class NumberBuilder {
    public:
        static std::vector<std::string> smalls;
        static std::vector<std::string> tens;
        static std::vector<std::string> bigs;    
        static std::string hundred;
        static std::string negative;
};

std::vector<std::string> NumberBuilder::smalls = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", 
"Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
std::vector<std::string> NumberBuilder::tens = {"", "", "Twenty", "Thirty", "Fourty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
std::vector<std::string> NumberBuilder::bigs = {"", "Thousand", "Million", "Billion"};
std::string NumberBuilder::hundred = "Hundred";
std::string NumberBuilder::negative = "Negative";

std::string listToStr(std::list<std::string> parts) {
    std::string str = "";
    int i = 0; 
    for(std::string part : parts) {
        str += part;
        if(i != parts.size() - 1) str += " ";
        i++;
    }
    return str;
}

std::string convertChunk(int num) {
    std::list<std::string> parts;
    // convert hundred place
    if(num >= 100) {
        parts.push_back(NumberBuilder::smalls[num / 100]);
        parts.push_back(NumberBuilder::hundred);
        num %= 100;
    }
    // convert tens place
    if(num >= 10 && num <= 19) {
        parts.push_back(NumberBuilder::smalls[num]);
    } else if(num >= 20) {
        parts.push_back(NumberBuilder::tens[num / 10]);
        num %= 10;
    }
    // convert ones place
    if(num >= 1 && num <= 9) {
        parts.push_back(NumberBuilder::smalls[num]);
    }
    return listToStr(parts);
}

std::string convert(int num) {
    if(num == 0) return NumberBuilder::smalls[0];
    else if(num < 0) return NumberBuilder::negative + " " + convert(-1 * num);
    std::list<std::string> parts;
    int chunkCount = 0;
    while (num > 0)
    {
        if(num % 1000 != 0) {
            std::string chunk = convertChunk(num % 1000) + " " + NumberBuilder::bigs[chunkCount];
            parts.push_front(chunk);
        }
        num /= 1000; // shift chunk
        chunkCount++;
    }
    return listToStr(parts);
}

/**
 * Given any integer, print an English phrase that describes the integer (e.g., "One
 * Thousand, Two Hundred Thirty Four").
 */
int main() {
    std::cout << "Enter a number: ";
    int num;
    std::cin >> num;
    std::cout << convert(num) << '\n';
}