#ifndef OPERATION_H
#define OPERATION_H

#include "KeyPair.h"
#include "Account.h"
#include <iomanip>

class Operation {
private:
    Account sender;
    Account receiver;
    uint amount;
    std::vector<unsigned char> signature;

public:
    // Constructor that initializes the private member variables
    Operation(Account sender, Account receiver, uint amount, std::vector<unsigned char> signature)
        : sender(sender), receiver(receiver), amount(amount), signature(signature) {}

    // Create an Operation object
    static Operation createOperation(Account sender, Account receiver, uint amount, std::vector<unsigned char> signature) {
        return Operation(sender, receiver, amount, signature);
    }

    // Verify the operation
    bool verifyOperation() {
        // Verify that sender has enough balance
        if (sender.getBalance() < amount) {
            return false;
        }

        // Verify the signature
        std::vector<EC_KEY*> publicKeys = sender.getPublicKeys();
        if (publicKeys.empty()) {
            return false;
        }
        EVP_PKEY* pkey = EVP_PKEY_new();
        EC_KEY* ecKey = publicKeys[0];
        if (!EVP_PKEY_set1_EC_KEY(pkey, ecKey)) {
            return false;
        }
        EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
        if (!mdctx) {
            return false;
        }
        if (!EVP_DigestVerifyInit(mdctx, nullptr, EVP_sha256(), nullptr, pkey)) {
            EVP_MD_CTX_free(mdctx);
            return false;
        }
        int balance = sender.getBalance();
        if (!EVP_DigestVerifyUpdate(mdctx, &balance, sizeof(int))) {
            EVP_MD_CTX_free(mdctx);
            return false;
        }
        if (!EVP_DigestVerifyUpdate(mdctx, &amount, sizeof(uint))) {
            EVP_MD_CTX_free(mdctx);
            return false;
        }
        if (!EVP_DigestVerifyUpdate(mdctx, &receiver, sizeof(Account))) {
            EVP_MD_CTX_free(mdctx);
            return false;
        }
        if (!EVP_DigestVerifyFinal(mdctx, signature.data(), signature.size())) {
            EVP_MD_CTX_free(mdctx);
            return false;
        }

        // Update balances
        sender.updateBalance(sender.getBalance() - amount);
        receiver.updateBalance(receiver.getBalance() + amount);

        return true;
    }

    // Get the private member variables
    Account getSender() {
        return sender;
    }

    Account getReceiver() {
        return receiver;
    }

    uint getAmount() {
        return amount;
    }

    std::vector<unsigned char> getSignature() {
        return signature;
    }

    // Convert the Operation object to a string
    std::string toString() const {
        std::stringstream ss;
        ss << "Operation:\n";
        ss << "Sender: " << sender.toString() << "\n";
        ss << "Receiver: " << receiver.toString() << "\n";
        ss << "Amount: " << amount << "\n";
        ss << "Signature: ";
        for (const auto& s : signature) {
            ss << std::hex << std::setw(2) << std::setfill('0') << (int)s;
        }
        ss << "\n";
        return ss.str();
    }

    // Print the Operation object as a string
    void print() const {
        std::cout << toString();
    }
};

#endif // OPERATION_H