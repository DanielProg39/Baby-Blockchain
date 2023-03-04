#ifndef HASH_H
#define HASH_H

#include <vector>
#include <openssl/pem.h>

class Hash {
public:
    // Generate a SHA256 hash of a vector of bytes
    static std::vector<unsigned char> SHA256(std::vector<unsigned char> data) {
        std::vector<unsigned char> hash(SHA256_DIGEST_LENGTH);
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, data.data(), data.size());
        SHA256_Final(hash.data(), &sha256);
        return hash;
    }
};

#endif // HASH_H