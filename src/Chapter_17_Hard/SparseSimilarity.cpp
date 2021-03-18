#include <iostream>
#include <vector>

class Document
{
    public:
        int document_id;
        std::vector<int> elements;
        Document() = default;
        Document(int id, std::vector<int> el) : document_id(id), elements(el) {}
};

std::vector<Document> get_documents()
{
    std::vector<Document> documents;
    documents.push_back(Document(13, {14, 15, 100, 9, 3}));
    documents.push_back(Document(32, {32, 1, 9, 3, 5}));
    documents.push_back(Document(19, {15, 29, 2, 6, 8, 7}));
    documents.push_back(Document(24, {7, 10}));
    return documents;
}

class Similarity
{
    public:
        int id1, id2, similarity;
        Similarity() = default;
        Similarity(int i1, int i2, int s) : id1(i1), id2(i2), similarity(s) {}
};

std::vector<Similarity> similarities_bf(std::vector<Document> documents)
{
    // todo
}

std::vector<Similarity> similarities_better_bf(std::vector<Document> documents)
{
    // todo
}

std::vector<Similarity> similarities_little_optimization(std::vector<Document> documents)
{
    // todo
}

std::vector<Similarity> similarities_optimized(std::vector<Document> documents)
{
    // todo
}

std::vector<Similarity> similarities_alternative_optimized(std::vector<Document> documents)
{
    // todo
}

/**
 * Sparse Similarity: The similarity of two documents (each with distinct words) is defined
 * to be the size of the intersection divided by the size of the union. For example, if the 
 * documents consist of integers, the similarity of {1, 5, 3} and {1, 7, 2, 3} is 0.4, because
 * the intersection has size 2 and the union has size 5. 
 * 
 * We have a long list of documents (with distinct values and each with an associated ID) where 
 * the similarity is belived to be "sparse". That is, any two arbitrary selected documents are
 * very likely to have similarity 0. Design an algorithm that returns a list of pairs of document
 * IDs and associated similarity.
 * 
 * Print only the pairs with similarity greater than 0. Empty documents should not be printed at all.
 * For simplicity, you may assume each document is represented as an array of distinct integers.
 * 
 * EXAMPLE:
 * 
 * Input:
 *      13: {14, 15, 100, 9, 3}
 *      16: {32, 1, 9, 3, 5}
 *      19: {15, 29, 2, 6, 8, 7}
 *      24: {7, 10}
 * Output:
 *      ID1, ID2: SIMILARITY
 *      13, 19: 0.1
 *      13, 16: 0.25
 *      19, 24: 0.142857142857142857
 */  
int main()
{
    std::cout << "Enter 1 for brute force, 2 for slightly better brute force, 3 for solution with a little\n"
    "optimization, 4 for optimized solution or any other number for alternative optimized solution:\n";
    int method;
    std::cin >> method;
    std::vector<Document> documents = get_documents();
    std::vector<Similarity> similarities;
    if(method == 1)
    {
        similarities = similarities_bf(documents);
    }
    else if(method == 2)
    {
        similarities = similarities_better_bf(documents);
    }
    else if(method == 3)
    {
        similarities = similarities_little_optimization(documents);
    }
    else if(method == 4)
    {
        similarities = similarities_optimized(documents);
    }
    else 
    {
        similarities = similarities_alternative_optimized(documents);
    }
    std::cout << "ID1, ID2: SIMILARITY\n";
    for(Similarity s : similarities)
    {
        std::cout << s.id1 << ", " << s.id2 << ": " << s.similarity << '\n';
    }
}