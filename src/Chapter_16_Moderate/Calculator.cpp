#include <iostream>
#include <unordered_map>
#include <vector>
#include <limits>
#include <algorithm>
#include <stack>

enum Operator
{
    ADD, SUBTRACT, MULTIPLY, DIVIDE, BLANK
};

class Term
{
    public:
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

double apply_op(double left, Operator op, double right)
{
    if(op == Operator::ADD) return left + right;
    else if(op == Operator::SUBTRACT) return left - right;
    else if(op == Operator::MULTIPLY) return left * right;
    else if(op == Operator::DIVIDE) return left / right;
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
        if(next.get_value() == std::numeric_limits<int>::min() || next.get_operator() == Operator::ADD || 
        next.get_operator() == Operator::SUBTRACT)
        {
            result = apply_op(result, processing.get_operator(), processing.get_value());
            processing = Term();
        }
    }
    return result;
}

int priority_of_operator(Operator op)
{
    if(op == Operator::ADD || op == Operator::SUBTRACT) return 1;
    else if(op == Operator::MULTIPLY || op == Operator::DIVIDE) return 2;
    return 0;
}

void collapse_top(Operator future_top, std::stack<double>& number_stack, std::stack<Operator>& operator_stack)
{
    while (operator_stack.size() >= 1 && number_stack.size() >= 2)
    {
        Operator op = operator_stack.top();
        if(priority_of_operator(future_top) <= priority_of_operator(op))
        {
            double second = number_stack.top();
            number_stack.pop();
            double first = number_stack.top();
            number_stack.pop();
            operator_stack.pop();
            double collapsed = apply_op(first, op, second);
            number_stack.push(collapsed);
            op = operator_stack.top();
        }
        else
        {
            break;
        }
    }
}

Operator parse_next_operator(std::string equation, int offset)
{
    if(offset < equation.length())
    {
        char op = equation[offset];
        switch (op)
        {
        case '+': return Operator::ADD;
        case '-': return Operator::SUBTRACT;
        case '/': return Operator::DIVIDE;
        case '*': return Operator::MULTIPLY;
        }
    }
    return Operator::BLANK;
}

int parse_next_number(std::string equation, int offset)
{
    std::string str = "";
    while (offset < equation.length() && equation[offset] >= '0' && equation[offset] <= '9')
    {
        str += equation[offset];
        offset++;
    }
    return std::stoi(str);
}

double solve2(std::string equation)
{
    std::stack<double> number_stack;
    std::stack<Operator> operator_stack;
    for(int i = 0; i < equation.length(); i++)
    {
        try
        {
            // get number and push
            int value = parse_next_number(equation, i);
            number_stack.push(value);
            // move to the operator
            i += std::to_string(value).length();
            if(i >= equation.length()) break;
            // get operator, collapse top as needed, push operator
            Operator op = parse_next_operator(equation, i);
            collapse_top(op, number_stack, operator_stack);
            operator_stack.push(op);
        }
        catch(const std::exception& e)
        {
            return std::numeric_limits<int>::min();
        }
    }
    // final collapse
    collapse_top(Operator::BLANK, number_stack, operator_stack);
    if(number_stack.size() == 1 && operator_stack.size() == 0) return number_stack.top();
    return 0;
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