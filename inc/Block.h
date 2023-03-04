#ifndef BLOCK_H
#define BLOCK_H

#include "Transaction.h"

#include <vector>
#include <string>
#include <iostream>
#include "Transaction.h"
#include "Hash.h"

using namespace std; // just for convenience

class Block {
private:
    vector<unsigned char> blockID;
    vector<unsigned char> prevHash;
    vector<Transaction> setOfTransactions;

public:
    // Constructor to initialize a block
    Block(vector<Transaction> setOfTransactions, vector<unsigned char> prevHash) {
        this->setOfTransactions = setOfTransactions;
        this->prevHash = prevHash;
        this->blockID = createBlockID();
    }

    // Creates a unique block ID using the transactions and previous hash
    vector<unsigned char> createBlockID() {
        // Concatenate transaction data and previous block hash
        vector<unsigned char> blockData;
        for (Transaction tx : setOfTransactions) {
            blockData.insert(blockData.end(), tx.getData().begin(), tx.getData().end());
        }
        blockData.insert(blockData.end(), prevHash.begin(), prevHash.end());

        // Compute block hash and use it as its ID
        return Hash::SHA256(blockData);
    }

    // Create a new block
    static Block createBlock(vector<Transaction> setOfTransactions, vector<unsigned char> prevHash) {
        Block newBlock(setOfTransactions, prevHash);
        return newBlock;
    }

    // Get the private member variables
    vector<unsigned char> getBlockID() {
        return blockID;
    }

    vector<unsigned char> getPrevHash() {
        return prevHash;
    }

    vector<Transaction> getSetOfTransactions() {
        return setOfTransactions;
    }

    // Convert the block object to a string representation
    string toString() {
        string blockStr = "";
        blockStr += "Block ID: ";
        for (unsigned char c : blockID) {
            blockStr += to_string(c);
        }
        blockStr += "\n";
        blockStr += "Previous block hash: ";
        for (unsigned char c : prevHash) {
            blockStr += to_string(c);
        }
        blockStr += "\n";
        blockStr += "Transactions:\n";
        for (Transaction tx : setOfTransactions) {
            blockStr += tx.toString();
            blockStr += "\n";
        }
        return blockStr;
    }

    // Print the block data to the console
    void print() {
        cout << toString() << endl;
    }
};

#endif // BLOCK_H