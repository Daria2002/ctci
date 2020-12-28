#include <iostream>
#include <unordered_map>
#include <vector>
#include <limits>
#include <algorithm>

class Term
{
    public:
        enum Operator
        {
            ADD, SUBTRACT, MULTIPLY, DIVIDE, BLANK
        };

        Term() = default;

        Term(double v, Operator o) : value(v), op(o) {}

        double get_value() 
        {
            return value;
        }

        Operator get_operator()
        {
            return op;
        }

        void set_number(double v)
        {
            value = v;
        }

        static std::vector<Term> parse_term_sequence(std::string sequence)
        {
            std::vector<Term> terms;
            while (!sequence.empty())
            {
                double num;
                std::string num_str;
                Operator op;
                char op_char;
                int start = 0;
                if(sequence[0] >= '0' && sequence[0] <= '9') 
                {
                    op = Operator::BLANK;
                }
                else 
                {
                    op_char = sequence[start];
                    switch (op_char)
                    {
                    case '+':
                        op = Operator::ADD;
                        break;
                    case '-':
                        op = Operator::SUBTRACT;
                        break;
                    case '/':
                        op = Operator::DIVIDE;
                        break;
                    default:
                        op = Operator::MULTIPLY;
                        break;
                    }
                    start++; // number starts at index 1
                }
                int end;
                for(end = start; end < sequence.size(); end++)
                {
                    if(sequence[end] < '0' || sequence[end] > '9') break;
                    num_str += sequence[end];
                }
                num = std::stod(num_str);
                terms.push_back(Term(num, op));
                sequence = sequence.substr(end);
            }
            return terms;
        }

    private:
        double value = std::numeric_limits<int>::min();
        Operator op = Operator::BLANK;
};

double apply_op(double left, Term::Operator op, double right)
{
    if(op == Term::ADD) return left + right;
    else if(op == Term::SUBTRACT) return left - right;
    else if(op == Term::MULTIPLY) return left * right;
    else if(op == Term::DIVIDE) return left / right;
    return right;
}

/**
 * collapse two terms together using the operator in secondary and the numbers from each.
 */
Term collapse_term(Term primary, Term secondary)
{
    if(primary.get_value() == std::numeric_limits<int>::min()) return secondary;
    if(secondary.get_value() == std::numeric_limits<int>::min()) return primary;
    double value = apply_op(primary.get_value(), secondary.get_operator(), secondary.get_value());
    primary.set_number(value);
    return primary;
}

double solve1(std::string equation)
{
    std::vector<Term> terms = Term::parse_term_sequence(equation);
    if(terms.empty()) return std::numeric_limits<int>::min();
    double result = 0;
    Term processing;
    for(int i = 0; i < terms.size(); i++)
    {
        Term current = terms[i];
        Term next = (i + 1 < terms.size() ? terms[i + 1] : Term());
        // apply the current term to processing
        processing = collapse_term(processing, current);
        if(next.get_value() == std::numeric_limits<int>::min() || next.get_operator() == Term::ADD 
        || next.get_operator() == Term::SUBTRACT)
        {
            result = apply_op(result, processing.get_operator(), processing.get_value());
            processing = Term();
        }
    }
    return result;
}

double solve2(std::string equation)
{
    double result = 0;
    // todo
    return result;
}

/**
 * Calculator: Given an arithmetic equation consisting of positive integers, +, -, * and /
 * (no parentheses), compute the result.
 * EXAMPLE:
 * Input: 2*3+5/6*3+15
 * Output: 23.5
 */
int main()
{
    std::cout << "Enter 1 to solve using solution #1 or any other number to solve using solution #2.\n";
    int method;
    std::cin >> method;
    std::cout << "Enter equation:\n";
    std::string equation;
    std::cin.ignore();
    std::getline(std::cin, equation);
    std::string equation_without_spaces = equation;
    equation_without_spaces.erase(std::remove(equation_without_spaces.begin(), 
    equation_without_spaces.end(), ' '), equation_without_spaces.end());
    double result = (method == 1 ? solve1(equation_without_spaces) : solve2(equation_without_spaces));
    std::cout << equation << " = " << result << '\n';
}