//
//  ChildNumber.cpp
//  Test
//
//  Created by xgc on 12/20/17.
//  Copyright © 2017 xgc. All rights reserved.
//

#include "ChildNumber.hpp"
#include <assert.h>

const int ChildNumber::HARDENED_BIT = 0x80000000;
ChildNumber ChildNumber::ZERO(0);
ChildNumber ChildNumber::ONE(1);
ChildNumber ChildNumber::ZERO_HARDENED(0, true);
ChildNumber ChildNumber::LTC_HARDENED(2, true);

ChildNumber::ChildNumber(uint32_t childNumber)
{
    this->i = childNumber;
}

ChildNumber::ChildNumber(uint32_t childNumber, bool isHardened)
{
    //assert(hasHardenedBit(childNumber));
    i = isHardened ? (childNumber | HARDENED_BIT) : childNumber;
}


bool ChildNumber::isHardened() {
    return hasHardenedBit(i);
}

bool ChildNumber::hasHardenedBit(uint32_t a) {
    return (a & HARDENED_BIT) != 0;
}


uint32_t ChildNumber::num() {
    return i /*& (~HARDENED_BIT)*/;
}
