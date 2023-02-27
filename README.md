# Baby Blockchain
A very simple payment blockchain implementation (without decentralization and consensus, only basic mechanics)

------------

## Overview

A "baby blockchain" is a simplified version of a traditional blockchain system that focuses on the basic mechanics of blockchain technology. The system is developed using C++ programming language and includes several classes that manage the different components of the blockchain, such as hash functions, digital signatures, keys, accounts, operations, transactions, blocks, and nodes. Unlike a full-fledged blockchain, it does not require a decentralized network of nodes or consensus mechanisms.

### Content

- A database to store the transactions and user information
- A system for accessing and managing the transactions
- Cryptographic algorithms for securing the transactions and protecting against fraud
- A payment gateway for processing payments
- A system for managing user accounts

### Product features

- Secure transactions through the use of cryptographic algorithms
- An interface for easy management of transactions
- Payment processing capabilities for efficient and convenient transactions

### Security requirements

- Confidentiality of personal and financial information
- Tamper-proof transactions with integrity maintained
- High availability to ensure the system is accessible and reliable at all times

### Restrictions

- Lack of decentralization and consensus mechanisms compared to a full-fledged blockchain
- Limited scalability, which may require future scaling efforts to handle high volumes of transactions.

## Technical details

The system is developed using C++ programming language and includes several classes to manage the different components of the blockchain.

The **Hash** class provides a wrapper for using a hash function, which is an essential component of the blockchain technology. The hash function is used to generate a unique representation of data, known as a hash, that serves as a fingerprint of the data. This hash is used to link the blocks in a blockchain, ensuring the integrity of the data stored in the blockchain.

The **Signature** class provides a wrapper for using a digital signature, which is used to verify the authenticity of transactions in the blockchain. Digital signatures are generated using public key cryptography, and they allow users to sign their transactions with a unique digital signature that is tied to their specific account.

The **KeyPair** class is responsible for working with keys, which are used to encrypt and decrypt data in the blockchain. A key pair consists of a public key and a private key, and they are used to sign transactions and verify digital signatures, respectively.

The **Account class** is used to manage a wallet, create operations, and sign data. An account is tied to a specific public key, and it is used to track the balance of coins in the blockchain. Users can create operations, such as payments, and sign the data associated with these operations using their private key.

The **Operation** class allows users to create payment operations, which are used to transfer coins from one account to another. These operations are stored in the blockchain as part of a transaction.

The **Transaction** class allows users to form transactions that contain user payments. A transaction is a collection of operations that are verified and processed by the blockchain network.

The **Block** class allows users to form blocks, which are collections of transactions that are verified and processed by the network. Each block contains a unique hash that links it to the previous block in the blockchain, forming a chain of blocks.

The **Blockchain** class allows users to form a blockchain, which is a database of coins and existing transactions. The blockchain is maintained by nodes in the network, and it is used to store and verify transactions.

The **Node** class allows users to maintain one node in the network. The node is responsible for processing the blockchain and has network interfaces that allow it to communicate with other nodes in the network.

The **UserApplication** class allows users to run an application that maintains a digital wallet. The wallet is used to generate and store keys, form new transactions, and check the status of transactions.
