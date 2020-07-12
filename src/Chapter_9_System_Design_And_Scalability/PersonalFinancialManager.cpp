#include <iostream>

/**
 * Explain how you would design a personal financial manager (likeMint.com).This system would connect
 * to your bank accounts, analyze your spending habits, and make recommendations.
 */
int main() {
    std::cout << "Personal Financial Manager is write-heavy problem because there is a lot of data coming in,\n"
                 "but it's rarely being read. As much work as possible should be done asynchronously. It means\n"
                 "that we can execute multiple things at the time and we don't have to finish executing the current\n"
                 "thing in order to move on to the next one.\n"
                 "Step 1: Scope the Problem\n"
                 "  - the financial history includes outgoing money, incoming money and current money\n"
                 "  - just websit for now, although it could potentially be a mobile app as well\n"
                 "  - email notification on regular basis or on certain conditions (spending over a certain treshold...)\n"
                 "Step 2: Make Reasonable Assumptions\n"
                 "  - the system is write-heavy because a typical user may take several new transactions daily, although few\n"
                 "    users would access the website more than once a week. In fact, for many users, their primary interaction\n"
                 "    might be through email alerts.\n"
                 "  - the bank won't push data to our system, we will need to pull data from the banks.\n"
                 "  - alerts on users exceeding budgets do not neeed to be sent instantaneously. It's pretty safe for them to be\n"
                 "    up to 24 hours delayed.\n"
                 "Step 3: Draw Major Components\n"
                 "  bank data synchronizer -> raw transaction data -> categorizer -> categorized transactions -> budget analyzer -> budget data\n"
                 "                                                                                     -----------> frontend <--------\n"
                 "  - the bank data is pulled at periodic times and stored in some list of raw, unprocessed transactions. This data is then pushed to\n"
                 "    the categorizer which assigns each transaction to the category and stores these transactions in another datastore called\n"
                 "    categorized transactions. The budget analyzer pulls in the categorized transactions and updates each user's budget per\n"
                 "    category, and stores the user's budget. The frontend pulls data from both categorized transactions datastore as well as from the\n"
                 "    budget datastore. A user could also interact with the frontend by changing the budget or the categorization of their transactions.\n"
                 "Step 4: Identify the Key Issues\n"
                 "  - This is data-heavy system and since we want it to feel snappy (sharp, clever) and responsive we'll want as much processing as possible\n"
                 "    to be asynchronous. There should be at least one task queue where we can queue up work that needs to be done (pulling in new bank data,\n"
                 "    re-analyzing budgets, and categorizing new bank data). A task queue system should be able to prioritize some task types over others,"
                 "    but we wouldn't want a low priority tasks to \"starve\" because there is always higher priority tasks. There will probably be a large\n "
                 "    number of inactive users - users who signed up once and then haven't touched the system since. The syste should entirely remove them or\n"
                 "    deprioritize their accounts. The biggest bottleneck in system like this is a massive amount of data that needs to be pulled and analyzed.\n"
                 "    ";
}