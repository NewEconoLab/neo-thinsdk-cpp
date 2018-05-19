//
// Created by Administrator on 2018/3/22.
//

#include "NeoSeriesCoinApi.h"
#include "NeoCreateSignTransactionParams.h"
#include "neo_transaction.h"
#include "ScriptBuilder.h"


string NeoSeriesCoinApi::getAddress(data_chunk dc, CoinType coinType, NetworkType netType, vector<ChildNumber> path, NetParams netparams)
{
    uint64_t network = netparams.getHDprivate();
    string coinName = netparams.getSymbol();

    const hd_private m(dc, network);

    hd_private tmp = m;

    int level = path.size();
    for(int i = 0; i < level; i++) {
        ChildNumber cn = path[i];
        if(cn.isHardened()) {
            tmp = tmp.derive_private(cn.num());
        } else {
            tmp = tmp.derive_private(cn.num());
        }
    }

    ec_secret secret = tmp.secret();
    uint8_t p_privateKey[ECC_BYTES] = {0};
    std::memcpy(p_privateKey, &secret[0], secret.size());

    uint8_t p_publicKey[ECC_BYTES+1] = {0};
    ecc_get_publickey( p_privateKey, p_publicKey);
    string address = getAddressFromPublicKey(p_publicKey);

    return address;
}

string NeoSeriesCoinApi::getPrivate(data_chunk dc, CoinType coinType, NetworkType netType, vector<ChildNumber> path, NetParams netparams)
{
    uint64_t network = netparams.getHDprivate();

    const hd_private m(dc, network);

    hd_private tmp = m;

    int level = path.size();
    for(int i = 0; i < level; i++) {
        ChildNumber cn = path[i];
        if(cn.isHardened()) {
            tmp = tmp.derive_private(cn.num());
        } else {
            tmp = tmp.derive_private(cn.num());
        }
    }

    ec_secret secret = tmp.secret();
    uint8_t p_privateKey[ECC_BYTES] = {0};
    std::memcpy(p_privateKey, &secret[0], secret.size());

    string strPri = getWifFromPrivateKey(p_privateKey);

    return strPri;
}

int randomSalt(uint8_t array[8], int len)
{

    srand((unsigned)time(NULL));
    int i;
    for (i = 0; i < len; i++) {
        array[i] = rand() % 0xFF;
    }


    return 0;
}

bool NeoSeriesCoinApi::createWalltByPassword(vector<string> words, string password, vector<ChildNumber> path, NetParams netparams, BtWallet& bw)
{
    const auto seed = decode_mnemonic(words);
    data_chunk dc;

    dc = to_chunk(seed);

    uint8_t salt[8] = {0};
    randomSalt(salt, 8);

    KeyCrypterScrypt kcs;

    uint32_t N = netparams.getN();
    uint32_t R = netparams.getR();
    uint32_t P = netparams.getP();

    if(netparams.getApiVersion() == 0x01) {
        N =32768;
        R = 8;
        P = 1;
    }

    vector<uint8_t> vecIv;
    bool res = kcs.deriveKey(password, salt, 8, N, R, P, vecIv);
    if(!res) {
        return false;
    }

    uint8_t encryptBytes[256] = {0};
    int encryptLen = kcs.encrypt((uint8_t*)&seed[0], seed.size(), encryptBytes, vecIv);
    if(encryptLen <= 0) {
        return false;
    }

    vector<uint8_t> vSeed(encryptBytes, encryptBytes + encryptLen);

    EncryptedData encSeedData;
    encSeedData.setIV(vecIv);
    encSeedData.setEncryptedBytes(vSeed);

    vector<uint8_t> vMnemonic;
    getMnemonicAsBytes(words, vMnemonic);

    encryptLen = kcs.encrypt((uint8_t*)&vMnemonic[0], vMnemonic.size(), encryptBytes, vecIv);
    if(encryptLen <= 0) {
        return false;
    }

    vector<uint8_t> vMn(encryptBytes, encryptBytes + encryptLen);

    EncryptedData encMnData;
    encMnData.setIV(vecIv);
    encMnData.setEncryptedBytes(vMn);

    string hashPwd;
    getSHA256(password, hashPwd);

    long creationTimeSeconds = time(NULL);

    vector<uint8_t> vSalt(&salt[0], &salt[8]);

    BtSeed* btSeed = new BtSeed(dc, words, encMnData, encSeedData, creationTimeSeconds, hashPwd, vSalt);
    bw.setBtSeed(btSeed);
    bw.setSymbol(netparams.getSymbol());

    string address;
    address = getAddress(dc, netparams.getCoinType(), netparams.getNetType(), path, netparams);

    bw.setAddress(address);

    return true;
}

