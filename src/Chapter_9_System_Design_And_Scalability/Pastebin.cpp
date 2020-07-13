#include <iostream>

/**
 * Design a system like Pastebin, where a user can enter a piece 
 * of text and get a randomlygenerated URL to access it.
*/
int main() {
    std::cout << "Step 1: Scope of this problem\n"
                 "  -No user accounts and editing docs.\n"
                 "  -Tracks analytics of how many times each page is accessed.\n"
                 "  -Old docs get deleted after not being accessed for a sufficiently long period of time.\n"
                 "  -Document URL should not be easily guessed.\n"
                 "  -The system has a frontend as well as API.\n"
                 "  -The analytics for each URL can be accessed through a stats link on each page.\n"
                 "Step 2: Make reasonable assumptions\n"
                 "  -the system gets heavy traffic and contains many millions of docs.\n"
                 "  -traffic is not equally distributed across docs. Some docs get much more access than others.\n"
                 "Step 3: Draw the major components\n"
                 "  -documents can be stored in db or on a file. It's probably better to store them on a file because\n"
                 "   documents can be large and searching capabilities won't be needed.\n"
                 "  -There will be a simple db that looks up the location of each file and then access the file.\n"
                 "  -There will also be a db that tracks analytics. It will add each visit as a row in a db and\n"
                 "   than to access the stats of each visit, we pull the relevant data in from this db.\n"
                 "Step 4: Identify the key issues\n"
                 "  -reading data from the filesystem is relatively slow compared with reading from data in memory.\n"
                 "  -there should be a cache to store some docs that are much more frequently accessed than others.\n"
                 "  -since there is no option to edit docs there is no need to worry about invalidating this cache.\n"
                 "  -for retrieving docs from db introduce sharding the database using some mapping from the url\n"
                 "   (i.e. the url's hash code modulo some integer), which will allow us to quickly locate the db which\n"
                 "   contains this file. There is also approach where we could skip the db entirely and just let a hash\n"
                 "   of the URL indicate which server contains the doc. Potential issue: adding servers - difficult to\n"
                 "   redistribute docs. Generating URLs should provide difficult access without being provided the link.\n"
                 "  -one approach for generating URL is to generate a random GUID (globally unique identifier)-128-bit value\n"
                 "  -GUID is not strictly guaranteed to be unique but it has low enough odds of collision that we can treat it\n"
                 "   as unique. The drawback of this is that such a URL is not very pretty to the user. We could hash it to a\n"
                 "   smaller value, but then that increases the odds of collision.\n"
                 ;
}
