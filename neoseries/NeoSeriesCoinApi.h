//
// Created by Administrator on 2018/3/22.
//

#ifndef TEST_NEOSERIESCOINAPI_H
#define TEST_NEOSERIESCOINAPI_H

#include "../common/BaseCoinApi.hpp"
#include "../common/ChildNumber.hpp"
#include "../common/Netparams.hpp"
#include "../common/BtWallet.hpp"
#include "../common/CreateSignTransactionParams.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <bitcoin/bitcoin.hpp>
#include "ChildNumber.hpp"
#include "../utils/Common.h"
#include "helper.h"
#include "bignum.h"

using namespace bc;
using namespace bc::wallet;
using namespace bc::chain;
using namespace bc::machine;
using namespace std;

class NeoSeriesCoinApi  : public BaseCoinApi
{
public:
    bool createWalltByPassword(vector<string> words, string password, vector<ChildNumber> path, NetParams netparams, BtWallet& bw);
    string getPriKeyFromBtSeed(BtSeed btSeed, string password, vector<ChildNumber> path, NetParams netparams);

    bool createSignTransaction(CreateSignTransactionParams* params, vector<ChildNumber> path, NetParams netparams, map<string, string>& resultMap);
    bool createNep5Transaction(CreateSignTransactionParams* params, vector<ChildNumber> path, NetParams netparams, map<string, string>& resultMap);
    bool getNep5Contract(string scriptAddress, string from, string to, CBigNum num, vector<uint8_t>& rawdata);
    vector<string> getMnemonicCodeFromBtSeed(BtSeed btSeed, string password, NetParams netparams);
private:
    string getAddress(data_chunk dc, CoinType coinType, NetworkType netType, vector<ChildNumber> path, NetParams netparams);
    string getPrivate(data_chunk dc, CoinType coinType, NetworkType netType, vector<ChildNumber> path, NetParams netparams);


};


#endif //TEST_NEOSERIESCOINAPI_H
