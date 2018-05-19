//
//  Common.cpp
//  Test
//
//  Created by xgc on 12/21/17.
//  Copyright © 2017 xgc. All rights reserved.
//

#include <stdio.h>
#include "Common.h"
#include "../common/coin_code.hpp"



using namespace bc;
using namespace bc::wallet;


void split(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(std::string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));
        
        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}

string byte2Hex(hash_digest hd) {
    int size = hd.size();
    string res;
    char sz[3] = {0};
    for(int i = 0; i < size; i++) {
        sprintf(sz, "%02x", (uint8_t)hd[i]);
        res += sz;
    }
    
    return res;
}

void getSHA256(string& str, string& res)
{
    vector<uint8_t> ss(&str[0], &str[0] + str.length());
    hash_digest hd = sha256_hash(ss);
    
    res = byte2Hex(hd);
}

uint64_t getHdPrivateNet(CoinType coinType, NetworkType netType, NetParams netParams)
{
    uint64_t ret = 0;
    string coinName = netParams.getSymbol();
    switch(coinType) {
        case CoinType::BTC:
        case CoinType::SBTC:
        case CoinType::LTC:
        case CoinType::DOGE:
        case CoinType::WBTC:
        case CoinType::ZEC:
        case CoinType::DSH:
        case CoinType::BCH:
        case CoinType::QTUM:
            if(coinName == CoinSymbol::BTC) {
                if(netType == NetworkType::MAIN) {
                    ret = hd_private::to_prefixes(coin_code::BTC.HDprivate, coin_code::BTC.HDpublic);
                } else {
                    ret = hd_private::to_prefixes(coin_code::tBTC.HDprivate, coin_code::tBTC.HDpublic);
                }
            } else if(coinName == CoinSymbol::SBTC) {
                if(netType == NetworkType::MAIN) {
                    ret = hd_private::to_prefixes(coin_code::BTC.HDprivate, coin_code::BTC.HDpublic);
                } else {
                    ret = hd_private::to_prefixes(coin_code::tBTC.HDprivate, coin_code::tBTC.HDpublic);
                }
            } else if(coinName == CoinSymbol::LTC) {
                if(netType == NetworkType::MAIN) {
                    ret = hd_private::to_prefixes(coin_code::LTC.HDprivate, coin_code::LTC.HDpublic);
                } else {
                    ret = hd_private::to_prefixes(coin_code::tLTC.HDprivate, coin_code::tLTC.HDpublic);
                }
            } else if(coinName == CoinSymbol::DOGE) {
                if(netType == NetworkType::MAIN) {
                    ret = hd_private::to_prefixes(coin_code::DOGE.HDprivate, coin_code::DOGE.HDpublic);
                } else {
                    ret = hd_private::to_prefixes(coin_code::tDOGE.HDprivate, coin_code::tDOGE.HDpublic);
                }
            }else if(coinName == CoinSymbol::ZEC) {
                if(netType == NetworkType::MAIN) {
                    ret = hd_private::to_prefixes(coin_code::ZEC.HDprivate, coin_code::ZEC.HDpublic);
                } else {
                    ret = hd_private::to_prefixes(coin_code::tZEC.HDprivate, coin_code::tZEC.HDpublic);
                }
            }else if(coinName == CoinSymbol::DSH) {
                if(netType == NetworkType::MAIN) {
                    ret = hd_private::to_prefixes(coin_code::DSH.HDprivate, coin_code::DSH.HDpublic);
                } else {
                    ret = hd_private::to_prefixes(coin_code::tDSH.HDprivate, coin_code::tDSH.HDpublic);
                }
            }else if(coinName == CoinSymbol::BCH) {
                if(netType == NetworkType::MAIN) {
                    ret = hd_private::to_prefixes(coin_code::BCH.HDprivate, coin_code::BCH.HDpublic);
                } else {
                    ret = hd_private::to_prefixes(coin_code::tBCH.HDprivate, coin_code::tBCH.HDpublic);
                }
            }else if(coinName == CoinSymbol::WBTC) {
                if(netType == NetworkType::MAIN) {
                    ret = hd_private::to_prefixes(coin_code::WBTC.HDprivate, coin_code::WBTC.HDpublic);
                } else {
                    ret = hd_private::to_prefixes(coin_code::tWBTC.HDprivate, coin_code::tWBTC.HDpublic);
                }
            }else if(coinName == CoinSymbol::QTUM
                    || coinName == "QTUMTOKEN") {
                if(netType == NetworkType::MAIN) {
                    ret = hd_private::to_prefixes(coin_code::QTUM.HDprivate, coin_code::QTUM.HDpublic);
                } else {
                    ret = hd_private::to_prefixes(coin_code::tQTUM.HDprivate, coin_code::tQTUM.HDpublic);
                }
            }

            break;
        case CoinType::ETH:
        case CoinType::ETC:
            break;
    }

    return ret;
}

