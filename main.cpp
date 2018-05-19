#include <QCoreApplication>
#include "common/CommonCoinApi.hpp"


void testNeo()
{
    CommonCoinApi* cca = new CommonCoinApi();

    if(cca) {
        vector<string> words;

        words = cca->createAllCoinMnemonicCode();

        for (const auto &word: words) {
            bc::cout << word << std::endl;
        }

        bool ret = cca->checkMnemonicCode(words);
        bc::cout << ret << std::endl;

        KeyPath keyPath;
        keyPath.setSymbol("NEO");
        keyPath.setPath1(44);
        keyPath.setHd1(true);
        keyPath.setPath2(888);
        keyPath.setHd2(true);
        keyPath.setPath3(0);
        keyPath.setHd3(true);
        keyPath.setPath4(0);
        keyPath.setHd4(false);
        keyPath.setPath5(0);
        keyPath.setHd5(false);

        string password = "12345";
        NetParams netParams;
        netParams.setCoinType(CoinType::NEO);
        netParams.setNetType(NetworkType::TEST);
        netParams.setVersion(0x00000000);
        netParams.setSymbol("NEO");

        netParams.setApiVersion(2);

        netParams.setHDprivate(0);
        netParams.setHDpublic(0);
        netParams.setP2KH(0);
        netParams.setP2SH(0);
        netParams.setKeyprefixes(0);

        netParams.setN(32768);
        netParams.setR(8);
        netParams.setP(1);


        netParams.setKeyPath(keyPath);

        string strWords;

        int size = words.size();
        for(int i = 0; i < size; i++) {
            strWords += words[i];
            if(i != size - 1)
                strWords += " ";
        }

        BtWallet bw;

        ret = cca->createWallet(strWords, password, netParams, bw);
        bc::cout << ret << std::endl;

        string strPriv = cca->getPriKeyFromBtSeed(*bw.getBtSeed(), password, netParams);
        bc::cout << strPriv << std::endl;

        vector<string> wl;
        wl = cca->getMnemonicCodeFromBtWallet(*bw.getBtSeed(), password, netParams);

        size = wl.size();
        for(int i = 0; i < size; i++) {
            bc::cout << wl[i] << std::endl;
        }

        string newPassword = "abcde";
        BtSeed newBtSeed;
        ret = cca->changePassword(*bw.getBtSeed(), password, newPassword, newBtSeed, netParams);
        bc::cout << ret << std::endl;

        NeoCreateSignTransactionParams params;
        params.setBtSeed(newBtSeed);
        params.setPriKey("KxQvp9esz3r13Zgki2pE8STxMrJ8nyAaN9uHcxEttbXNkWzKxf3z");
        params.setPassword(newPassword);
        params.setFromAddress("ANCMUhUuS5v5FGjb2eBXTCUtChbxNPZZgn");
        params.setSendAddress("APxpKoFCfBk8RjkRdKwyUnsBntDRXLYAZc");
        params.setAssetId("c56f33fc6ecfcd0c225c4ab356fee59390af8560be0e930faebe74a6daff7c9b");
        params.setSendValue(100000000);


        vector<BtcvoutForm> voutList;
        BtcvoutForm vout1;
        vout1.setHash("b80f65fc5c0cc9a24ae2d613770202aae95dfa598f6541f75987b747eb5ca830");
        vout1.setValue(10000000000);
        vout1.setN(0);
        vout1.setCoinBase(false);
        voutList.push_back(vout1);
        params.setBtcvoutFormList(voutList);

        map<string, string> resultMap;

        ret = cca->createSignTransaction(&params, netParams, resultMap);

        bc::cout << ret << std::endl;
    }
}

void testNep5()
{
    CommonCoinApi* cca = new CommonCoinApi();

    if(cca) {
        vector<string> words;

        words = cca->createAllCoinMnemonicCode();

        for (const auto &word: words) {
            bc::cout << word << std::endl;
        }

        bool ret = cca->checkMnemonicCode(words);
        bc::cout << ret << std::endl;

        KeyPath keyPath;
        keyPath.setSymbol("NEO");
        keyPath.setPath1(44);
        keyPath.setHd1(true);
        keyPath.setPath2(888);
        keyPath.setHd2(true);
        keyPath.setPath3(0);
        keyPath.setHd3(true);
        keyPath.setPath4(0);
        keyPath.setHd4(false);
        keyPath.setPath5(0);
        keyPath.setHd5(false);

        string password = "12345";
        NetParams netParams;
        netParams.setCoinType(CoinType::NEO);
        netParams.setNetType(NetworkType::TEST);
        netParams.setVersion(0x00000000);
        netParams.setSymbol("NEO");

        netParams.setApiVersion(2);

        netParams.setHDprivate(0);
        netParams.setHDpublic(0);
        netParams.setP2KH(0);
        netParams.setP2SH(0);
        netParams.setKeyprefixes(0);

        netParams.setN(32768);
        netParams.setR(8);
        netParams.setP(1);


        netParams.setKeyPath(keyPath);

        string strWords;

        int size = words.size();
        for(int i = 0; i < size; i++) {
            strWords += words[i];
            if(i != size - 1)
                strWords += " ";
        }

        BtWallet bw;

        ret = cca->createWallet(strWords, password, netParams, bw);
        bc::cout << ret << std::endl;

        string strPriv = cca->getPriKeyFromBtSeed(*bw.getBtSeed(), password, netParams);
        bc::cout << strPriv << std::endl;

        vector<string> wl;
        wl = cca->getMnemonicCodeFromBtWallet(*bw.getBtSeed(), password, netParams);

        size = wl.size();
        for(int i = 0; i < size; i++) {
            bc::cout << wl[i] << std::endl;
        }

        string newPassword = "abcde";
        BtSeed newBtSeed;
        ret = cca->changePassword(*bw.getBtSeed(), password, newPassword, newBtSeed, netParams);
        bc::cout << ret << std::endl;

        NeoCreateSignTransactionParams params;
        params.setBtSeed(newBtSeed);
        params.setPriKey("KxQvp9esz3r13Zgki2pE8STxMrJ8nyAaN9uHcxEttbXNkWzKxf3z");
        params.setPassword(newPassword);
        params.setFromAddress("ANCMUhUuS5v5FGjb2eBXTCUtChbxNPZZgn");
        params.setSendAddress("ANCMUhUuS5v5FGjb2eBXTCUtChbxNPZZgn");
        params.setAssetId("602c79718b16e442de58778e148d0b1084e3b2dffd5de6b7b16cee7969282de7");
        params.setSendValue(0);

        vector<uint8_t> data;
        cca->getNep5Contract("c88acaae8a0362cdbdedddf0083c452a3a8bb7b8", "ANCMUhUuS5v5FGjb2eBXTCUtChbxNPZZgn", "APxpKoFCfBk8RjkRdKwyUnsBntDRXLYAZc", 100000000, data);
        params.setData(data);


        vector<BtcvoutForm> voutList;
        BtcvoutForm vout1;
        vout1.setHash("d233d677aee8164cffc5ffa0699920d9dda9d4f5a8c23ca074641777e2a00f3b");
        vout1.setValue(900000000);
        vout1.setN(0);
        vout1.setCoinBase(false);
        voutList.push_back(vout1);
        params.setBtcvoutFormList(voutList);

        map<string, string> resultMap;

        ret = cca->createSignTransaction(&params, netParams, resultMap);

        bc::cout << ret << std::endl;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    testNeo();

    testNep5();

    return a.exec();
}
