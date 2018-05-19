//
//  BtWallet.cpp
//  Test
//
//  Created by xgc on 12/19/17.
//  Copyright © 2017 xgc. All rights reserved.
//

#include "BtWallet.hpp"

string BtWallet::getAddress()
{
    return address;
}

void BtWallet::setAddress(string address)
{
    this->address = address;
}

string BtWallet::getSymbol()
{
    return symbol;
}

void BtWallet::setSymbol(string symbol)
{
    this->symbol = symbol;
}

BtSeed* BtWallet::getBtSeed()
{
    return btSeed;
}

void BtWallet::setBtSeed(BtSeed* btSeed)
{
    this->btSeed = btSeed;
}
