#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

class Document
{
    public:
        int document_id;
        std::vector<int> elements;
        Document() = default;
        Document(int id, std::vector<int> el) : document_id(id), elements(el) {}
        void sort()
        {
            std::sort(elements.begin(), elements.end());
        }
};

std::vector<Document> get_documents()
{
    std::vector<Document> documents;
    documents.push_back(Document(13, {14, 15, 100, 9, 3}));
    documents.push_back(Document(16, {32, 1, 9, 3, 5}));
    documents.push_back(Document(19, {15, 29, 2, 6, 8, 7}));
    documents.push_back(Document(24, {7, 10}));
    return documents;
}

class DocPair 
{
    public:
        int id1, id2;
        DocPair() = default;
        DocPair(int i1, int i2) : id1(i1), id2(i2) {}
        
        bool operator==(const DocPair &docPair) const
        {
            return (docPair.id1 == docPair.id2);
        }
};

int get_intersection_bf(const std::vector<int>& els1, const std::vector<int>& els2)
{   
    int intersection = 0;
    for(int el1 : els1)
    {
        intersection += std::count_if(els2.begin(), els2.end(), [&](int el) { return el == el1; });
    }
    return intersection;
}

double calculate_similarity_bf(const Document& doc1, const Document& doc2)
{
    const double _intersection = get_intersection_bf(doc1.elements, doc2.elements);
    const double _union = doc1.elements.size() + doc2.elements.size() - _intersection;
    return _intersection/_union;
}

double calculate_similarity_better_bf(const Document& doc1, const Document& doc2)
{
    double intersection = 0;
    std::unordered_set<int> set1 (doc1.elements.begin(), doc1.elements.end());
    for(auto el : doc2.elements)
    {
        if(set1.find(el) != set1.end()) intersection++;
    }
    double _union = doc1.elements.size() + doc2.elements.size() - intersection;
    return intersection/_union;
}

double calculate_similarity_sorted(const Document& doc1, const Document& doc2)
{
    std::vector<int> els1 = doc1.elements;
    std::vector<int> els2 = doc2.elements;
    els1.insert(els1.end(), els2.begin(), els2.end()); // merge
    std::sort(els1.begin(), els1.end());
    double intersection = 0;
    for(int i = 1; i < els1.size(); i++)
    {
        if(els1[i] == els1[i - 1]) intersection++;
    }
    double _union = doc1.elements.size() + doc2.elements.size() - intersection;
    return intersection/_union;
}

struct Hash
{
    std::size_t operator()(const DocPair& docPair) const
    {
        std::hash<int> hash_f;
        return hash_f(docPair.id1 * docPair.id2);
    }
};

std::unordered_map<DocPair, double, Hash> similarities_bf(const std::vector<Document>& documents,
double calculate_similarity(const Document&, const Document&))
{
    std::unordered_map<DocPair, double, Hash> similarities;
    for(int i = 0; i < documents.size(); i++)
    {
        for(int j = i + 1; j < documents.size(); j++)
        {
            similarities[DocPair(documents[i].document_id, documents[j].document_id)] = 
            calculate_similarity(documents[i], documents[j]);
        }
    }
    return similarities;
}

std::unordered_map<DocPair, double, Hash> similarities_little_optimization(std::vector<Document> documents)
{
    // todo
}

std::unordered_map<DocPair, double, Hash> similarities_optimized(std::vector<Document> documents)
{
    // todo
}

std::unordered_map<DocPair, double, Hash> similarities_alternative_optimized(std::vector<Document> documents)
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
    std::cout << 
    "Enter 1 for brute force, 2 for slightly better brute force, 3 for alternate slightly better brute force,\n"
    "4 for solution with a little optimization, 5 for optimized solution or any other number for alternative\n"
    "optimized solution:\n";
    int method;
    std::cin >> method;
    std::vector<Document> documents = get_documents();
    std::unordered_map<DocPair, double, Hash> similarities;
    if(method == 1)
    {
        similarities = similarities_bf(documents, calculate_similarity_bf);
    }
    else if(method == 2)
    {
        similarities = similarities_bf(documents, calculate_similarity_better_bf);
    }
    else if(method == 3)
    {
        similarities = similarities_bf(documents, calculate_similarity_sorted);
    }
    else if(method == 4)
    {
        similarities = similarities_little_optimization(documents);
    }
    else if(method == 5)
    {
        similarities = similarities_optimized(documents);
    }
    else 
    {
        similarities = similarities_alternative_optimized(documents);
    }
    std::cout << "ID1, ID2: SIMILARITY\n";
    for(auto const& [docPair, similarity] : similarities)
    {
        if(similarity == 0) continue;
        std::cout << docPair.id1 << ", " << docPair.id2 << ": " << similarity << '\n';
    }
}