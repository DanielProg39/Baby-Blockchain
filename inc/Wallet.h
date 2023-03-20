#ifndef WALLET_H
#define WALLET_H

#include <iostream>
#include <vector>
#include <sstream>
#include <openssl/ec.h>
#include <openssl/ecdsa.h>
#include <openssl/obj_mac.h>
#include <openssl/bio.h>
#include <openssl/pem.h>

// Forward declarations
#include "Block.h"
#include "Transaction.h"
#include "Account.h"
#include "Hash.h"
#include "Operation.h"

class Wallet {
private:
    std::vector<KeyPair> keyPairs;
    std::vector<Transaction> userTxes;
    Account account;

public:
    // Constructor to create a wallet
    Wallet(std::string id, std::vector<EC_KEY*> keys) : account(Account::createAccount(id, keys)) {
    }
    // Function to generate a new key pair and add it to the wallet
    void generateNewKeyPair() {
        KeyPair newKeyPair;
        keyPairs.push_back(newKeyPair);

        // Create a transaction to send the new public key to the account
        Transaction tx = createTransaction(account.getaccountID(), 0);
        tx.addOutput(newKeyPair.getPublicKey(), 0);
        tx.signInput(0, account.getPublicKeys(), newKeyPair.getPrivateKey());
        tx.validateTransaction();
        userTxes.push_back(tx);

        // TODO: Initiate a search for transactions related to the new public key
    }

    // Function to create a new transaction
    void createTransaction(std::string accID, uint amount) {
        Transaction tx = createOperation(accID, amount, userTxes.size()).toTransaction();
        tx.signInput(0, account.getPublicKeys(), keyPairs[0].getPrivateKey());
        tx.verify();
        userTxes.push_back(tx);
    }

    // Function to get the current balance of the wallet
    uint getBalance() {
        int balance = 0;
        for (const auto& tx : userTxes) {
            balance += tx.getBalance(account.getaccountID());
        }
        account.updateBalance(balance);
        return balance;
    }

    // Function to print the current balance of the wallet
    void printBalance() {
        std::cout << "Current balance: " << getBalance() << std::endl;
    }

    // Function to sign data with a private key
    std::vector<uint8_t> signData(std::vector<uint8_t> data, uint index) {
        ECDSA_SIG* signature = ECDSA_do_sign(data.data(), data.size(), keyPairs[index].getPrivateKey());
        std::vector<uint8_t> r(BN_num_bytes(signature->r)), s(BN_num_bytes(signature->s));
        BN_bn2bin(signature->r, r.data());
        BN_bn2bin(signature->s, s.data());
        std::vector<uint8_t> result(r.size() + s.size());
        std::copy(r.begin(), r.end(), result.begin());
        std::copy(s.begin(), s.end(), result.begin() + r.size());
        ECDSA_SIG_free(signature);
        return result;
    }

    // Function to create a new operation
    Operation createOperation(std::string recipient, uint amount, uint index) {
        Operation op(account.getaccountID(), recipient, amount, getBalance(), index);
        std::vector<uint8_t> signature = signData;
        op.setSignature(signature);
        return op;
    }
};

#endif // WALLET_H