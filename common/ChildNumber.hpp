//
//  ChildNumber.hpp
//  Test
//
//  Created by xgc on 12/20/17.
//  Copyright © 2017 xgc. All rights reserved.
//

#ifndef ChildNumber_hpp
#define ChildNumber_hpp

#include <cstdint>

class ChildNumber {
public:
    ChildNumber(uint32_t childNumber);
    ChildNumber(uint32_t childNumber, bool isHardened);
    static bool hasHardenedBit(uint32_t a);
    bool isHardened();
    uint32_t num();
public:
    static const int HARDENED_BIT;
    static ChildNumber ZERO;
    static ChildNumber ONE;
    static ChildNumber ZERO_HARDENED;
    static ChildNumber LTC_HARDENED;
private:
    uint32_t i;
};

#endif /* ChildNumber_hpp */
