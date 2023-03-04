#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <sstream>
#include <vector>
#include <openssl/ec.h>

class Account {
private:
    std::string accountID;
    std::vector<EC_KEY*> publicKeys;
    int balance;

public:
    // Constructor to create an account
    Account(std::string id, std::vector<EC_KEY*> keys) {
        accountID = id;
        publicKeys = keys;
        balance = 0;
    }

    // Function for creating a new account
    static Account createAccount(std::string id, std::vector<EC_KEY*> keys) {
        Account newAccount(id, keys);
        return newAccount;
    }

    // Add a public key to the account
    void addKeyToAccount(EC_KEY* key) {
        publicKeys.push_back(key);
    }

    // Update the balance of the account
    void updateBalance(int newBalance) {
        balance = newBalance;
    }

    // Get the current balance of the account
    int getBalance() const {
        return balance;
    }

    // Get the private member variables
    std::vector<EC_KEY*> getPublicKeys() const {
        return publicKeys;
    }

    std::string getaccountID() const {
        return accountID;
    }

    int getBalance() {
        return balance;
    }

    // Convert the account object to a string
    std::string toString() const {
        std::stringstream ss;
        ss << "Account ID: " << accountID << "\n";
        ss << "Public Keys: [";
        for (const auto& key : publicKeys) {
            char buf[256];
            EC_KEY_print_fp(stdout, key, 0);
            ss << buf << ", ";
        }
        ss << "]\n";
        ss << "Balance: " << balance << "\n";
        return ss.str();
    }

    // Print the account details
    void print() const {
        std::cout << toString();
    }
};

#endif // ACCOUNT_H