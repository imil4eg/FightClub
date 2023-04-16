#include "OpenSSLPasswordHasher.hpp"

#include <openssl/evp.h>
#include <openssl/sha.h>

#include <sstream>
#include <iomanip>
#include <exception>

namespace FightClub::Server::User {
            
            std::string OpenSSLPasswordHasher::hash(const std::string& value) const
            {
                EVP_MD_CTX *mdctx;
	            if((mdctx = EVP_MD_CTX_new()) == NULL)
	            	throw std::runtime_error("couldn't create hash");

	            if(EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL) != 1)
	            	throw std::runtime_error("couldn't create hash");

	            if(EVP_DigestUpdate(mdctx, value.c_str(), EVP_MD_size(EVP_sha256())) != 1)
	            	throw std::runtime_error("couldn't create hash");

                unsigned char** digest = nullptr;
	            if((*digest = (unsigned char *)OPENSSL_malloc(EVP_MD_size(EVP_sha256()))) == NULL)
	            	throw std::runtime_error("couldn't create hash");

	            if(EVP_DigestFinal_ex(mdctx, *digest, nullptr) != 1)
	            	throw std::runtime_error("couldn't create hash");

	            EVP_MD_CTX_free(mdctx);

                return std::string(reinterpret_cast<char*>(digest));
            }
}