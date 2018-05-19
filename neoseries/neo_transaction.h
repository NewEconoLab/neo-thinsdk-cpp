//
// Created by Administrator on 2018/3/18.
//

#ifndef TEST_TRANSACTION_H
#define TEST_TRANSACTION_H

#include <vector>
#include "helper.h"
#include "serialize.h"
#include "hash.h"
using namespace std;

namespace neo
{
    enum TransactionType
    {
        /// <summary>
        /// 用于分配字节费的特殊交易
        /// </summary>
                MinerTransaction = 0x00,
        /// <summary>
        /// 用于分发资产的特殊交易
        /// </summary>
                IssueTransaction = 0x01,
        /// <summary>
        /// 用于分配小蚁币的特殊交易
        /// </summary>
                ClaimTransaction = 0x02,
        /// <summary>
        /// 用于报名成为记账候选人的特殊交易
        /// </summary>
                EnrollmentTransaction = 0x20,
        /// <summary>
        /// 用于资产登记的特殊交易
        /// </summary>
                RegisterTransaction = 0x40,
        /// <summary>
        /// 合约交易，这是最常用的一种交易
        /// </summary>
                ContractTransaction = 0x80,
        /// <summary>
        /// Publish scripts to the blockchain for being invoked later.
        /// </summary>
                PublishTransaction = 0xd0,
        InvocationTransaction = 0xd1
    };

    enum TransactionAttributeUsage
    {
        /// <summary>
        /// 外部合同的散列值
        /// </summary>
                ContractHash = 0x00,

        /// <summary>
        /// 用于ECDH密钥交换的公钥，该公钥的第一个字节为0x02
        /// </summary>
                ECDH02 = 0x02,
        /// <summary>
        /// 用于ECDH密钥交换的公钥，该公钥的第一个字节为0x03
        /// </summary>
                ECDH03 = 0x03,

        /// <summary>
        /// 用于对交易进行额外的验证
        /// </summary>
                Script = 0x20,

        Vote = 0x30,

        DescriptionUrl = 0x81,
        Description = 0x90,

        Hash1 = 0xa1,
        Hash2 = 0xa2,
        Hash3 = 0xa3,
        Hash4 = 0xa4,
        Hash5 = 0xa5,
        Hash6 = 0xa6,
        Hash7 = 0xa7,
        Hash8 = 0xa8,
        Hash9 = 0xa9,
        Hash10 = 0xaa,
        Hash11 = 0xab,
        Hash12 = 0xac,
        Hash13 = 0xad,
        Hash14 = 0xae,
        Hash15 = 0xaf,

        /// <summary>
        /// 备注
        /// </summary>
        Remark = 0xf0,
        Remark1 = 0xf1,
        Remark2 = 0xf2,
        Remark3 = 0xf3,
        Remark4 = 0xf4,
        Remark5 = 0xf5,
        Remark6 = 0xf6,
        Remark7 = 0xf7,
        Remark8 = 0xf8,
        Remark9 = 0xf9,
        Remark10 = 0xfa,
        Remark11 = 0xfb,
        Remark12 = 0xfc,
        Remark13 = 0xfd,
        Remark14 = 0xfe,
        Remark15 = 0xff
    };

    class Attribute {
    public:
        TransactionAttributeUsage usage;
        vector<uint8_t> data;
    };

    struct Fixed8
    {
        const uint64_t D = 100000000;
        uint64_t value;
    };

    struct TransactionOutput
    {
        vector<uint8_t> assetId;
        Fixed8 value;
        vector<uint8_t> toAddress;
    };

    struct TransactionInput
    {
        vector<uint8_t> hash;
        uint16_t index;
    };

    class Witness
    {
    public:
        string getAddress();
        string getHashStr();
        bool isSmartContract();
    public:
        vector<uint8_t> InvocationScript;//设置参数脚本，通常是吧signdata push进去
        vector<uint8_t> VerificationScript;//校验脚本，通常是 push 公钥, CheckSig 两条指令   验证的东西就是未签名的交易
    };

    class Transaction;

    class IExtData
    {
    public:
        virtual void Serialize(Transaction& trans, writer& sink) {};
        virtual void Deserialize(Transaction& trans, reader& sink) {};
    };

    class InvokeTransData : public IExtData
    {
    public:
        void Serialize(Transaction& trans, writer& sink);
        void Deserialize(Transaction& trans, reader& sink);

        vector<uint8_t> script;
        Fixed8 gas;
    };

    class Transaction
    {
    public:
        void SerializeUnsigned(writer& sink);
        void Serialize(writer& sink);
        void Deserialize(reader& sink);

        bool getMessage(vector<uint8_t>& rawData);
        bool getRawData(vector<uint8_t>& rawData);
        void AddWitness(vector<uint8_t> signData, vector<uint8_t> pubkey, string addrs);
        bool AddWitnessScript(vector<uint8_t>& script, vector<uint8_t>& iscript);

        bool getHash(vector<uint8_t>& hash);

        static void writeVarInt(writer& sink, uint64_t value);
        static uint64_t readVarInt(reader& sink, uint64_t max = 9007199254740991);
    public:
        TransactionType type;
        uint8_t version;
        vector<Attribute> attributes;
        vector<TransactionInput> inputs;
        vector<TransactionOutput> outputs;
        vector<Witness> witnesses;
        IExtData* extdata;
    };
}



#endif //TEST_TRANSACTION_H
