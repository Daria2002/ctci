#include <iostream>

void print_proposal_no1() {
    std::cout << "==============\n"
                 "Approach no.1:\n"
                 "==============\n"
                 "Keep data in simple txt and let clients download the data through\n"
                 "FTP (File transfer protocol, i.e. Filezilla).\n"
                 "Pros: Files can be easily viewed and backed up.\n"
                 "Cons: Complex parsing.\n";
}

void print_proposal_no2() {
    std::cout << "==============\n"
                 "Approach no.2:\n"
                 "==============\n"
                 "Use a standard SQL database and let the clients plug directly into that.\n"
                 "Pros: Easy to do queries, rolling back(reverting), backing up data and\n"
                 "security could be provided using standard db features, easy for the clients\n"
                 "to integrate into existing apps.\n"
                 "Cons: SQL backend is too complex for supporting a feed of a few bits of info, \n"
                 "it's difficult for humans to be able to read it, so there should be additional\n"
                 "layer to view and maintain the data (increases implementation const), security\n"
                 "and expensive(inefficient) queries.\n";
}

void print_proposal_no3() {
    std::cout << "==============\n"
                 "Approach no.3:\n"
                 "==============\n"
                 "Use XML because our data has fixed format and size(company_name, open, high, low, closing_price).\n"
                 "XML is a standard data model to share and distribute data.\n"
                 "Pros: Easy to distribute and read by both machines and humans, most languages have a\n"
                 "library to perform XML parsing, so it's reasonably easy for clients to implement, easy\n"
                 "to add new data(just add new node), it's possible to use existing tools for backing\n"
                 "up the data (we don't need to implement our own backup tool).\n"
                 "Cons: Using XML files sends the clients all the information, even if they only want, \n"
                 "a part of it. Also, performing any queries requires parsing the entire file.\n";
}

/**
 * Imagine you are building some sort of service that will be called by up to 1,000 client applications
 * to get simple end-of-day stock price information (open, close, high, low). You may assume that you 
 * already have the data, and you can store it in any format you wish. How would you design the client-facing 
 * service that provides the information to client applications? You are responsible for the development, rollout, 
 * and ongoing monitoring and maintenance of the feed. Describe the different methods you considered and why you would 
 * recommend your approach. Your service can use any technologies you wish, and can distribute the information to the 
 * client applications inany mechanism you choose.
 */
int main() {
    std::cout << "==========\n"
                 "Stock Data\n"
                 "==========\n";
    std::cout << "Important aspects: Client Ease of Use, Ease for Ourselfs,\n"
                 "Flexibility for Future Demands and Scalability and Efficiency.\n";
    print_proposal_no1();
    print_proposal_no2();
    print_proposal_no3();
    std::cout << "===================================================\n"
                 "Extra option: implement with or without web service \n"
                 "(i.e. SOAP - simple object access protocol, based on XML):\n"
                 "Pros: adds layer to our work, easier integration for user, additional security.\n"
                 "Cons: clients will be limited to grabbing the data only how we expect them to.\n";
}
