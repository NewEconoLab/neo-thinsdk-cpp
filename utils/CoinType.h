//
//  CoinType.h
//  Test
//
//  Created by xgc on 12/18/17.
//  Copyright © 2017 xgc. All rights reserved.
//

#ifndef CoinType_h
#define CoinType_h

#include <string>
using namespace std;

enum CoinType {
    BTC = 1,
    NEO,
    GAS
};


enum NetworkType {
    MAIN = 1,
    TEST = 2,
    REGTEST = 3
};

class CoinSymbol {
public:
    static const std::string BTC;
    static const std::string NEO;
    static const std::string GAS;
};


#endif /* CoinType_h */
