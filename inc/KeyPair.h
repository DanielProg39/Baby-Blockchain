#ifndef KEYPAIR_H
#define KEYPAIR_H

#include <iostream>
#include <openssl/pem.h>

class KeyPair {
private:
    EC_KEY *privateKey;
    EC_KEY *publicKey;

public:
    // Constructor to generate a new key pair
    KeyPair() {
        privateKey = EC_KEY_new_by_curve_name(NID_secp256k1);
        EC_KEY_generate_key(privateKey);
        publicKey = EC_KEY_dup(privateKey);
    }

    // Destructor to free the memory used by the key pair
    ~KeyPair() {
        EC_KEY_free(privateKey);
        EC_KEY_free(publicKey);
    }

    // Function to return the private key
    EC_KEY* getPrivateKey() const {
        return privateKey;
    }

    // Function to return the public key
    EC_KEY* getPublicKey() const {
        return publicKey;
    }

    // Function to convert the key pair to a string
    std::string toString() const {
        std::string privateKeyStr, publicKeyStr;

        // Convert private key to PEM format
        BIO *privateKeyBio = BIO_new(BIO_s_mem());
        PEM_write_bio_ECPrivateKey(privateKeyBio, privateKey, NULL, NULL, 0, NULL, NULL);
        char *privateKeyData;
        long privateKeyLen = BIO_get_mem_data(privateKeyBio, &privateKeyData);
        privateKeyStr = std::string(privateKeyData, privateKeyLen);
        BIO_free(privateKeyBio);

        // Convert public key to PEM format
        BIO *publicKeyBio = BIO_new(BIO_s_mem());
        PEM_write_bio_EC_PUBKEY(publicKeyBio, privateKey);
        char *publicKeyData;
        long publicKeyLen = BIO_get_mem_data(publicKeyBio, &publicKeyData);
        publicKeyStr = std::string(publicKeyData, publicKeyLen);
        BIO_free(publicKeyBio);

        // Return the string representation of the key pair
        return privateKeyStr + "\n" + publicKeyStr;
    }

    // Function to print the key pair
    void printKeyPair() const {
        std::cout << std::endl << toString() << std::endl;
    }
};

#endif // KEYPAIR_H