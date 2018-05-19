//
//  Netparams.cpp
//  Test
//
//  Created by xgc on 12/19/17.
//  Copyright © 2017 xgc. All rights reserved.
//

#include "Netparams.hpp"

NetParams::NetParams()
{
    ApiVersion = 0x01;
    version = 0x02;
    P = 1;
    R = 8;
    N = 32768;
}

string NetParams::getSymbol()
{
    return symbol;
}

CoinType NetParams::getCoinType()
{
    return coinType;
}

NetworkType NetParams::getNetType()
{
    return nettype;
}

KeyPath NetParams::getKeyPath()
{
    return keyPath;
}

uint32_t NetParams::getVersion()
{
    return version;
}

uint32_t NetParams::getHDprivate()
{
    return HDprivate;
}

uint32_t NetParams::getHDpublic()
{
    return HDpublic;
}

uint32_t NetParams::getP2KH()
{
    return P2KH;
}

uint32_t NetParams::getP2SH()
{
    return P2SH;
}

uint8_t NetParams::getKeyprefixes()
{
    return keyprefixes;
}

uint16_t NetParams::getApiVersion()
{
    return ApiVersion;
}

uint32_t NetParams::getN()
{
    return N;
}

uint32_t NetParams::getR()
{
    return R;
}

uint32_t NetParams::getP()
{
    return P;
}

void NetParams::setSymbol(string symbol)
{
    this->symbol = symbol;
}

void NetParams::setCoinType(CoinType coinType)
{
    this->coinType = coinType;
}

void NetParams::setNetType(NetworkType netType)
{
    this->nettype = netType;
}

void NetParams::setKeyPath(KeyPath keyPath)
{
    this->keyPath = keyPath;
}

void NetParams::setVersion(uint32_t version)
{
    this->version = version;
}

void NetParams::setHDprivate(uint32_t HDprivate)
{
    this->HDprivate = HDprivate;
}

void NetParams::setHDpublic(uint32_t HDpublic)
{
    this->HDpublic = HDpublic;
}

void NetParams::setP2KH(uint32_t P2KH)
{
    this->P2KH = P2KH;
}

void NetParams::setP2SH(uint32_t P2SH)
{
    this->P2SH = P2SH;
}

void NetParams::setKeyprefixes(uint8_t keyprefixes)
{
    this->keyprefixes = keyprefixes;
}

void NetParams::setApiVersion(uint16_t ApiVersion)
{
    this->ApiVersion = ApiVersion;
}

void NetParams::setN(uint32_t N)
{
    this->N = N;
}

void NetParams::setR(uint32_t R)
{
    this->R = R;
}

void NetParams::setP(uint32_t P)
{
    this->P = P;
}
