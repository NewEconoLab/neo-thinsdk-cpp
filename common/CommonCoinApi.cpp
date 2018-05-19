//
//  CommonCoinApi.cpp
//  Test
//
//  Created by xgc on 12/19/17.
//  Copyright © 2017 xgc. All rights reserved.
//

#include "CommonCoinApi.hpp"
#include "../utils/KeyCrypterScrypt.h"
#include "NeoSeriesCoinApi.h"

map<string, vector<ChildNumber> > CommonCoinApi::BIP44Map;

bool CommonCoinApi::getBIP44Path(KeyPath keyPath, vector<ChildNumber>& path)
{
    if(keyPath.getPath1() < 0 || keyPath.getPath2() < 0 || keyPath.getPath3() < 0) {
        return false;
    }
    
    map<string,vector<ChildNumber> >::iterator it;
    it = BIP44Map.find(keyPath.getSymbol());

    if(it == BIP44Map.end()) {
        if(keyPath.getPath4() < 0 && keyPath.getPath5() < 0) {
            path.push_back(ChildNumber(keyPath.getPath1(), true));
            path.push_back(ChildNumber(keyPath.getPath2(), true));
            path.push_back(ChildNumber(keyPath.getPath3(), true));
        } else if(keyPath.getPath4() >= 0 && keyPath.getPath5() < 0) {
            path.push_back(ChildNumber(keyPath.getPath1(), true));
            path.push_back(ChildNumber(keyPath.getPath2(), true));
            path.push_back(ChildNumber(keyPath.getPath3(), true));
            path.push_back(ChildNumber(keyPath.getPath4(), true));
        } else if(keyPath.getPath4() >= 0 && keyPath.getPath5() >= 0) {
            path.push_back(ChildNumber(keyPath.getPath1(), true));
            path.push_back(ChildNumber(keyPath.getPath2(), true));
            path.push_back(ChildNumber(keyPath.getPath3(), true));
            path.push_back(ChildNumber(keyPath.getPath4(), true));
            path.push_back(ChildNumber(keyPath.getPath5(), true));
        }
        
        BIP44Map.insert(make_pair(keyPath.getSymbol(), path));
        
        return true;
    }
    
    path = it->second;
    
    return true;
}

bool CommonCoinApi::getBIP44PathV2(KeyPath keyPath, vector<ChildNumber>& path)
{
    if(keyPath.getPath1() < 0 || keyPath.getPath2() < 0 || keyPath.getPath3() < 0) {
        return false;
    }

    if(keyPath.getPath4() < 0 && keyPath.getPath5() < 0) {
        path.push_back(ChildNumber(keyPath.getPath1(), keyPath.getHd1()));
        path.push_back(ChildNumber(keyPath.getPath2(), keyPath.getHd2()));
        path.push_back(ChildNumber(keyPath.getPath3(), keyPath.getHd3()));
    } else if(keyPath.getPath4() >= 0 && keyPath.getPath5() < 0) {
        path.push_back(ChildNumber(keyPath.getPath1(), keyPath.getHd1()));
        path.push_back(ChildNumber(keyPath.getPath2(), keyPath.getHd2()));
        path.push_back(ChildNumber(keyPath.getPath3(), keyPath.getHd3()));
        path.push_back(ChildNumber(keyPath.getPath4(), keyPath.getHd4()));
    } else if(keyPath.getPath4() >= 0 && keyPath.getPath5() >= 0) {
        path.push_back(ChildNumber(keyPath.getPath1(), keyPath.getHd1()));
        path.push_back(ChildNumber(keyPath.getPath2(), keyPath.getHd2()));
        path.push_back(ChildNumber(keyPath.getPath3(), keyPath.getHd3()));
        path.push_back(ChildNumber(keyPath.getPath4(), keyPath.getHd4()));
        path.push_back(ChildNumber(keyPath.getPath5(), keyPath.getHd5()));
    }


    return true;
}


/*
 获取助记词列表
 */
vector<string> CommonCoinApi::createAllCoinMnemonicCode()
{
    uint8_t seed[16] = {0};

    KeyCrypterScrypt::randomSeed(seed, 16);
    
    vector<uint8_t> v(&seed[0], &seed[16]);
    
    data_slice entropy = v;
    
    word_list wl = create_mnemonic(entropy);
    return wl;
}

/*
 检查助记词列表
 */
bool CommonCoinApi::checkMnemonicCode(vector<string> words)
{
    return validate_mnemonic(words, language::en);
}

/*
 根据 加密种子获取 解密后的私钥
 */
string CommonCoinApi::getPriKeyFromBtSeed(BtSeed btSeed, string password, NetParams netParams)
{
    vector<ChildNumber> vCN;

    if(netParams.getApiVersion() == 0x01) {
        getBIP44Path(netParams.getKeyPath(), vCN);
    }
    else
    {
        getBIP44PathV2(netParams.getKeyPath(), vCN);
    }

    NeoSeriesCoinApi neoApi;
    return neoApi.getPriKeyFromBtSeed(btSeed, password, vCN, netParams);

}

/*
 根据 加密种子获取 解密后的助记词
 */
vector<string> CommonCoinApi::getMnemonicCodeFromBtWallet(BtSeed btSeed, string password, NetParams netParams)
{
    NeoSeriesCoinApi neoApi;
    return neoApi.getMnemonicCodeFromBtSeed(btSeed, password, netParams);
}

/*
 一次创建一个地址
 */
