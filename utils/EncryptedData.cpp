//
//  EncryptedData.cpp
//  Test
//
//  Created by xgc on 12/19/17.
//  Copyright © 2017 xgc. All rights reserved.
//

#include "EncryptedData.h"


vector<uint8_t> EncryptedData::getIV()
{
    return initialisationVector;
}

void EncryptedData::setIV(vector<uint8_t> initialisationVector)
{
    this->initialisationVector = initialisationVector;
}

vector<uint8_t> EncryptedData::getEncryptedBytes()
{
    return encryptedBytes;
}

void EncryptedData::setEncryptedBytes(vector<uint8_t> encryptedBytes)
{
    this->encryptedBytes = encryptedBytes;
}
