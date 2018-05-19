//
//  KeyCrypterScrypt.h
//  Test
//
//  Created by xgc on 12/18/17.
//  Copyright © 2017 xgc. All rights reserved.
//

#ifndef KeyCrypterScrypt_h
#define KeyCrypterScrypt_h

#include "SecureRandom.h"
#include "Common.h"

class KeyCrypterScrypt
{
public:
    static void randomSeed(uint8_t seed[16], int len);
    static int randomSalt(uint8_t* salt, int len);
    bool deriveKey(string password, uint8_t* salt , int len, uint32_t N, uint32_t R, uint32_t P, vector<uint8_t>& vecIv);
    int encrypt(uint8_t* plainBytes, int plainLen, uint8_t* encryptBytes, vector<uint8_t> vecIv);
    int decrypt(uint8_t* encryptBytes, int encryptLen, uint8_t* plainBytes, vector<uint8_t> vecIv);
    bool getKeyParameter(KeyParameter& key);
    bool getIV(IV& iv);
public:
    static const int KEY_LENGTH;
    static const int BLOCK_LENGTH;
    static const int SALT_LENGTH;
    static const int LOGN;
    static const int R;
    static const int p;
    
private:
    static SecureRandom secureRandom;
    KeyParameter key;
    //IV iv;
};


#endif /* KeyCrypterScrypt_h */