string NeoSeriesCoinApi::getPriKeyFromBtSeed(BtSeed btSeed, string password, vector<ChildNumber> path, NetParams netparams)
{
    KeyCrypterScrypt kcs;

    vector<uint8_t> randomSalt = btSeed.getRandomSalt();

    uint32_t N = netparams.getN();
    uint32_t R = netparams.getR();
    uint32_t P = netparams.getP();

    if(netparams.getApiVersion() == 0x01) {
        N =32768;
        R = 8;
        P = 1;
    }

    vector<uint8_t> vecIv;
    bool res = kcs.deriveKey(password, &randomSalt[0], 8, N, R, P, vecIv);
    if(!res) {
        return "";
    }

    EncryptedData encSeedData = btSeed.getEncryptedSeed();
    vector<uint8_t> vEncSeed = encSeedData.getEncryptedBytes();

    uint8_t plainSeed[1024] = {0};

    int len = kcs.decrypt(&vEncSeed[0], vEncSeed.size(), plainSeed, encSeedData.getIV());
    if(len <= 0) {
        return "";
    }

    vector<uint8_t> vSeed(&plainSeed[0], &plainSeed[0] + len);

    data_chunk dc;

    dc = to_chunk(vSeed);

    string strPriv;

    strPriv = getPrivate(dc, netparams.getCoinType(), netparams.getNetType(), path, netparams);

    return strPriv;
}

