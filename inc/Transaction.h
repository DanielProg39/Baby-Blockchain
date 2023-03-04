#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Operation.h"

class Transaction {
private:
    std::string transactionID;
    std::vector<Operation> setOfOperations;
    uint nonce;

public:
    // Constructor for Transaction
    Transaction(std::vector<Operation> operations, uint nonce) {
        setOfOperations = operations;
        this->nonce = nonce;

        // Calculate transaction ID
        std::string txData;
        for (const auto& op : setOfOperations) {
            txData += op.toString();
        }
        txData += std::to_string(nonce);

        // Compute SHA256 hash of transaction data
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256(reinterpret_cast<const unsigned char*>(txData.c_str()), txData.length(), hash);

        // Convert hash to hexadecimal string
        char hexHash[2 * SHA256_DIGEST_LENGTH + 1];
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            sprintf(hexHash + 2 * i, "%02x", hash[i]);
        }
        transactionID = std::string(hexHash, 2 * SHA256_DIGEST_LENGTH);
    }

    // Create Transaction
    static Transaction createTransaction(std::vector<Operation> setOfOperations, uint nonce) {
        return Transaction(setOfOperations, nonce);
    }

    // Returns the transaction data as a string, used to calculate the block hash
    std::string getData() const {
        std::string txData;
        for (const auto& op : setOfOperations) {
            txData += op.toString();
        }
        txData += std::to_string(nonce);
        return txData;
    }

    // Validate the transaction by checking each operation
    bool validateTransaction() {
        for (Operation op : setOfOperations) {
            if (!op.verifyOperation()) {
                return false;
            }
        }

        return true;
    }

    // Get the private member variables
    std::string getTransactionID() {
        return transactionID;
    }

    std::vector<Operation> getSetOfOperations() {
        return setOfOperations;
    }

    uint getNonce() {
        return nonce;
    }

    // Return a string representation of the transaction
    std::string toString() const {
        std::stringstream ss;
        ss << "Transaction ID: " << transactionID << "\n";
        ss << "Operations:\n";
        for (const auto& op : setOfOperations) {
            ss << op.toString() << "\n";
        }
        ss << "Nonce: " << nonce << "\n";
        return ss.str();
    }

    // Print the transaction to the console
    void print() const {
        std::cout << toString();
    }
};

#endif // TRANSACTION_H