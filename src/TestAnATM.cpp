#include <iostream>

/**
 * How would you test an ATM in a distributed banking system? 
 */
int main() {
    std::cout << "Who is going to use? (anyone, blind people...), what are they going to use\n"
    "it for? (withdrawing money, transferring money, checking their balance...), what tools do\n"
    "we have to test? (do we have access to the code (black box) or just ATM (white box)?\n"
    "Test: logging in, withdrawing money, depositing money, checking balance, transferring money\n"
    "Probably it would be possible to mix manual and automated testing. Manual: low balance, new account\n"
    "nonexistent account... Automated: standard scenarious, test with fake accounts on a closed\n"
    "system. Prioritize security and reliability. Account must be protected and money must be\n"
    "properly accounted for.";
}
