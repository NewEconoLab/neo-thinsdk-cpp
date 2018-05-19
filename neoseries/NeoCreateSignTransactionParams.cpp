//
// Created by Administrator on 2018/3/23.
//

#include "NeoCreateSignTransactionParams.h"

const BtSeed &NeoCreateSignTransactionParams::getBtSeed() const {
    return btSeed;
}

void NeoCreateSignTransactionParams::setBtSeed(const BtSeed &btSeed) {
    NeoCreateSignTransactionParams::btSeed = btSeed;
}

const string &NeoCreateSignTransactionParams::getFromAddress() const {
    return fromAddress;
}

void NeoCreateSignTransactionParams::setFromAddress(const string &fromAddress) {
    NeoCreateSignTransactionParams::fromAddress = fromAddress;
}

const string &NeoCreateSignTransactionParams::getSendAddress() const {
    return sendAddress;
}

void NeoCreateSignTransactionParams::setSendAddress(const string &sendAddress) {
    NeoCreateSignTransactionParams::sendAddress = sendAddress;
}

uint64_t NeoCreateSignTransactionParams::getSendValue() const {
    return sendValue;
}

void NeoCreateSignTransactionParams::setSendValue(uint64_t sendValue) {
    NeoCreateSignTransactionParams::sendValue = sendValue;
}

const string &NeoCreateSignTransactionParams::getPassword() const {
    return password;
}

void NeoCreateSignTransactionParams::setPassword(const string &password) {
    NeoCreateSignTransactionParams::password = password;
}

const string &NeoCreateSignTransactionParams::getPriKey() const {
    return priKey;
}

void NeoCreateSignTransactionParams::setPriKey(const string &priKey) {
    NeoCreateSignTransactionParams::priKey = priKey;
}

const vector<BtcvoutForm> &NeoCreateSignTransactionParams::getBtcvoutFormList() const {
    return btcvoutFormList;
}

void
NeoCreateSignTransactionParams::setBtcvoutFormList(const vector<BtcvoutForm> &btcvoutFormList) {
    NeoCreateSignTransactionParams::btcvoutFormList = btcvoutFormList;
}

bool NeoCreateSignTransactionParams::isRecipientsPayFees() const {
    return recipientsPayFees;
}

void NeoCreateSignTransactionParams::setRecipientsPayFees(bool recipientsPayFees) {
    NeoCreateSignTransactionParams::recipientsPayFees = recipientsPayFees;
}

const vector<uint8_t> &NeoCreateSignTransactionParams::getData() const {
    return data;
}

void NeoCreateSignTransactionParams::setData(const vector<uint8_t> &data) {
    NeoCreateSignTransactionParams::data = data;
}

TxType NeoCreateSignTransactionParams::getTxType() const {
    return txType;
}

void NeoCreateSignTransactionParams::setTxType(TxType txType) {
    NeoCreateSignTransactionParams::txType = txType;
}

const string &NeoCreateSignTransactionParams::getAssetId() const {
    return assetId;
}

void NeoCreateSignTransactionParams::setAssetId(const string &assetId) {
    NeoCreateSignTransactionParams::assetId = assetId;
}