bool NeoSeriesCoinApi::createSignTransaction(CreateSignTransactionParams* params, vector<ChildNumber> path, NetParams netparams, map<string, string>& resultMap)
{
    NeoCreateSignTransactionParams* neoParams = (NeoCreateSignTransactionParams*)params;
    string priKey = neoParams->getPriKey();

    ec_secret secret;

    if(priKey.length() == 0)
    {
        priKey = getPriKeyFromBtSeed(neoParams->getBtSeed(), neoParams->getPassword(),
                                     path, netparams);
    }
    secret = getPrivateKeyFromWif(priKey);

    uint8_t Key[ECC_BYTES] ={0};
    std::memcpy(Key, &secret[0], ECC_BYTES);
    string test = getWifFromPrivateKey(Key);

    neo::Transaction tx;
    tx.type = neo::TransactionType::ContractTransaction;
    tx.version = netparams.getVersion();

    vector<BtcvoutForm> btcvoutFormList = neoParams->getBtcvoutFormList();
    int size = btcvoutFormList.size();

    uint64_t sum = 0;

    for(int i = 0; i < size; i++)
    {
        hash_digest utxoHash;
        decode_hash(utxoHash, btcvoutFormList[i].getHash());

        neo::TransactionInput input;
        input.hash.assign(utxoHash.begin(), utxoHash.end());
        input.index = (int16_t)btcvoutFormList[i].getN();
        sum += btcvoutFormList[i].getValue();

        tx.inputs.push_back(input);
    }

    uint64_t sendValue = neoParams->getSendValue();
    string sendAddress = neoParams->getSendAddress();
    if(sum < sendValue)
        return false;
    string assetId = neoParams->getAssetId();
    neo::TransactionOutput output;
    vector<uint8_t> vAssetId = fromUserHex(assetId);
    reverse(vAssetId.begin(), vAssetId.end());
    output.assetId = vAssetId;
    output.value.value = sendValue;
    short_hash pubkeyHash = getPublicKeyHashFromAddress(sendAddress);
    output.toAddress.assign(pubkeyHash.begin(), pubkeyHash.end());

    tx.outputs.push_back(output);

    string fromAddress = neoParams->getFromAddress();
    uint64_t left = sum - sendValue;
    if(left > 0) {
        neo::TransactionOutput output2;
        output2.assetId = vAssetId;
        output2.value.value = left;
        short_hash pkh = getPublicKeyHashFromAddress(fromAddress);
        output2.toAddress.assign(pkh.begin(), pkh.end());

        tx.outputs.push_back(output2);
    }

    vector<uint8_t> unsignedData;
    tx.getMessage(unsignedData);

    string tt = encode_base16(unsignedData);

    vector<uint8_t> signature;
    vector<uint8_t> vSecret(secret.begin(), secret.end());
    bool bRet = Sign(unsignedData, vSecret, signature);
    if(bRet == false)
        return false;

    uint8_t p_privateKey[ECC_BYTES] = {0};
    std::memcpy(p_privateKey, &secret[0], secret.size());

    uint8_t p_publicKey[ECC_BYTES + 1] = {0};
    ecc_get_publickey( p_privateKey, p_publicKey);

    vector<uint8_t> vPubkey(p_publicKey, p_publicKey + ECC_BYTES + 1);

    tx.AddWitness(signature, vPubkey, fromAddress);

    vector<uint8_t> rawData;
    tx.getRawData(rawData);

    string hex = encode_base16(rawData);

    size_t newLen = rawData.size();

    std::cout << "Raw Transaction len: " << newLen << std::endl;
    std::cout << "Raw Transaction: " << std::endl;
    std::cout << hex << std::endl;

    std::stringstream strIO;
    string strLen;
    strIO << newLen;
    strIO >> strLen;
    strIO.clear();

    resultMap.insert(make_pair("hex", hex));
    resultMap.insert(make_pair("length", strLen));

    return true;
}

bool NeoSeriesCoinApi::getNep5Contract(string scriptAddress, string from, string to, CBigNum num, vector<uint8_t>& rawdata)
{
    neo::ScriptBuilder sb;

    vector<uint8_t> assetId;
    assetId = fromUserHex(scriptAddress);
    reverse(assetId.begin(), assetId.end());

    Json::Value paramList;

    Json::Value fromJson;
    string fromParam = "(address)" + from;
    fromJson["from"] = fromParam;
    paramList.append(fromParam);

    Json::Value toJson;
    string toParam = "(address)" + to;
    toJson["to"] = toParam;
    paramList.append(toParam);

    Json::Value numJson;
    string numParam = "(integer)" + num.ToString();
    numJson["num"] = numParam;
    paramList.append(numParam);

    sb.EmitParamJson(paramList);
    sb.EmitPushString("transfer");
    sb.EmitAppCall(assetId);

    sb.toRawData(rawdata);

    return true;
}

vector<string> NeoSeriesCoinApi::getMnemonicCodeFromBtSeed(BtSeed btSeed, string password, NetParams netparams)
{
    KeyCrypterScrypt kcs;

    vector<string> vRes;

    vector<uint8_t> randomSalt = btSeed.getRandomSalt();

    uint32_t N = netparams.getN();
    uint32_t R = netparams.getR();
    uint32_t P = netparams.getP();

    if(netparams.getApiVersion() == 0x01) {
        N =32768;
        R = 8;
        P = 1;
    }

    vector<uint8_t> vecIv;
    bool res = kcs.deriveKey(password, &randomSalt[0], 8, N, R, P, vecIv);
    if(!res) {
        return vRes;
    }

    EncryptedData encEncryptedMnemonicCode = btSeed.getEncryptedMnemonicCode();
    vector<uint8_t> vEncMne = encEncryptedMnemonicCode.getEncryptedBytes();

    uint8_t plainMne[1024] = {0};

    int len = kcs.decrypt(&vEncMne[0], vEncMne.size(), plainMne, encEncryptedMnemonicCode.getIV());
    if(len <= 0) {
        return vRes;
    }

    string strMne((char*)plainMne, len);

    split(strMne, vRes, " ");

    return vRes;
}

