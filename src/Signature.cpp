#include "../inc/blockchain.h"
#include "../src/KeyPair.cpp"

class Signature {
    private:
        ECDSA_SIG *signature;

    public:
        // Function to generate a digital signature for a message using a private key
        static std::vector<unsigned char> signData(EC_KEY* privateKey, const std::vector<unsigned char>& message) {
            // Create a new ECDSA signature using the private key and the message
            ECDSA_SIG* sig = ECDSA_do_sign(message.data(), message.size(), privateKey);
            // Get the length of the signature
            unsigned int sigLen = i2d_ECDSA_SIG(sig, nullptr);
            // Create a vector of unsigned char to store the signature
            std::vector<unsigned char> signature(sigLen);
            unsigned char* sig_data = signature.data();
            // Convert the ECDSA signature to a byte array
            i2d_ECDSA_SIG(sig, &sig_data);
            // Free the ECDSA signature object
            ECDSA_SIG_free(sig);
            
            return signature;
        }

        // Function to verify a digital signature for a message using a public key
        static bool verifySignature(EC_KEY* publicKey, const std::vector<unsigned char>& signature, const std::vector<unsigned char>& message) {
            // Create a new ECDSA signature object
            ECDSA_SIG* sig = ECDSA_SIG_new();
            // Get the data from the signature vector
            const unsigned char* sig_data = signature.data();
            // Convert the byte array signature to an ECDSA signature object
            d2i_ECDSA_SIG(&sig, &sig_data, signature.size());
            // Verify the signature using the public key and the message
            int result = ECDSA_do_verify(message.data(), message.size(), sig, publicKey);
            // Free the ECDSA signature object
            ECDSA_SIG_free(sig);

            // Return the result of the verification (1 for valid signature, 0 for invalid signature)
            return result == 1;
        }

        // Function to print the signature
        void printSignature() const {
            std::cout << "Signature: " << signature << std::endl;
        }
};
