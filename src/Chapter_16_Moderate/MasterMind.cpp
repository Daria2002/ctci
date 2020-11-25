#include<iostream>
#include<ctime> // time
#include<cstdlib> // srand, rand
#include<vector>

class Result {
    public:
        Result() = default;
        Result(int h, int p) : hits(h), pseudohits(p) {}
        int hits = 0;
        int pseudohits = 0;
};

std::ostream& operator<<(std::ostream& os, const Result& result) 
{
    os << "Hits = " << result.hits << ", pseudo-hits = " << result.pseudohits << '\n';
    return os;
}

char code(int n) 
{
    switch (n)
    {
    case 0:
        return 'R';
    case 1:
        return 'Y';
    case 2:
        return 'G';
    case 3:
        return 'B';
    default:
        return ' ';
    }
}

int code(char c) 
{
    switch (c)
    {
    case 'R':
        return 0;
    case 'Y':
        return 1;
    case 'G':
        return 2;
    case 'B':
        return 3;
    default:
        return -1;
    }
}

Result estimate(std::string guess, std::string solution, const int digits) 
{
    if(guess.size() != solution.size()) return Result(-1, -1);
    Result res;
    std::vector<int> freq(digits);
    // compute hits and build freq vector
    for(int i = 0; i < guess.size(); i++) 
    {
        if(guess[i] == solution[i]) 
        {
            res.hits++;
        } 
        else 
        {
            freq[code(solution[i])]++; // if not hit
        }
    }
    // compute pseudo-hits
    for(int i = 0; i < guess.size(); i++) {
        int c = code(guess[i]);
        // if c is not hit 
        // guess[i] != solution[i] -> i.e. sol = RRGB guess = RGBR
        // R is hit and pseudo-hit, count only when pseudo-hit
        if(c >= 0 && freq[c] > 0 && guess[i] != solution[i]) {
            res.pseudohits++;
            freq[c]--;
        }
    }
    return res;
}

std::string get_random_code(const int digits) 
{
    std::string random_code = "";
    for(int i = 0; i < digits; i++) {
        random_code += code(rand() % 4);
    }
    return random_code;
}

/**
 * The Game of Master Mind is played as follows:
 * The computer has four slots, and each slot will contain a ball that is red (R), yellow (Y), green (G) or
 * blue (B). For example, the computer might have RGGB (Slot #1 is red, Slots #2 and #3 are green, Slot
 * #4 is blue).
 * You, the user, are trying to guess the solution. You might, for example, guess YRGB.
 * When you guess the correct color for the correct slot, you get a "hit". If you guess a color that exists
 * but is in the wrong slot, you get a "pseudo-hit". Note that a slot that is a hit can never count as a
 * pseudo-hit.
 * For example, if the actual solution is RGBY and you guess GGRR, you have one hit and one pseudo-
 * hit.
 * Write a method that, given a guess and a solution, returns the number of hits and pseudo-hits.
 */
int main() 
{
    constexpr int digits = 4;
    srand(std::time(NULL));
    std::string solution = get_random_code(digits);
    constexpr int iterations = 10;
    for(int i = 0; i < iterations; i++) 
    {
        std::string guess = get_random_code(digits);
        std::cout << "Solution = " << solution << ", guess = " << guess << '\n';
        Result result = estimate(guess, solution, digits);
        std::cout << result;
        if(result.hits == digits) break;
    }
}