//
//  CommonCoinApi.hpp
//  Test
//
//  Created by xgc on 12/19/17.
//  Copyright © 2017 xgc. All rights reserved.
//

#ifndef CommonCoinApi_hpp
#define CommonCoinApi_hpp

#include "Netparams.hpp"
#include "BtSeed.hpp"
#include "BtWallet.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <bitcoin/bitcoin.hpp>
#include "ChildNumber.hpp"
#include "Common.h"
#include "CreateSignTransactionParams.hpp"
#include "NeoCreateSignTransactionParams.h"
#include "NeoSeriesCoinApi.h"

using namespace bc;
using namespace bc::wallet;
using namespace std;

class CommonCoinApi
{
public:
    
    /*
     获取助记词列表
     */
    vector<string> createAllCoinMnemonicCode();
    
    /*
     检查助记词列表
     */
    bool checkMnemonicCode(vector<string> words);
    
    /*
     根据 加密种子获取 解密后的私钥
     */
    string getPriKeyFromBtSeed(BtSeed btSeed, string password, NetParams netParams);
    
    /*
     根据 加密种子获取 解密后的助记词
     */
    vector<string> getMnemonicCodeFromBtWallet(BtSeed btSeed, string password, NetParams netParams);
    
    /*
     一次创建一个地址
     */
    bool createWallet(string words, string password, NetParams netParams, BtWallet& bw);
    
    /*
     一次创建多种币种钱包
     */
    vector<BtWallet*> createWallets(string words, string password, vector<NetParams> netParamsList);
    
    /*
     修改密码
     */
    bool changePassword(BtSeed btSeed, string oldPassword, string newPassword, BtSeed& newBtSeed, NetParams netparams);
    
    /*
     创建签名交易
     */
    bool createSignTransaction(CreateSignTransactionParams* createSignTransactionParams, NetParams netParams, map<string, string>& resultMap);

    /*
     nep5转账
     */
    bool getNep5Contract(string scriptAddress, string from, string to, CBigNum num, vector<uint8_t>& rawdata);
    

private:
    bool getBIP44Path(KeyPath keyPath, vector<ChildNumber>& path );
    bool getBIP44PathV2(KeyPath keyPath, vector<ChildNumber>& path);
private:
    static map<string, vector<ChildNumber> > BIP44Map;
    
    
};

#endif /* CommonCoinApi_hpp */
