//
//  coin_code.cpp
//  Test
//
//  Created by xgc on 12/24/17.
//  Copyright © 2017 xgc. All rights reserved.
//

#include "coin_code.hpp"

Prefixes::Prefixes(uint32_t bip44_code,uint32_t HDprivate, uint32_t HDpublic, uint32_t P2KH, uint32_t P2SH, uint8_t keyprefixes, uint32_t version)
{
    this->bip44_code  = bip44_code;
    this->HDprivate = HDprivate;
    this->HDpublic = HDpublic;
    this->P2KH = P2KH;
    this->P2SH = P2SH;
    this->keyprefixes = keyprefixes;
    this->version = version;
}

Prefixes coin_code::BTC(0x80000000, 0x0488ADE4, 0x0488B21E, 0x00, 0x05, 128, 2);
Prefixes coin_code::tBTC(0x80000001, 0x04358394, 0x043587CF, 0x6f, 0xC4, 239, 2);
Prefixes coin_code::LTC(0x80000002, 0x0488ADE4, 0x0488B21E, 0x30, 0x32, 176, 2);
Prefixes coin_code::tLTC(0x80000001, 0x04358394, 0x043587CF, 0x6f, 0x3A, 239, 2);
Prefixes coin_code::DOGE(0x80000003, 0x02fac398, 0x02facafd, 0x1e, 0x16, 158, 2);
Prefixes coin_code::tDOGE(0x80000001, 0x04358394, 0x043587cf, 0x71, 0xc4, 241, 2);
Prefixes coin_code::SBTC(0x80000000, 0x0488ADE4, 0x0488B21E, 0x00, 0x05, 128, 2);
Prefixes coin_code::tSBTC(0x80000001, 0x04358394, 0x043587CF, 0x6f, 0xC4, 239, 2);
Prefixes coin_code::WBTC(0x80000000, 0x0488ADE4, 0x0488B21E, 0x00, 0x05, 128, 2);
Prefixes coin_code::tWBTC(0x80000001, 0x04358394, 0x043587CF, 0x6f, 0xC4, 239, 2);
Prefixes coin_code::ZEC(0x80000085, 0x0488ADE4, 0x0488B21E, 0x1CB8, 0x1CBD, 0x80, 1);
Prefixes coin_code::tZEC(0x80000001, 0x04358394, 0x043587CF, 0x1D25, 0x1CBA,0xEF, 1);
Prefixes coin_code::DSH(0x80000005, 0x0488ADE4, 0x0488B21E, 0x4C, 0x10, 204, 2);
Prefixes coin_code::tDSH(0x80000001, 0x04358394, 0x043587CF, 0x8C, 0x13, 239, 2);
Prefixes coin_code::BCH(0x80000091, 0x0488ADE4, 0x0488B21E, 0x00, 0x05, 128, 2);
Prefixes coin_code::tBCH(0x80000001, 0x04358394, 0x043587CF, 0x6f, 0xC4, 239, 2);
Prefixes coin_code::QTUM(0x800008fd, 0x0488ADE4, 0x0488B21E, 0x3A, 0x32, 128, 2);
Prefixes coin_code::tQTUM(0x80000001, 0x04358394, 0x043587CF, 0x78, 0x6E, 239, 2);
Prefixes coin_code::LBTC(0x80000000, 0x0488ADE4, 0x0488B21E, 0x00, 0x05, 128, 0xff01);
Prefixes coin_code::tLBTC(0x80000001, 0x04358394, 0x043587CF, 0x6f, 0xC4, 239, 0xff01);
Prefixes coin_code::WICC(0x80000000, 0x4c233f4b, 0x4c1d3d5f, 73, 51, 153, 1);
Prefixes coin_code::tWICC(0x80000001, 0x7d5c5a26, 0x7d573a2c, 135, 88, 210, 1);