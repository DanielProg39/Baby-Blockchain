#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <map>

#include "Block.h"
#include "Transaction.h"
#include "Account.h"
#include "Hash.h"
#include "Operation.h"

class Blockchain {
private:
    std::map<Account, int> coinDatabase;
    std::vector<Block> blockHistory;
    std::vector<Transaction> txDatabase;
    uint faucetCoins;

public:
    // Constructor for Blockchain, which initializes the private member variables
    Blockchain() : coinDatabase(), blockHistory(), txDatabase(), faucetCoins(0) {}

    // Initialize a new blockchain
    static Blockchain initBlockchain() {
        Blockchain blockchain;
        std::vector<EC_KEY*> keys1 = {nullptr};
        std::vector<EC_KEY*> keys2 = {nullptr};
        Account account1 = Account("A1", keys1);
        Account account2 = Account("A2", keys2);
        blockchain.getTokenFromFaucet(account1, 500);
        blockchain.getTokenFromFaucet(account2, 1000);
        std::vector<Transaction> transactions;
        Transaction transaction1 = Transaction::createTransaction({Operation::createOperation(account1, account2, 200, std::vector<unsigned char>())}, 0);
        Transaction transaction2 = Transaction::createTransaction({Operation::createOperation(account1, account2, 100, std::vector<unsigned char>())}, 0);
        transactions.push_back(transaction1);
        transactions.push_back(transaction2);
        Block block = Block::createBlock(transactions, blockchain.blockHistory.back().getBlockID());
        blockchain.validateBlock(block);
        return blockchain;
    }

    // Adds coins from the faucet to the account
    void getTokenFromFaucet(Account account, int amount) {
        if (amount <= faucetCoins) {
            coinDatabase[account] = coinDatabase[account] + amount;
            faucetCoins -= amount;
            account.updateBalance(account.getBalance() + amount);
        } else {
            std::cout << "Not enough coins in faucet." << std::endl;
        }
    }

    // Validate a new block and add it to the blockchain if it passes the validation
    void validateBlock(Block block) {
        // Check that the block contains a link to the last actual block in history
        if (blockHistory.size() > 0 && block.getPrevHash() != blockHistory.back().getBlockID()) {
            std::cout << "Block validation failed: invalid previous hash." << std::endl;
            return;
        }

        // Check that transactions in the block have not been added to history yet
        for (const auto& tx : block.getSetOfTransactions()) {
            if (std::find(txDatabase.begin(), txDatabase.end(), tx) != txDatabase.end()) {
                std::cout << "Block validation failed: transaction already exists in history." << std::endl;
                return;
            }
        }

        // Check that the block does not contain conflicting transactions
        for (auto& tx : block.getSetOfTransactions()) {
            for (auto& op : tx.getSetOfOperations()) {
                if (coinDatabase[op.getSender()] < op.getAmount()) {
                    std::cout << "Block validation failed: sender does not have enough balance for transaction." << std::endl;
                    return;
                }
            }
        }

        // Check every operation in a transaction
        for (auto& tx : block.getSetOfTransactions()) {
            for (auto& op : tx.getSetOfOperations()) {
                // Signature verification
                if (!op.verifyOperation()) {
                    std::cout << "Block validation failed: operation signature verification failed." << std::endl;
                    return;
                }

                // Verify that the operation does not spend more coins than is available on the balance of the sender's account
                if (coinDatabase[op.getSender()] < op.getAmount()) {
                    std::cout << "Block validation failed: operation spends more coins than available on sender's account." << std::endl;
                    return;
                }

                // Update the balance of the sender's account
                coinDatabase[op.getSender()] -= op.getAmount();
                op.getReceiver().updateBalance(op.getReceiver().getBalance() + op.getAmount());
            }
        }

        // Block validation successful, add transactions to database and add block to history
        for (const auto& tx : block.getSetOfTransactions()) {
            txDatabase.push_back(tx);
        }
        blockHistory.push_back(block);
        std::cout << "Block validation successful." << std::endl;
    }

    // Get the current state of accounts and balances
    void showCoinDatabase() const {
        for (const auto& entry : coinDatabase) {
            std::cout << "Account: " << entry.first.getaccountID() << ", Balance: " << entry.second << std::endl;
        }
    }
};

#endif // BLOCKCHAIN_H