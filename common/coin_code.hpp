//
//  coin_code.hpp
//  Test
//
//  Created by xgc on 12/24/17.
//  Copyright © 2017 xgc. All rights reserved.
//

#ifndef coin_code_hpp
#define coin_code_hpp

#include <vector>
#include <bitcoin/bitcoin.hpp>
using namespace bc;

struct Prefixes
{
    uint32_t bip44_code;
    uint32_t HDprivate;
    uint32_t HDpublic;
    uint32_t P2KH;
    uint32_t P2SH;
    uint8_t keyprefixes;
    uint32_t version;
    
    Prefixes(uint32_t bip44_code,uint32_t HDprivate, uint32_t HDpublic, uint32_t P2KH, uint32_t P2SH, uint8_t keyprefixes, uint32_t version);
};

class coin_code
{
public:
    static Prefixes BTC;
    static Prefixes tBTC;
    static Prefixes LTC;
    static Prefixes tLTC;
    static Prefixes DOGE;
    static Prefixes tDOGE;
    static Prefixes SBTC;
    static Prefixes tSBTC;
    static Prefixes WBTC;
    static Prefixes tWBTC;
    static Prefixes ZEC;
    static Prefixes tZEC;
    static Prefixes DSH;
    static Prefixes tDSH;
    static Prefixes BCH;
    static Prefixes tBCH;
    static Prefixes QTUM;
    static Prefixes tQTUM;
    static Prefixes LBTC;
    static Prefixes tLBTC;
    static Prefixes WICC;
    static Prefixes tWICC;
};

#endif /* coin_code_hpp */
