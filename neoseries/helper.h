
#ifndef helper_hpp
#define helper_hpp

#include "ecc.h"
#include <bitcoin/bitcoin.hpp>
#include <string>

using namespace bc;
using namespace bc::wallet;
using namespace std;

#define SCRIPT_HASH_LENGTH 20
#define NEO_ADDRESS_VERSION 0x17
#define NEO_PRIVATE_VERSION 0x80
#define NEO_PRIVATE_SENTINEL 0x01

vector<uint8_t> getScriptFromPublicKey(uint8_t p_publicKey[ECC_BYTES + 1]);

short_hash getScriptHashFromScript(data_slice script);

string getAddressFromScriptHash(short_hash scripthash);

string getWifFromPrivateKey(uint8_t p_privateKey[ECC_BYTES]);

short_hash getPublicKeyHashFromAddress(string address);

ec_secret getPrivateKeyFromWif(string wif);

string getAddressFromPublicKey(uint8_t p_publicKey[ECC_BYTES + 1]);

bool Sign(vector<uint8_t>& message, vector<uint8_t>& prikey, vector<uint8_t>& signature);

bool VerifySignature(vector<uint8_t>& message, vector<uint8_t>& signature, vector<uint8_t>& pubkey);

#endif
