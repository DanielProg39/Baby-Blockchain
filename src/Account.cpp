#include "../inc/blockchain.h"

class Account {
private:
    std::string accountID;
    std::vector<EC_KEY> publicKeys;
    int balance;

public:
    // Constructor to create an account
    Account(std::string id, std::vector<EC_KEY> keys) {
        accountID = id;
        publicKeys = keys;
        balance = 0;
    }

    // Function to add a public key to the account
    void addKeyToAccount(EC_KEY* key) {
        publicKeys.push_back(*key);
    }

    // Function to update the balance of the account
    void updateBalance(int newBalance) {
        balance = newBalance;
    }

    // Function to get the current balance of the account
    int getBalance() const {
        return balance;
    }

    // Function to convert the account object to a string
    std::string toString() const {
        std::stringstream ss;
        ss << "Account ID: " << accountID << "\n";
        ss << "Public Keys: [";
        for (const auto& key : publicKeys) {
            char buf[256];
            EC_KEY_print_fp(stdout, &key, 0);
            ss << buf << ", ";
        }
        ss << "]\n";
        ss << "Balance: " << balance << "\n";
        return ss.str();
    }

    // Function to print the account details
    void print() const {
        std::cout << toString();
    }
};
