#include <iostream>

class BiNode
{
    public:
        BiNode() = default;
        BiNode(int val, BiNode *n1, BiNode *n2) : value(val), node1(n1), node2(n2) {}
        int value;
        BiNode *node1, *node2;
};

class NodePair
{
    public:
        NodePair() = default;
        NodePair(BiNode *h, BiNode *t) : head(h), tail(t) {}
        BiNode *head, *tail;
};

void concat(BiNode *n1, BiNode *n2)
{
    n1->node2 = n2;
    n2->node1 = n1;
}

bool is_null(NodePair p)
{
    return p.head != nullptr && p.tail != nullptr;
}

class Result
{
    public:
        Result() = default;
        Result(bool n, NodePair r) : is_null(n), root(r) {}
        bool is_null;
        NodePair root;
};

Result convert1(BiNode *root)
{
    if(root == nullptr) return Result(true, NodePair());
    // std::cout << "root val = " << root->value << '\n';
    // if(root->node1 != nullptr)
    //     std::cout << "root node1 = " << root->node1->value << '\n';
    // if(root->node2 != nullptr)
    //     std::cout << "root node2 = " << root->node2->value << '\n';
    Result part1 = convert1(root->node1);
    Result part2 = convert1(root->node2);
    if(!part1.is_null)
    {
        concat(part1.root.tail, root);
    }
    if(!part2.is_null)
    {
        concat(root, part2.root.head);
    }
    return Result(false, NodePair(part1.is_null ? root : part1.root.head, part2.is_null ? root : part2.root.tail));
}

/**
 * BiNode: Consider a simple data structure called BiNode, which has pointers to two other nodes. The
 * data structure BiNode could be used to represent both a binary tree (where node1 is the left node
 * and node2 is the right node) or a doubly linked list (where node1 is the previous node and node2
 * is the next node). Implement a method to convert a binary search tree (implemented with BiNode)
 * into a doubly linked list. The values should be kept in order and the operation should be performed
 * in place (that is, on the original data structure).
 */
int main()
{
    std::cout << "Enter 1 to solve using additional data structure, enter 2 to solve retrieving\n" 
    "the tail or any other number to solve building a circular linked list:\n";
    int method;
    std::cin >> method;
    // create tree
    BiNode node0(0, nullptr, nullptr);
    BiNode node1(1, &node0, nullptr);
    BiNode node3(3, nullptr, nullptr);
    BiNode node2(2, &node1, &node3);
    BiNode node6(6, nullptr, nullptr);
    BiNode node5(5, nullptr, &node6);
    BiNode node4(4, &node2, &node5);
    if(method == 1)
    {
        Result r = convert1(&node4);
        BiNode *tmp = r.root.head;
        std::cout << "List elements: ";
        while (tmp != nullptr)
        {
            std::cout << tmp->value << ", ";
            tmp = tmp->node2;
        }
        std::cout << '\n';
    }
    else if(method == 2)
    {
        // todo
    }
    else 
    {
        // todo
    }
}