#include <iostream>
#include <vector>
#include <algorithm>

class Dimension
{
    public:
        Dimension() = default;
        Dimension(int h, int w): ht(h), wt(w) {}
        int ht, wt;
};

std::vector<Dimension> get_dimensions()
{
    std::vector<Dimension> dims;
    dims.push_back(Dimension(65, 105));
    dims.push_back(Dimension(70, 150));
    dims.push_back(Dimension(56, 90));
    dims.push_back(Dimension(75, 190));
    dims.push_back(Dimension(60, 95));
    dims.push_back(Dimension(68, 100));
    return dims;
}

std::vector<Dimension> max(std::vector<Dimension> v1, std::vector<Dimension> v2)
{
    if(v1.empty()) return v2;
    else if(v2.empty()) return v1;
    return v1.size() > v2.size() ? v1 : v2;
}

bool can_append(Dimension dim, std::vector<Dimension> seq)
{
    if(seq.empty()) return true;
    Dimension last = seq[seq.size() - 1];
    return last.wt < dim.wt && last.ht < dim.ht;
}

std::vector<Dimension> longest_seq_at_index(std::vector<Dimension> people, std::vector<Dimension> seq, int index)
{
    if(index >= people.size()) return seq;
    Dimension dim = people[index];
    std::vector<Dimension> without = longest_seq_at_index(people, seq, index + 1);
    std::vector<Dimension> with;
    if(can_append(dim, seq))
    {
        std::vector<Dimension> seqWith = seq;
        seqWith.push_back(dim);
        with = longest_seq_at_index(people, seqWith, index + 1);
    }
    return max(without, with);
}

std::vector<Dimension> longest_recursive(std::vector<Dimension> people)
{
    std::sort(people.begin(), people.end(), [](const Dimension& lhs, const Dimension& rhs)
    {
        return lhs.ht < rhs.ht;
    });
    return longest_seq_at_index(people, std::vector<Dimension>(), 0);
} 

std::vector<Dimension> longest_seq_at_index(std::vector<Dimension> people, 
std::vector<std::vector<Dimension>> solutions, int index)
{
    Dimension dim = people[index];
    std::vector<Dimension> best_seq;
    // find the longest subseq that we can append this element to
    for(int i = 0; i < index; i++)
    {
        std::vector<Dimension> solution = solutions[i];
        if(can_append(dim, solution)) 
        {
            best_seq = max(best_seq, solution);
        }
    }
    best_seq.push_back(dim);
    return best_seq;
}

std::vector<Dimension> longest_iterative(std::vector<Dimension> people)
{
    std::sort(people.begin(), people.end(), [](const Dimension& lhs, const Dimension& rhs)
    {
        return lhs.ht < rhs.ht;
    });
    std::vector<std::vector<Dimension>> solutions;
    for(int i = 0; i < people.size(); i++) solutions.push_back(std::vector<Dimension>());
    std::vector<Dimension> best_seq;
    // find the longest subseq that terminates with each element
    for(int i = 0; i < people.size(); i++)
    {
        std::vector<Dimension> longest_at_index = longest_seq_at_index(people, solutions, i);
        solutions[i] = longest_at_index;
        best_seq = max(best_seq, longest_at_index);
    }
    return best_seq;
} 

/**
 * Circus Tower: A circus is designing a tower routine consisting of people
 * standing atop one another's shoulders. For practical and aesthetic reasons,
 * each person must be both shorter and lighter than the person below him or her.
 * Given the hights and weights of each person in the circus, write a method to 
 * compute the largest possible number of people in such a tower.
 * EXAMPLE:
 * Input (ht, wt): (65, 105) (70, 150) (56, 90) (75, 190) (60, 95) (68, 100)
 * Output: The longest tower is length 6 and includes from top to bottom:
 * (56, 90) (60, 95) (65, 100) (68, 110) (70, 150) (75, 190) 
 */
int main()
{
    std::cout << "Enter 1 to solve using recursive solution or any other number\n"
    "to solve using iterative solution:\n";
    int method;
    std::cin >> method;
    std::vector<Dimension> people = get_dimensions();
    std::vector<Dimension> longest_tower = (method == 1 ? 
    longest_recursive(people) : longest_iterative(people));
    std::cout << "Longest tower:\n";
    for(Dimension dim : longest_tower)
    {
        std::cout << "ht = " << dim.ht << ", wt = " << dim.wt << '\n';
    }
}