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
};

bool operator==(const DocPair &docPair1, const DocPair& docPair2)
{
    return (docPair1.id1 == docPair2.id1 && docPair1.id2 == docPair2.id2) || 
    (docPair1.id2 == docPair2.id1 && docPair1.id1 == docPair2.id2);
}

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

std::unordered_map<int, std::vector<int>> preprocess(const std::vector<Document>& documents)
{
    std::unordered_map<int, std::vector<int>> map_element_to_documents;
    for(Document doc : documents)
    {
        for(int el : doc.elements)
        {
            if(map_element_to_documents.find(doc.document_id) == map_element_to_documents.end())
            {
                map_element_to_documents[el] = std::vector<int>();
            }
            map_element_to_documents[el].push_back(doc.document_id);
        }
    }
    return map_element_to_documents;
}

std::vector<int> get_similar_documents(const Document& doc, const std::unordered_map<int, std::vector<int>>& map_element_to_documents)
{
    std::vector<int> similar_documents;
    for(int i = 0; i < doc.elements.size(); i++)
    {
        std::vector<int> document_ids = map_element_to_documents.at(doc.elements[i]);
        for(int j = 0; j < document_ids.size(); j++)
        {
            if(document_ids[j] == doc.document_id) continue;
            similar_documents.push_back(document_ids[j]);
        }
    }
    return similar_documents;
}

std::unordered_map<DocPair, double, Hash> similarities_little_optimization(const std::vector<Document>& documents)
{
    std::unordered_map<int, std::vector<int>> map_element_to_documents = preprocess(documents);
    std::unordered_map<DocPair, double, Hash> similarities;
    for(int i = 0; i < documents.size(); i++)
    {
        std::vector<int> similar_documents = get_similar_documents(documents[i], map_element_to_documents);
        for(int k = 0; k < similar_documents.size(); k++)
        {
            DocPair docPair(documents[i].document_id, similar_documents[k]);
            if(similarities.find(docPair) != similarities.end()) continue; // already in map
            Document doc2 = std::find_if(documents.begin(), documents.end(), 
            [&](const Document& doc) {return doc.document_id == similar_documents[k];})[0]; // [0] - there is only one element 
            similarities[docPair] = calculate_similarity_bf(documents[i], doc2);
        }
    }
    return similarities;
}

std::unordered_map<DocPair, double, Hash> similarities_optimized(const std::vector<Document>& documents)
{
    std::unordered_map<int, std::vector<int>> map_element_to_documents = preprocess(documents);
    std::unordered_map<DocPair, int, Hash> intersection_count;
    for(int i = 0; i < documents.size(); i++)
    {
        std::vector<int> similar_documents = get_similar_documents(documents[i], map_element_to_documents);
        for(int k = 0; k < similar_documents.size(); k++)
        {
            DocPair docPair(documents[i].document_id, similar_documents[k]);
            intersection_count[docPair]++;
        }
    }
    std::unordered_map<DocPair, double, Hash> similarities;
    for(auto& element : intersection_count)
    {
        DocPair doc_pair = element.first;
        int count = element.second;
        Document doc1 = std::find_if(documents.begin(), documents.end(), 
            [&](const Document& doc) {return doc.document_id == doc_pair.id1;})[0];
        Document doc2 = std::find_if(documents.begin(), documents.end(), 
            [&](const Document& doc) {return doc.document_id == doc_pair.id2;})[0];
        similarities[doc_pair] = count*1.0/(doc1.elements.size() + doc2.elements.size() - count);
    }
    return similarities;
}

class Element
{
    public:
        int word, doc_id;
        Element() = default;
        Element(int w, int id) : word(w), doc_id(id) {}
};

bool operator<(const Element& el1, const Element& el2) {
    return el1.word < el2.word;
}

std::vector<Element> sort_words(const std::vector<Document>& documents)
{
    std::vector<Element> elements;
    for(Document doc : documents)
    {
        for(int el : doc.elements)
        {
            elements.push_back(Element(el, doc.document_id));
        }
    }
    std::sort(elements.begin(), elements.end());
    return elements;
}

void increment(std::unordered_map<DocPair, int, Hash>& intersections, const int id1, const int id2)
{
    intersections[DocPair(id1, id2)]++;
}

std::unordered_map<DocPair, int, Hash> calculate_intersections(const std::vector<Element>& elements)
{
    std::unordered_map<DocPair, int, Hash> intersections;
    for(int i = 0; i < elements.size(); i++)
    {
        Element left = elements[i];
        for(int j = i + 1; j < elements.size(); j++)
        {
            Element right = elements[j];
            if(left.word != right.word) break;
            increment(intersections, left.doc_id, right.doc_id);
        }
    }
    return intersections;
}

std::unordered_map<DocPair, double, Hash> intersections_to_similarities(const std::vector<Document>& documents, 
const std::unordered_map<DocPair, int, Hash>& intersections)
{
    std::unordered_map<DocPair, double, Hash> similarities;
    for(auto& element : intersections)
    {
        DocPair doc_pair = element.first;
        int count = element.second;
        Document doc1 = std::find_if(documents.begin(), documents.end(), 
            [&](const Document& doc) {return doc.document_id == doc_pair.id1;})[0];
        Document doc2 = std::find_if(documents.begin(), documents.end(), 
            [&](const Document& doc) {return doc.document_id == doc_pair.id2;})[0];
        similarities[doc_pair] = count*1.0/(doc1.elements.size() + doc2.elements.size() - count);
    }
    return similarities;
}

std::unordered_map<DocPair, double, Hash> similarities_alternative_optimized(const std::vector<Document>& documents)
{
    std::vector<Element> elements = sort_words(documents);
    std::unordered_map<DocPair, int, Hash> intersections = calculate_intersections(elements);
    std::unordered_map<DocPair, double, Hash> similarities = intersections_to_similarities(documents, intersections);
    return similarities;
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