uint64_t getHdPrivateNet(CoinType coinType, NetworkType netType)
{
    uint64_t ret = 0;
    switch(coinType) {
        case CoinType::BTC:
        case CoinType::SBTC:
        case CoinType::WBTC:
        case CoinType::BCH:
            if(netType == NetworkType::MAIN) {
                ret = hd_private::to_prefixes(coin_code::BTC.HDprivate, coin_code::BTC.HDpublic);
            } else {
                ret = hd_private::to_prefixes(coin_code::tBTC.HDprivate, coin_code::tBTC.HDpublic);
            }
            break;
        case CoinType::LTC:
            if(netType == NetworkType::MAIN) {
                ret = hd_private::to_prefixes(coin_code::LTC.HDprivate, coin_code::LTC.HDpublic);
            } else {
                ret = hd_private::to_prefixes(coin_code::tLTC.HDprivate, coin_code::tLTC.HDpublic);
            }
            break;
        case CoinType::DOGE:
            if(netType == NetworkType::MAIN) {
                ret = hd_private::to_prefixes(coin_code::DOGE.HDprivate, coin_code::DOGE.HDpublic);
            } else {
                ret = hd_private::to_prefixes(coin_code::tDOGE.HDprivate, coin_code::tDOGE.HDpublic);
            }
            break;
        case CoinType::ZEC:
            if(netType == NetworkType::MAIN) {
                ret = hd_private::to_prefixes(coin_code::ZEC.HDprivate, coin_code::ZEC.HDpublic);
            } else {
                ret = hd_private::to_prefixes(coin_code::tZEC.HDprivate, coin_code::tZEC.HDpublic);
            }
            break;
        case CoinType::DSH:
            if(netType == NetworkType::MAIN) {
                ret = hd_private::to_prefixes(coin_code::DSH.HDprivate, coin_code::DSH.HDpublic);
            } else {
                ret = hd_private::to_prefixes(coin_code::tDSH.HDprivate, coin_code::tDSH.HDpublic);
            }
            break;
        case CoinType::QTUM:
            if(netType == NetworkType::MAIN) {
                ret = hd_private::to_prefixes(coin_code::QTUM.HDprivate, coin_code::QTUM.HDpublic);
            } else {
                ret = hd_private::to_prefixes(coin_code::tQTUM.HDprivate, coin_code::tQTUM.HDpublic);
            }
            break;
        case CoinType::ETH:
        case CoinType::ETC:
            break;
    }
    
    return ret;
}

uint32_t getP2kh(CoinType coinType, NetworkType netType, NetParams netParams)
{
    uint32_t ret = 0;
    string coinName = netParams.getSymbol();

    switch(coinType) {
        case CoinType::BTC:
        case CoinType::SBTC:
        case CoinType::LTC:
        case CoinType::DOGE:
        case CoinType::WBTC:
        case CoinType::ZEC:
        case CoinType::DSH:
        case CoinType::BCH:
        case CoinType::QTUM:
            if(coinName == CoinSymbol::BTC || coinName == CoinSymbol::SBTC || coinName == CoinSymbol::WBTC
                    || coinName == CoinSymbol::BCH ) {
                if(netType == NetworkType::MAIN) {
                    ret = coin_code::BTC.P2KH;
                } else {
                    ret = coin_code::tBTC.P2KH;
                }
            } else if(coinName == CoinSymbol::LTC) {
                if(netType == NetworkType::MAIN) {
                    ret = coin_code::LTC.P2KH;
                } else {
                    ret = coin_code::tLTC.P2KH;
                }
            } else if(coinName == CoinSymbol::DOGE) {
                if(netType == NetworkType::MAIN) {
                    ret = coin_code::DOGE.P2KH;
                } else {
                    ret = coin_code::tDOGE.P2KH;
                }
            }
            else if(coinName == CoinSymbol::ZEC) {
                if(netType == NetworkType::MAIN) {
                    ret = coin_code::ZEC.P2KH;
                } else {
                    ret = coin_code::tZEC.P2KH;
                }
            }
            else if(coinName == CoinSymbol::DSH) {
                if(netType == NetworkType::MAIN) {
                    ret = coin_code::DSH.P2KH;
                } else {
                    ret = coin_code::tDSH.P2KH;
                }
            }
            else if(coinName == CoinSymbol::QTUM
                    || coinName == "QTUMTOKEN") {
                if(netType == NetworkType::MAIN) {
                    ret = coin_code::QTUM.P2KH;
                } else {
                    ret = coin_code::tQTUM.P2KH;
                }
            }
            break;
        case CoinType::ETH:
        case CoinType::ETC:
            break;
    }

    return ret;
}

