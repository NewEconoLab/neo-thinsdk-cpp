//
//  BtcvoutForm.cpp
//  Test
//
//  Created by xgc on 12/22/17.
//  Copyright © 2017 xgc. All rights reserved.
//

#include "BtcvoutForm.hpp"

BtcvoutForm::BtcvoutForm(string hash, uint64_t value, int n, bool coinBase)
{
    this->hash = hash;
    this->value = value;
    this->n = n;
    this->coinBase = coinBase;
}

string BtcvoutForm::getHash()
{
    return this->hash;
}

void BtcvoutForm::setHash(string hash)
{
    this->hash = hash;
}

uint64_t BtcvoutForm::getValue()
{
    return this->value;
}

void BtcvoutForm::setValue(uint64_t value)
{
    this->value = value;
}

int BtcvoutForm::getN()
{
    return n;
}

void BtcvoutForm::setN(int n)
{
    this->n = n;
}

bool BtcvoutForm::getCoinBase()
{
    return this->coinBase;
}

void BtcvoutForm::setCoinBase(bool coinBase)
{
    this->coinBase = coinBase;
}
