
#include "helper.h"
#include <string.h>

vector<uint8_t> getScriptFromPublicKey(uint8_t p_publicKey[ECC_BYTES + 1])
{
    uint8_t p_script[ECC_BYTES + 3] = {0};

    p_script[0] = ECC_BYTES + 1;
    memcpy(p_script + 1, p_publicKey, ECC_BYTES + 1);
    p_script[ECC_BYTES + 2] = 172;

    vector<uint8_t> tmp(p_script, p_script + ECC_BYTES + 3);
    //data_slice script(tmp);
    return tmp;
}

short_hash getScriptHashFromScript(data_slice script)
{
    hash_digest hd = sha256_hash(script);
    return ripemd160_hash(hd);
}

string getAddressFromScriptHash(short_hash scripthash)
{
    int size = scripthash.size();
    if(size != 20) {
        return "";
    }

    return encode_base58(wrap(NEO_ADDRESS_VERSION, scripthash));
}

string getWifFromPrivateKey(uint8_t p_privateKey[ECC_BYTES])
{
    ec_secret secret;
    std::memcpy(secret.data(), p_privateKey, ECC_BYTES);
    wif_compressed wif;
    const auto prefix = to_array(NEO_PRIVATE_VERSION);
    const auto compressed = to_array(NEO_PRIVATE_SENTINEL);
    build_checked_array(wif, { prefix, secret, compressed });
    return encode_base58(wif);
}

bool is_neo_address(data_slice decoded)
{
    return (decoded.size() == payment_size) && verify_checksum(decoded);
}


short_hash getPublicKeyHashFromAddress(string address)
{
    payment decoded;
    if (!decode_base58(decoded, address) || !is_neo_address(decoded))
        return{};
    if(decoded[0] != NEO_ADDRESS_VERSION)
        return {};

    short_hash pkhash;
    std::memcpy(pkhash.data(), decoded.data() + 1, SCRIPT_HASH_LENGTH);

    return pkhash;
}

bool is_neo_wif(data_slice decoded)
{
    const auto size = decoded.size();
    if (size != wif_compressed_size)
        return false;

    if (!verify_checksum(decoded))
        return false;

    return (size == wif_uncompressed_size) ||
           decoded.data()[1 + ec_secret_size] == NEO_PRIVATE_SENTINEL;
}

ec_secret getPrivateKeyFromWif(string wif)
{
    data_chunk decoded;
    if (!decode_base58(decoded, wif) || !is_neo_wif(decoded))
        return {};

    if(decoded[0] != NEO_PRIVATE_VERSION || decoded[33] != NEO_PRIVATE_SENTINEL)
        return {};

    ec_secret secret;
    std::memcpy(secret.data(), decoded.data() + 1, ECC_BYTES);

    return secret;
}

string getAddressFromPublicKey(uint8_t p_publicKey[ECC_BYTES + 1])
{
    vector<uint8_t> vScript;
    vScript = getScriptFromPublicKey(p_publicKey);
    short_hash scriptHash = getScriptHashFromScript(vScript);

    return getAddressFromScriptHash(scriptHash);
}
//int ecdsa_sign(const uint8_t p_privateKey[ECC_BYTES], const uint8_t p_hash[ECC_BYTES], uint8_t p_signature[ECC_BYTES*2]);
bool Sign(vector<uint8_t>& message, vector<uint8_t>& prikey, vector<uint8_t>& signature)
{
    uint8_t prikey_array[ECC_BYTES] = {0};
    std::memcpy(prikey_array, &prikey[0], ECC_BYTES);

    data_slice ds(message);
    hash_digest hd = sha256_hash(ds);

    uint8_t p_hash[ECC_BYTES] = {0};
    std::memcpy(p_hash, hd.data(), hd.size());

    uint8_t p_signature[ECC_BYTES * 2] = {0};

    int ret = ecdsa_sign(prikey_array, p_hash, p_signature);
    if(ret == 0)
        return false;
    signature.assign(p_signature, p_signature + ECC_BYTES * 2);
    return true;
}

//int ecdsa_verify(const uint8_t p_publicKey[ECC_BYTES+1], const uint8_t p_hash[ECC_BYTES], const uint8_t p_signature[ECC_BYTES*2]);
bool VerifySignature(vector<uint8_t>& message, vector<uint8_t>& signature, vector<uint8_t>& pubkey)
{
    uint8_t p_publicKey[ECC_BYTES + 1] = {0};
    std::memcpy(p_publicKey, &pubkey[0], ECC_BYTES + 1);

    uint8_t p_signature[ECC_BYTES * 2] = {0};
    std::memcpy(p_signature, &signature[0], ECC_BYTES * 2);

    data_slice ds(message);
    hash_digest hd = sha256_hash(ds);
    uint8_t p_hash[ECC_BYTES] = {0};
    std::memcpy(p_hash, hd.data(), hd.size());

    int ret = ecdsa_verify(p_publicKey, p_hash, p_signature);
    if(ret == 0)
        return false;

    return true;
}
