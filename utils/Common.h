//
//  Common.h
//  Test
//
//  Created by xgc on 12/19/17.
//  Copyright © 2017 xgc. All rights reserved.
//

#ifndef Common_h
#define Common_h


#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/bitcoin/math/hash.hpp>
#include "CoinType.h"
#include "../common/Netparams.hpp"

using namespace std;

using namespace bc;
using namespace bc::wallet;

typedef vector<uint8_t> KeyParameter;
typedef vector<uint8_t> IV;

/*
enum MYVARTYPE
{
    VT_NONE = 0,
    VT_I4 = 1,
    VT_I8,
    VT_STR
};

struct MYVARIANT
{
    MYVARTYPE vt;
    
    union
    {
        string strVal;
        long lVal;
        uint8_t llVal;
    };
    
};
*/

enum TxType
{
    TX_NONE = 0,
    TX_WICC_REGISTERACCOUNT = 1,
    TX_WICC_COMMON = 2,
    TX_WICC_TRANSFER_SPC = 3,
    TX_WICC_BET = 4
};

#define WRAP_ZEC_SIZE(payload_size) (payload_size + checksum_size + 2)

static BC_CONSTEXPR size_t zec_payment_size = 2u + short_hash_size + checksum_size;
typedef byte_array<zec_payment_size> zec_payment;

//#define HIBYTE(w)   ((uint8_t) (((uint16_t) (w) >> 8) & 0xFF))
//#define LOBYTE(w)   ((uint8_t) (w))

void split(const std::string& s, std::vector<std::string>& v, const std::string& c);

string byte2Hex(hash_digest hd);

void getSHA256(string& str, string& res);

uint64_t getHdPrivateNet(CoinType coinType, NetworkType netType, NetParams netParams);

//uint64_t getHdPrivateNet(CoinType coinType, NetworkType netType);

uint32_t getP2kh(CoinType coinType, NetworkType netType, NetParams netParams);

//uint32_t getP2kh(CoinType coinType, NetworkType netType);

uint8_t getKeyPrefixe(CoinType coinType, NetworkType netType, NetParams netParams);

bool hex( char ch );

void getMnemonicAsBytes(vector<string>& words, vector<uint8_t>& mnemonicBytes);

string zecAddressFromPublic(const ec_public& point, uint16_t version);

short_hash zecHashFromAddress(string& address);

uint16_t to_zec_version(uint16_t address, uint8_t wif);

//std::vector varSizeData(const std::vector<uint8_t> b);
void varSizeInt(writer& sink, uint64_t size);

vector<uint8_t> fromUserHex(std::string const& _s);

#endif /* Common_h */
