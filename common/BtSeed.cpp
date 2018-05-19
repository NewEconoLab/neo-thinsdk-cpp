//
//  BtSeed.cpp
//  Test
//
//  Created by xgc on 12/19/17.
//  Copyright © 2017 xgc. All rights reserved.
//

#include "BtSeed.hpp"

BtSeed::BtSeed()
{
    
}

BtSeed::BtSeed(vector<uint8_t> seed, vector<string> mnemonicCode, EncryptedData encryptedMnemonicCode,
       EncryptedData encryptedSeed, long creationTimeSeconds, string pwdhash, vector<uint8_t> randomSalt)
{
    this->seed = seed;
    this->mnemonicCode = mnemonicCode;
    this->encryptedMnemonicCode = encryptedMnemonicCode;
    this->encryptedSeed = encryptedSeed;
    this->creationTimeSeconds = creationTimeSeconds;
    this->pwdhash = pwdhash;
    this->randomSalt = randomSalt;
}

vector<uint8_t> BtSeed::getRandomSalt()
{
    return randomSalt;
}

EncryptedData BtSeed::getEncryptedSeed()
{
    return encryptedSeed;
}

EncryptedData BtSeed::getEncryptedMnemonicCode()
{
    return encryptedMnemonicCode;
}

long BtSeed::getCreationTimeSeconds()
{
    return creationTimeSeconds;
}

void BtSeed::setRandomSalt(vector<uint8_t> randomSalt)
{
    this->randomSalt = randomSalt;
}

void BtSeed::setEncryptedSeed(EncryptedData encryptedSeed)
{
    this->encryptedSeed = encryptedSeed;
}

void BtSeed::setEncryptedMnemonicCode(EncryptedData encryptedMnemonicCode)
{
    this->encryptedMnemonicCode = encryptedMnemonicCode;
}

void BtSeed::setCreationTimeSeconds(long creationTimeSeconds)
{
    this->creationTimeSeconds = creationTimeSeconds;
}

void BtSeed::setSeed(vector<uint8_t> seed)
{
    this->seed = seed;
}

void BtSeed::setPwdhash(string pwdhash)
{
    this->pwdhash = pwdhash;
}

void BtSeed::setMnemonicCode(vector<string> mnemonicCode)
{
    this->mnemonicCode = mnemonicCode;
}

vector<uint8_t> BtSeed::getSeed()
{
    return this->seed;
}

string BtSeed::getPwdhash()
{
    return this->pwdhash;
}

vector<string> BtSeed::getMnemonicCode()
{
    return this->mnemonicCode;
}
