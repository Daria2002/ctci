#include <iostream>

class BiNode
{
    public:
        BiNode() = default;
        BiNode(int val, BiNode *n1, BiNode *n2) : value(val), node1(n1), node2(n2) {}
        int value;
        BiNode *node1 = nullptr, *node2 = nullptr;
};

class NodePair
{
    public:
        NodePair() = default;
        NodePair(BiNode *h, BiNode *t) : head(h), tail(t) {}
        BiNode *head = nullptr, *tail = nullptr;
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

class Result2
{
    public:
        Result2() = default;
        Result2(bool n, BiNode *h) : is_null(n), head(h) {}
        bool is_null;
        BiNode *head;
};

BiNode* get_tail(BiNode *head)
{
    if(head == nullptr) return nullptr;
    // std::cout << "head val = " << head->value << '\n';
    while ((head->node2) != nullptr)
    {
        head = head->node2;
    }
    // std::cout << "tail value = " << head->value << '\n';
    if(head == nullptr) std::cout << "tail is nullptr\n";
    return head;
}

Result2 convert2(BiNode *root)
{
    if(root == nullptr) return Result2(true, new BiNode());
    Result2 part1(true, new BiNode());
    Result2 part2(true, new BiNode());
    if(root->node1 != nullptr)
    {
        part1 = convert2(root->node1);
        if(!part1.is_null)
        {
            // std::cout << "part1 = " << part1.head.value << '\n';
            concat(get_tail(part1.head), root);
        }
    }
    if(root->node2 != nullptr)
    {
        part2 = convert2(root->node2);
        if(!part2.is_null)
        {
            concat(root, part2.head);
        }
    }
    return part1.is_null ? Result2(false, root) : part1;
}

BiNode* convert_to_circular(BiNode *root)
{
    if(root == nullptr) return nullptr;
    BiNode* part1 = convert_to_circular(root->node1);
    BiNode* part3 = convert_to_circular(root->node2);
    if(part1 == nullptr && part3 == nullptr)
    {
        root->node1 = root;
        root->node2 = root;
        return root;
    }
    BiNode* tail = (part3 == nullptr) ? nullptr : part3->node1;
    // join left to root
    if(part1 == nullptr)
    {
        concat(part3->node1, root);
    }
    else 
    {
        concat(part1->node1, root);
    }
    // join right to root
    if(part3 == nullptr)
    {
        concat(root, part1);
    }
    else 
    {
        concat(root, part3);
    }
    // join right to root
    if(part1 != nullptr && part3 != nullptr)
    {
        concat(tail, part1);
    }
    return part1 == nullptr ? root : part1;
}

BiNode* convert3(BiNode *root)
{
    BiNode* head = convert_to_circular(root);
    // distroy circular list
    head->node1->node2 = nullptr;
    head->node1 = nullptr;
    return head;
}

void print_elements(BiNode *head)
{
    BiNode *tmp = head;
    std::cout << "List elements: ";
    while (tmp != nullptr)
    {
        std::cout << tmp->value << ", ";
        tmp = tmp->node2;
    }
    std::cout << '\n';
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
        print_elements(r.root.head);
    }

    else if(method == 2)
    {
        Result2 r = convert2(&node4);
        print_elements(r.head);
    }
    else 
    {
        BiNode* head = convert3(&node4);
        print_elements(head);
    }
}