uint8_t getKeyPrefixe(CoinType coinType, NetworkType netType, NetParams netParams)
{
    uint8_t ret = 0;
    string coinName = netParams.getSymbol();

    switch(coinType) {
        case CoinType::BTC:
        case CoinType::SBTC:
        case CoinType::LTC:
        case CoinType::DOGE:
        case CoinType::WBTC:
        case CoinType::ZEC:
        case CoinType::DSH:
        case CoinType::BCH:
        case CoinType::QTUM:
            if(coinName == CoinSymbol::BTC || coinName == CoinSymbol::SBTC || coinName == CoinSymbol::WBTC
               || coinName == CoinSymbol::BCH ) {
                if(netType == NetworkType::MAIN) {
                    ret = coin_code::BTC.keyprefixes;
                } else {
                    ret = coin_code::tBTC.keyprefixes;
                }
            } else if(coinName == CoinSymbol::LTC) {
                if(netType == NetworkType::MAIN) {
                    ret = coin_code::LTC.keyprefixes;
                } else {
                    ret = coin_code::tLTC.keyprefixes;
                }
            } else if(coinName == CoinSymbol::DOGE) {
                if(netType == NetworkType::MAIN) {
                    ret = coin_code::DOGE.keyprefixes;
                } else {
                    ret = coin_code::tDOGE.keyprefixes;
                }
            }
            else if(coinName == CoinSymbol::ZEC) {
                if(netType == NetworkType::MAIN) {
                    ret = coin_code::ZEC.keyprefixes;
                } else {
                    ret = coin_code::tZEC.keyprefixes;
                }
            }
            else if(coinName == CoinSymbol::DSH) {
                if(netType == NetworkType::MAIN) {
                    ret = coin_code::DSH.keyprefixes;
                } else {
                    ret = coin_code::tDSH.keyprefixes;
                }
            }
            else if(coinName == CoinSymbol::QTUM
                    || coinName == "QTUMTOKEN") {
                if(netType == NetworkType::MAIN) {
                    ret = coin_code::QTUM.keyprefixes;
                } else {
                    ret = coin_code::tQTUM.keyprefixes;
                }
            }
            break;
        case CoinType::ETH:
        case CoinType::ETC:
            break;
    }

    return ret;
}

uint16_t to_zec_version(uint16_t address, uint8_t wif)
{
    return uint16_t(wif) << 8 | address;
}

uint32_t getP2kh(CoinType coinType, NetworkType netType)
{
    uint32_t ret = 0;
    
    switch(coinType) {
        case CoinType::BTC:
        case CoinType::SBTC:
        case CoinType::WBTC:
        case CoinType::BCH:
            if(netType == NetworkType::MAIN) {
                ret = coin_code::BTC.P2KH;
            } else {
                ret = coin_code::tBTC.P2KH;
            }
            break;
        case CoinType::LTC:
            if(netType == NetworkType::MAIN) {
                ret = coin_code::LTC.P2KH;
            } else {
                ret = coin_code::tLTC.P2KH;
            }
            break;
        case CoinType::DOGE:
            if(netType == NetworkType::MAIN) {
                ret = coin_code::DOGE.P2KH;
            } else {
                ret = coin_code::tDOGE.P2KH;
            }
            break;
        case CoinType::ZEC:
            if(netType == NetworkType::MAIN) {
                ret = coin_code::ZEC.P2KH;
            } else {
                ret = coin_code::tZEC.P2KH;
            }
            break;
        case CoinType::DSH:
            if(netType == NetworkType::MAIN) {
                ret = coin_code::DSH.P2KH;
            } else {
                ret = coin_code::tDSH.P2KH;
            }
            break;
        case CoinType::QTUM:
            if(netType == NetworkType::MAIN) {
                ret = coin_code::QTUM.P2KH;
            } else {
                ret = coin_code::tQTUM.P2KH;
            }
            break;
        case CoinType::ETH:
        case CoinType::ETC:
            break;
    }
    
    return ret;
}