bool NeoSeriesCoinApi::createNep5Transaction(CreateSignTransactionParams* params, vector<ChildNumber> path, NetParams netparams, map<string, string>& resultMap)
{
    NeoCreateSignTransactionParams* neoParams = (NeoCreateSignTransactionParams*)params;
    string priKey = neoParams->getPriKey();

    ec_secret secret;

    if(priKey.length() == 0)
    {
        priKey = getPriKeyFromBtSeed(neoParams->getBtSeed(), neoParams->getPassword(),
                                     path, netparams);
    }
    secret = getPrivateKeyFromWif(priKey);

    uint8_t Key[ECC_BYTES] ={0};
    std::memcpy(Key, &secret[0], ECC_BYTES);

    neo::Transaction tx;
    tx.type = neo::TransactionType::InvocationTransaction;
    //tx.type = neo::TransactionType::ContractTransaction;
    tx.version = netparams.getVersion();

    vector<BtcvoutForm> btcvoutFormList = neoParams->getBtcvoutFormList();
    int size = btcvoutFormList.size();

    uint64_t sum = 0;

    for(int i = 0; i < size; i++)
    {
        hash_digest utxoHash;
        decode_hash(utxoHash, btcvoutFormList[i].getHash());

        neo::TransactionInput input;
        input.hash.assign(utxoHash.begin(), utxoHash.end());
        input.index = (int16_t)btcvoutFormList[i].getN();
        sum += btcvoutFormList[i].getValue();

        tx.inputs.push_back(input);
    }

    string sendAddress = neoParams->getSendAddress();

    string assetId = neoParams->getAssetId();
    neo::TransactionOutput output;
    vector<uint8_t> vAssetId = fromUserHex(assetId);
    reverse(vAssetId.begin(), vAssetId.end());
    output.assetId = vAssetId;
    output.value.value = sum;
    short_hash pubkeyHash = getPublicKeyHashFromAddress(sendAddress);
    output.toAddress.assign(pubkeyHash.begin(), pubkeyHash.end());

    tx.outputs.push_back(output);

    string fromAddress = neoParams->getFromAddress();


    neo::InvokeTransData* pInvokeData = new neo::InvokeTransData();
    tx.extdata = pInvokeData;
    pInvokeData->script = neoParams->getData();
    pInvokeData->gas.value = 100000000;

    vector<uint8_t> unsignedData;
    tx.getMessage(unsignedData);

    string tt = encode_base16(unsignedData);

    vector<uint8_t> signature;
    vector<uint8_t> vSecret(secret.begin(), secret.end());
    bool bRet = Sign(unsignedData, vSecret, signature);
    if(bRet == false)
        return false;

    uint8_t p_privateKey[ECC_BYTES] = {0};
    std::memcpy(p_privateKey, &secret[0], secret.size());

    uint8_t p_publicKey[ECC_BYTES + 1] = {0};
    ecc_get_publickey( p_privateKey, p_publicKey);

    vector<uint8_t> vPubkey(p_publicKey, p_publicKey + ECC_BYTES + 1);

    tx.AddWitness(signature, vPubkey, fromAddress);

    vector<uint8_t> rawData;
    tx.getRawData(rawData);

    string hex = encode_base16(rawData);

    size_t newLen = rawData.size();

    std::cout << "Raw Transaction len: " << newLen << std::endl;
    std::cout << "Raw Transaction: " << std::endl;
    std::cout << hex << std::endl;

    std::stringstream strIO;
    string strLen;
    strIO << newLen;
    strIO >> strLen;
    strIO.clear();

    resultMap.insert(make_pair("hex", hex));
    resultMap.insert(make_pair("length", strLen));

    return true;
}
