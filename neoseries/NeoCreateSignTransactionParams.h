//
// Created by Administrator on 2018/3/23.
//

#ifndef TEST_NEOCREATESIGNTRANSACTIONPARAMS_H
#define TEST_NEOCREATESIGNTRANSACTIONPARAMS_H

#include "../common/CreateSignTransactionParams.hpp"
#include "../common/BtSeed.hpp"
#include "../common/BtcvoutForm.hpp"

class NeoCreateSignTransactionParams : public CreateSignTransactionParams
{

public:
    const BtSeed &getBtSeed() const;

    void setBtSeed(const BtSeed &btSeed);

    const string &getFromAddress() const;

    void setFromAddress(const string &fromAddress);

    const string &getSendAddress() const;

    void setSendAddress(const string &sendAddress);

    uint64_t getSendValue() const;

    void setSendValue(uint64_t sendValue);

    const string &getPassword() const;

    void setPassword(const string &password);

    const string &getPriKey() const;

    void setPriKey(const string &priKey);

    const vector<BtcvoutForm> &getBtcvoutFormList() const;

    void setBtcvoutFormList(const vector<BtcvoutForm> &btcvoutFormList);

    bool isRecipientsPayFees() const;

    void setRecipientsPayFees(bool recipientsPayFees);

    const vector<uint8_t> &getData() const;

    void setData(const vector<uint8_t> &data);

    TxType getTxType() const;

    void setTxType(TxType txType);

    const string &getAssetId() const;

    void setAssetId(const string &assetId);

private:
    BtSeed btSeed;
    string fromAddress;
    string sendAddress;
    uint64_t sendValue;
    string password;
    string priKey;
    string assetId;
    vector<BtcvoutForm> btcvoutFormList;
    bool recipientsPayFees;
    vector<uint8_t> data;
    TxType txType;
};


#endif //TEST_NEOCREATESIGNTRANSACTIONPARAMS_H