bool CommonCoinApi::createWallet(string words, string password, NetParams netParams, BtWallet& bw)
{
    vector<ChildNumber> vCN;
    if(netParams.getApiVersion() == 0x01) {
        getBIP44Path(netParams.getKeyPath(), vCN);
    }
    else
    {
        getBIP44PathV2(netParams.getKeyPath(), vCN);
    }
    
    vector<string> wordList;
    split(words, wordList, " ");

    NeoSeriesCoinApi neoApi;
    return  neoApi.createWalltByPassword(wordList, password, vCN, netParams, bw);
}

/*
 一次创建多种币种钱包,需要释放内存 */

vector<BtWallet*> CommonCoinApi::createWallets(string words, string password, vector<NetParams> netParamsList)
{
    vector<BtWallet*> vbt;
    
    int size = netParamsList.size();
    for(int i = 0; i < size; i++){
        BtWallet* bw = new BtWallet();
        bool res = createWallet(words, password, netParamsList[i], *bw);
        if(res) {
            vbt.push_back(bw);
        }
    }
    
    return vbt;
}

/*
 修改密码
 */
bool CommonCoinApi::changePassword(BtSeed btSeed, string oldPassword, string newPassword, BtSeed& newBtSeed, NetParams netparams)
{
    KeyCrypterScrypt kcs;
    
    vector<uint8_t> randomSalt = btSeed.getRandomSalt();

    uint32_t N = netparams.getN();
    uint32_t R = netparams.getR();
    uint32_t P = netparams.getP();

    if(netparams.getApiVersion() == 0x01) {
        N = 32768;
        R = 8;
        P = 1;
    }

    vector<uint8_t> vecIv;
    bool res = kcs.deriveKey(oldPassword, &randomSalt[0], 8, N, R, P, vecIv);
    if(!res) {
        return false;
    }
    
    EncryptedData encSeedData = btSeed.getEncryptedSeed();
    vector<uint8_t> vEncSeed = encSeedData.getEncryptedBytes();
    
    uint8_t plainSeed[1024] = {0};
    
    int plainlen = kcs.decrypt(&vEncSeed[0], vEncSeed.size(), plainSeed, encSeedData.getIV());
    if(plainlen <= 0) {
        return "";
    }

    
    EncryptedData encEncryptedMnemonicCode = btSeed.getEncryptedMnemonicCode();
    vector<uint8_t> vEncMne = encEncryptedMnemonicCode.getEncryptedBytes();
    
    uint8_t plainMne[1024] = {0};
    
    int mnelen = kcs.decrypt(&vEncMne[0], vEncMne.size(), plainMne, encEncryptedMnemonicCode.getIV());
    if(mnelen <= 0) {
        return false;
    }

    vector<uint8_t> vecIv2;
    res = kcs.deriveKey(newPassword, &randomSalt[0], 8, N, R, P, vecIv2);
    if(!res) {
        return false;
    }
    
    
    uint8_t encryptBytes[256] = {0};
    int encryptLen = kcs.encrypt((uint8_t*)&plainSeed[0], plainlen, encryptBytes, vecIv2);
    if(encryptLen <= 0) {        return false;
    }
    
    vector<uint8_t> vSeed(encryptBytes, encryptBytes + encryptLen);
    
    EncryptedData encSeedData2;
    encSeedData2.setIV(vecIv2);
    encSeedData2.setEncryptedBytes(vSeed);
    
    
    encryptLen = kcs.encrypt((uint8_t*)&plainMne[0], mnelen, encryptBytes, vecIv2);
    if(encryptLen <= 0) {
        return false;
    }
    
    vector<uint8_t> vMn(encryptBytes, encryptBytes + encryptLen);
    
    EncryptedData encMnData2;
    encMnData2.setIV(vecIv2);
    encMnData2.setEncryptedBytes(vMn);
    
    string hashPwd;
    getSHA256(newPassword, hashPwd);
    
    data_chunk dc;
    
    dc = to_chunk(vSeed);
    
    vector<string> words;
    
    string finalMen((char*)plainMne, mnelen);
    split((char*)finalMen.c_str(), words, " ");
    
    
    newBtSeed.setSeed(dc);
    newBtSeed.setMnemonicCode(words);
    newBtSeed.setEncryptedMnemonicCode(encMnData2);
    newBtSeed.setEncryptedSeed(encSeedData2);
    newBtSeed.setCreationTimeSeconds(btSeed.getCreationTimeSeconds());
    newBtSeed.setPwdhash(hashPwd);
    newBtSeed.setRandomSalt(randomSalt);

    
    return true;
}


bool CommonCoinApi::createSignTransaction(CreateSignTransactionParams* createSignTransactionParams, NetParams netParams, map<string, string>& resultMap)
{
    vector<ChildNumber> vCN;
    if(netParams.getApiVersion() == 0x01) {
        getBIP44Path(netParams.getKeyPath(), vCN);
    }
    else
    {
        getBIP44PathV2(netParams.getKeyPath(), vCN);
    }

    NeoSeriesCoinApi neoApi;

    NeoCreateSignTransactionParams *params = (NeoCreateSignTransactionParams*)createSignTransactionParams;

    if(params->getData().size() <= 0)
        return neoApi.createSignTransaction(params, vCN, netParams, resultMap);
    return neoApi.createNep5Transaction(params, vCN, netParams, resultMap);
}



bool CommonCoinApi::getNep5Contract(string scriptAddress, string from, string to, CBigNum num, vector<uint8_t>& rawdata)
{
    NeoSeriesCoinApi neoApi;
    return neoApi.getNep5Contract(scriptAddress, from, to, num, rawdata);
}


