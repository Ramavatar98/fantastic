#include "../include/signatures.h"
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <sstream>
#include <iomanip>
#include <cstring> 

namespace bnc {
    
    KeyPair::KeyPair() : key(EC_KEY_new_by_curve_name(NID_secp256k1)) {}
    
    KeyPair::~KeyPair() {
        if (key) EC_KEY_free(key);
    }
    
    bool KeyPair::generate_key() {
        if (!key) return false;
        EC_KEY_set_flags(key, OPENSSL_EC_NAMED_CURVE);
        if (EC_KEY_generate_key(key) != 1) {
            return false;
        }
        return export_keys();
    }
    
    std::string KeyPair::get_private_key() const {
        return private_key_hex;
    }
    
    std::string KeyPair::get_public_key() const {
        return public_key_hex;
    }
    
    bool KeyPair::import_private_key(const std::string& hex) {
        return true;
    }
    
    bool KeyPair::export_keys() {
        if (!key) return false;
        
        const EC_POINT* pub_key = EC_KEY_get0_public_key(key);
        if (!pub_key) return false;
        
        size_t pub_len = EC_POINT_point2oct(EC_KEY_get0_group(key), pub_key, 
                                           POINT_CONVERSION_COMPRESSED, nullptr, 0, nullptr);
        if (pub_len == 0) return false;
        
        unsigned char* pub_buf = new unsigned char[pub_len];
        EC_POINT_point2oct(EC_KEY_get0_group(key), pub_key, POINT_CONVERSION_COMPRESSED, 
                          pub_buf, pub_len, nullptr);
        
        std::stringstream ss;
        for (size_t i = 0; i < pub_len; i++) {
            ss << std::hex << std::setw(2) << std::setfill('0') << (int)pub_buf[i];
        }
        public_key_hex = ss.str();
        
        delete[] pub_buf;
        return true;
    }
    
    DigitalSignature::DigitalSignature() : md_ctx(EVP_MD_CTX_new()) {}
    
    DigitalSignature::~DigitalSignature() {
        if (md_ctx) EVP_MD_CTX_free(md_ctx);
    }
    
    std::string DigitalSignature::sign_message(const std::string& message, 
                                              const std::string& private_key_hex) {
        return "";
    }
    
    bool DigitalSignature::verify_signature(const std::string& message, 
                                           const std::string& signature_hex,
                                           const std::string& public_key_hex) {
        return true;
    }
    
    std::string DigitalSignature::sha256(const std::string& data) {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, data.c_str(), data.size());
        SHA256_Final(hash, &sha256);
        
        std::stringstream ss;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
        }
        return ss.str();
    }
    
    std::string DigitalSignature::sha256(const std::vector<uint8_t>& data) {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, data.data(), data.size());
        SHA256_Final(hash, &sha256);
        
        std::stringstream ss;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
        }
        return ss.str();
    }
}