#include <iostream>

/**
 * A large eCommerce company wishes to list the best-selling products, overall and by category. 
 * For example, one product might be the #1056th best-selling product overall but the #13th 
 * best-selling product underSportsEquipment and the #24th best-selling product underSafety. 
 * Describe how you would design this system.
 */
int main() {
    std::cout << "Step 1: Scope the problem\n"
        	     "  - assumption 1: design the components relevant to this question, and\n"
                 "                  not the entire eCommerce system.\n"
                 "  - assumption 2: sales rank is defined as the total sales over the past week\n"
                 "  - assumption 3: product can be in multiple categories and there is no concept\n"
                 "                  of subcategories\n"
                 "Step 2: Make Reasonable Assumptions\n"
                 "  - assumption 1: the stats do not need to be 100% up-to-date\n"
                 "  - assumption 2: the precision is important for the most popular items (i.e. data\n"
                 "                  can be up to an hour old), but a small degree of error is okay\n"
                 "                  for the less popular items (i.e. data can be up to one day old).\n"
                 "  - assumption 3: time range for the most popular items doesn't need to be precisely\n"
                 "                  the last seven days (168 hours). It's okay sometimes 150 hours.\n"
                 "  - assumption 4: categorizations are based strictly on the origin of the transaction\n"
                 "                  (i.e., the seller's name, not the price or date)\n"
                 "Step 3: Draw the Major Components\n"
                 "  - draw a design of a basic, naive system that describes the major components.\n"
                 "    |purchase system| (orders added to db)-> |db| (sort)-> |sales rank data| -> |frontend|\n"
                 "  - every order is stored in db as soon as it comes. Every hour or so, we pull the sales\n"
                 "    data from the db by the category and compute the total sales, sort it, and store it\n"
                 "    in some sort of sales rank data cache (probably held in memory). The frontend pulls\n"
                 "    the sales rank from this table, rather than hitting the standard db and doing its\n"
                 "    own analytics.\n"
                 "Step 4: Identify the Key Issues\n"
                 "  - Analytics are Expensive: we need the table that contains columns: Prod ID, Total\n"
                 "                             Sun, Mon, Tues, Wed, Thurs, Fri, Sat where we will clear\n"
                 "                             out the corresponding day of the week and update value.\n"
                 "                             There will also be a separate table to store the associations\n"
                 "                             of product IDs and categories (2 columns). To get the sales\n"
                 "                             rank per category, we'll need to join these tables.\n"
                 "  - Database Writes are Very Frequent: Hitting the db is still very frequently, we'll\n"
                 "                                       probably want to batch up (make efficient, avoid repeating)\n"
                 "                                       the db writes. Idea is to store purchases in some sort of\n"
                 "                                       in-memory cache instead of immediately committing each purchase\n"
                 "                                       to the db. Periodically, we'll process the log/cache data and\n"
                 "                                       update db. Problem can occur if we process one product's logs before\n"
                 "                                       another's and re-run the stats in between, we could create a bias in the\n"
                 "                                       data. Solution is dividing up the in-memory cache by some time period\n"
                 "  - Joins are Expensive: Instead of executing expensive join for each category, we could execute one join of\n"
                 "                         products and categories, such that each product will be listed once per category.\n"
                 "                         Rather than running thousands of queries (one for each category), we could sort the data\n"
                 "                         on the category first and then the sales volume. Than, if we walked those results, we would get\n"
                 "                         the sales rank for each category. We would also need to do one sort of the entire table on just\n"
                 "                         sales number, to get the overall rank\n"
                 "  - Database Queries might Still Be Expensive: if the queries and writes get very expensive, we should consider\n"
                 "                                               forgoing (go without) a db entirely and just using log files.\n"
                 "                                               Using log files instead of db would allow us to take advantage of\n"
                 "                                               sth like MapReduce. MapReduce process: input -> splitting -> mapping ->\n"
                 "                                               shuffling -> reducing -> final result. MapReduce is a software framework and\n"
                 "                                               programming model used for processing huge amounts of data. It contains of two\n"
                 "                                               important tasks, namely Map and Reduce. Map takes a set of data and converts\n"
                 "                                               it into another set of data, where individual elements are broken down into tuples.\n"
                 "                                               A purchase data is written to a simple text file with name containing the product ID\n"
                 "                                               and time stamp. Each category has its own directory and each purchase gets written to\n"
                 "                                               all the categories associated with that product. There are frequent jobs to merge files\n"
                 "                                               together by product id and time ranges, so that eventually all purchases in a given day\n"
                 "                                               or possibly hour were grouped together. To get the best-selling products within each\n"
                 "                                               category we just need to sort each dir. The advantage of this system is that we can easily\n"
                 "                                               divide up the files across multiple servers, as they aren't dependent on each other.\n"
                 "                                               Overall ranking is calculated merging the most popular items from each category in a\n"
                 "                                               pairwise fashion. So, two categories get paired together and we merge most popular items\n"
                 "                                               (the first 100 or so). Then we move onto the next pair.\n";
}