bool hex( char ch ) //判断字符ch是否16进制字符，是返回1，否返回0
{
    if ( ch >='0' && ch <='9' ) //属于0-9集合，返回是
        return true;
    if ( ch >='A' && ch <='F' ) //属于A-F集合，返回是
        return true;
    if ( ch >='a' && ch <='f' ) //属于a-f集合，返回是
        return true;
    return false; //否则，返回不是
}

void getMnemonicAsBytes(vector<string>& words, vector<uint8_t>& mnemonicBytes)
{
    int size = words.size();
    for(int i = 0; i < size; i++) {
        int len = words[i].length();
        for(int j = 0; j < len; j++) {
            mnemonicBytes.push_back(words[i][j]);
        }

        if(i != size - 1)
            mnemonicBytes.push_back(' ');
    }
}


template <size_t Size>
std::array<uint8_t, WRAP_ZEC_SIZE(Size)> wrap(uint16_t version,
                                          const std::array<uint8_t, Size>& payload)
{
    byte_array<WRAP_ZEC_SIZE(Size)> out;
    out[0] = HIBYTE(version);
    out[1] = LOBYTE(version);

    for(int i = 0; i < payload.size(); i++) {
        out[i + 2] = payload[i];
    }
    insert_checksum(out);
    return out;
}

string zecAddressFromPublic(const ec_public& point, uint16_t version)
{
    if (!point)
        return{};

    data_chunk data;
    if (!point.to_data(data))
        return{};

    short_hash keyid = bitcoin_short_hash(data);

    return encode_base58(wrap(version, keyid));
}

short_hash zecHashFromAddress(string& address)
{
    zec_payment out;
    bool ret = decode_base58(out, address);

    const auto hash = slice<2, short_hash_size + 2>(out);
    return hash;
}

/*
std::vector varSizeData(const std::vector<uint8_t> b)
{
    std::vector<uint8_t> ret;


    if (b.size() < 0x4c)
    {
        ret.insert(ret. end(), (unsigned char)b.size());
    }
    else if (b.size() <= 0xff)
    {
        ret.insert(ret.end(), 0x4c);
        ret.insert(ret.end(), (unsigned char)b.size());
    }
    else if (b.size() <= 0xffff)
    {
        ret.insert(ret.end(), 0x4d);
        uint8_t data[2];
        WriteLE16(data, b.size());
        ret.insert(ret.end(), data, data + sizeof(data));
    }
    else
    {
        ret.insert(ret.end(), 0x4e);
        uint8_t data[4];
        WriteLE32(data, b.size());
        ret.insert(ret.end(), data, data + sizeof(data));
    }
    ret.insert(ret.end(), b.begin(), b.end());



    return ret;
}
*/

void varSizeInt(writer& sink, uint64_t size)
{
    if (size < 0x4c)
    {
        sink.write_byte(static_cast<uint8_t>(size));
    }
    else if (size <= 0xff)
    {
        sink.write_byte(static_cast<uint8_t>(0x4c));
        sink.write_byte(static_cast<uint8_t>(size));
    }
    else if (size <= 0xffff)
    {
        sink.write_byte(static_cast<uint8_t>(0x4d));
        sink.write_2_bytes_little_endian(static_cast<uint16_t>(size));
    }
    else
    {
        sink.write_byte(static_cast<uint8_t>(0x4e));
        sink.write_4_bytes_little_endian(static_cast<uint32_t>(size));
    }

}

int fromHex(char _i)
{
    if (_i >= '0' && _i <= '9')
        return _i - '0';
    if (_i >= 'a' && _i <= 'f')
        return _i - 'a' + 10;
    if (_i >= 'A' && _i <= 'F')
        return _i - 'A' + 10;
    throw exception();
}

vector<uint8_t> fromUserHex(std::string const& _s)
{
    std::vector<uint8_t> ret;
    assert(_s.size() % 2 == 0);
    if (_s.size() < 2)
        return ret;
    uint32_t s = (_s[0] == '0' && _s[1] == 'x') ? 2 : 0;

    ret.reserve((_s.size() - s) / 2);
    for (uint32_t i = s; i < _s.size(); i += 2)
        ret.push_back((uint8_t)(fromHex(_s[i]) * 16 + fromHex(_s[i + 1])));
    return ret;
}


