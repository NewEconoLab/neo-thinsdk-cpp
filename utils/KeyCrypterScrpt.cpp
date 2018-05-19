//
//  KeyCrypterScrpt.cpp
//  Test
//
//  Created by xgc on 12/18/17.
//  Copyright © 2017 xgc. All rights reserved.
//

#include <stdio.h>

#include "KeyCrypterScrypt.h"
#include "lib/scryptenc/scryptenc.h"
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>


const int KeyCrypterScrypt::KEY_LENGTH = 32;
const int KeyCrypterScrypt::BLOCK_LENGTH = 16;
const int KeyCrypterScrypt::SALT_LENGTH = 8;
const int KeyCrypterScrypt::LOGN = 15;
const int KeyCrypterScrypt::R = 8;
const int KeyCrypterScrypt::p = 1;

SecureRandom KeyCrypterScrypt::secureRandom;

void KeyCrypterScrypt::randomSeed(uint8_t seed[16], int len)
{
    secureRandom.random_number(seed, len);
}

int KeyCrypterScrypt::randomSalt(uint8_t* salt, int len)
{
    return random_salt(salt, len);
}

static double log2ex(double N) {
    return log10(N) / log10(2);
}

bool KeyCrypterScrypt::deriveKey(string password, uint8_t* salt , int len, uint32_t nN, uint32_t nR, uint32_t nP, vector<uint8_t>& vecIv)
{
    int res = 0;
    
    uint8_t dk[64] = {0};

    int logN = (int)log2ex(nN);

    res = drive_key((const uint8_t *)password.c_str(), password.length(),
                    logN, nR, nP,
                  salt, SALT_LENGTH,
                  dk);
    if(res != 0)
    {
        return false;
    }

    
    key.assign(dk, dk + 32);
    //iv.assign(dk + 32, dk + 48);
    vecIv.assign(dk + 32, dk + 48);
    
    return true;
}

int encrypt_my2(const unsigned char *plaintext, int plaintext_len, unsigned char *key,
               unsigned char *iv, unsigned char *ciphertext)
{
    EVP_CIPHER_CTX *ctx;

    int len;

    int ciphertext_len;

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new()))
        return -1;

    /* Initialise the encryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits */
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        return -1;

    /* Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_EncryptUpdate can be called multiple times if necessary
     */
    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
        return -1;
    ciphertext_len = len;

    /* Finalise the encryption. Further ciphertext bytes may be written at
     * this stage.
     */
    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) return -1;
    ciphertext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;

}


int
scryptenc_buf2(const uint8_t * inbuf, size_t inbuflen, uint8_t * outbuf, size_t * outlen,
              uint8_t * key_enc, uint8_t * iv)
{

    /* Encrypt data. */

    size_t len = encrypt_my2(inbuf, inbuflen, key_enc, iv, outbuf);

    *outlen = len;

    return (0);
}



int KeyCrypterScrypt::encrypt(uint8_t* plainBytes, int plainLen, uint8_t* encryptBytes, vector<uint8_t> vecIv)
{
    size_t outlen = 0;

    int res = scryptenc_buf2((const uint8_t *)plainBytes, (size_t)plainLen, encryptBytes, (size_t *)&outlen,
                             (uint8_t *)&key[0], (uint8_t *)&vecIv[0]);
    if(res < 0)
    {
        return res;
    }
    
    return outlen;
}

int KeyCrypterScrypt::decrypt(uint8_t* encryptBytes, int encryptLen, uint8_t* plainBytes, vector<uint8_t> vecIv)
{
    size_t outlen = 0;
    int res = scryptdec_buf((const uint8_t *)encryptBytes, (size_t)encryptLen, plainBytes, (size_t *)&outlen,
                            (uint8_t *)&key[0], (uint8_t *)&vecIv[0]);
    if(res < 0)
    {
        return res;
    }
    
    return outlen;
}

bool KeyCrypterScrypt::getKeyParameter(KeyParameter& keyParam)
{
    keyParam = key;
    return true;
}

bool KeyCrypterScrypt::getIV(IV& ivParam)
{
    //ivParam = iv;
    return true;
}
