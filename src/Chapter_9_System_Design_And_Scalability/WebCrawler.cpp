#include <iostream>

/**
 * If you were designing a web crawler, how would you avoid getting into infinite loops?
*/
int main() {
    std::cout << "Infinite loops occur when a cycle in a graph (where page is a node) occurs.\n"
                 "Detect cycles using a hash table where hash[v] = true after page v is visited.\n"
                 "Page v is defined with some sort of signature based on snippets of the content\n"
                 "and the page's URL. There should be a database which stores a list of items that\n"
                 "need to be crawled. On each iteration, the page with a highest priority is crawled.\n"
                 "Step 1; Open page, create signature based on content and URL.\n"
                 "Step 2: Query the db to see whether anything with this signature has been crawled recently.\n"
                 "Step 3: If sth with this signature has been recently crawled, insert this page back\n"
                 "        into the db at a low priority.\n"
                 "Step 4: If not, crawl the page and insert its links into the db.\n"
                 "Described solution will never finish crawling the web but it will avoid getting stuck in a\n"
                 "loop of pages. In order to have a possibility of finishing crawling the web we could set a\n"
                 "minimum priority that a page must have to be crawled.\n";
}
