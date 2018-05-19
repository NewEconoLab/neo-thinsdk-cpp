//
// Created by Administrator on 2018/3/18.
//

#include "neo_transaction.h"
#include "ScriptBuilder.h"

namespace neo
{
    void InvokeTransData::Serialize(Transaction& trans, writer& sink)
    {
        uint64_t len = script.size();
        Transaction::writeVarInt(sink, len);
        sink.write_bytes(&script[0], len);
        if(trans.version >= 1) {
            sink.write_8_bytes_little_endian(gas.value);
        }
    }

    void InvokeTransData::Deserialize(Transaction& trans, reader& sink)
    {
        uint64_t len = sink.read_8_bytes_little_endian();
        data_chunk data = sink.read_bytes(len);
        script.clear();
        script.assign(data.begin(), data.end());
        if(trans.version >= 1) {
            gas.value = sink.read_8_bytes_little_endian();
        }
    }

    string Witness::getAddress()
    {
        auto hash = getScriptHashFromScript(VerificationScript);
        return getAddressFromScriptHash(hash);
    }

    string Witness::getHashStr()
    {
        auto hash = getScriptHashFromScript(VerificationScript);
        string strHash = HexStr(hash.begin(), hash.end(), false);
        return strHash;
    }

    bool Witness::isSmartContract()
    {
        if(VerificationScript.size() != 35)
            return true;
        if(VerificationScript[0] != VerificationScript.size() - 2)
            return true;
        if(VerificationScript[VerificationScript.size() - 1] != 0xac)
            return true;
        return false;
    }

    void Transaction::writeVarInt(writer& sink, uint64_t value)
    {
        if (value > 0xffffffff)
        {
            sink.write_byte((uint8_t)(0xff));
            sink.write_8_bytes_little_endian(value);
        }
        else if (value > 0xffff)
        {
            sink.write_byte((uint8_t)(0xfe));
            sink.write_4_bytes_little_endian(value);
        }
        else if (value > 0xfc)
        {
            sink.write_byte((uint8_t)(0xfd));
            sink.write_2_bytes_little_endian(value);
        }
        else
        {
            sink.write_byte((uint8_t)(value));
        }
    }

    uint64_t Transaction::readVarInt(reader& sink, uint64_t max)
    {
        uint8_t fb = (uint8_t)sink.read_byte();
        uint64_t value = 0;

        data_chunk data;
        if (fb == 0xfd)
        {
            value = sink.read_2_bytes_little_endian();
        }
        else if (fb == 0xfe)
        {
            value = sink.read_4_bytes_little_endian();
        }
        else if (fb == 0xff)
        {
            value = sink.read_8_bytes_little_endian();
        }
        else
            value = fb;

        return value;
    }

    bool Transaction::getMessage(vector<uint8_t>& rawData)
    {
        data_chunk data;
        data_sink stream(data);
        ostream_writer sink(stream);
        SerializeUnsigned(sink);
        stream.flush();
        rawData.assign(data.begin(), data.end());

        return true;
    }

    bool Transaction::getRawData(vector<uint8_t>& rawData)
    {
        data_chunk data;
        data_sink stream(data);
        ostream_writer sink(stream);
        Serialize(sink);
        stream.flush();
        rawData.assign(data.begin(), data.end());

        return true;
    }

    bool Transaction::getHash(vector<uint8_t>& hash)
    {
        data_chunk data;
        data_sink stream(data);
        ostream_writer sink(stream);
        Serialize(sink);
        stream.flush();
        hash.assign(data.begin(), data.end());

        return true;
    }

    void Transaction::AddWitness(vector<uint8_t> signData, vector<uint8_t> pubkey, string addrs)
    {
        data_chunk data;
        data_sink stream(data);
        ostream_writer sink(stream);
        SerializeUnsigned(sink);
        stream.flush();

        vector<uint8_t> msg;
        msg.assign(data.begin(), data.end());

        bool bSign = VerifySignature(msg, signData, pubkey);
        if(bSign == false)
            throw new exception();

        string addr = getAddressFromPublicKey(&pubkey[0]);
        if(addr != addrs)
            throw new exception();

        uint8_t p_publicKey[ECC_BYTES + 1] = {0};
        std::memcpy(p_publicKey, &pubkey[0], ECC_BYTES + 1);
        data_slice vscript = getScriptFromPublicKey(p_publicKey);

        ScriptBuilder sb;
        sb.EmitPushBytes(signData);

        vector<uint8_t> iscript;
        sb.toRawData(iscript);

        vector<uint8_t> script(vscript.begin(), vscript.end());
        AddWitnessScript(script, iscript);
    }

    bool Transaction::AddWitnessScript(vector<uint8_t>& script, vector<uint8_t>& iscript)
    {
        short_hash scripthash = getScriptHashFromScript(script);
        Witness newwit;
        newwit.VerificationScript = script;
        newwit.InvocationScript = iscript;

        int size = witnesses.size();
        for(int i = 0; i < size; i++) {
            Witness tmpwit = witnesses[i];
            string tmpAddr = tmpwit.getAddress();
            string newAddr = newwit.getAddress();
            if(tmpAddr == newAddr)
                return false;
        }

        witnesses.push_back(newwit);
        return true;
    }

    void Transaction::SerializeUnsigned(writer& sink)
    {
        sink.write_byte((uint8_t)type);
        sink.write_byte(version);

        if(type == TransactionType::ContractTransaction) {

        }
        else if(type == TransactionType::InvocationTransaction) {
            extdata->Serialize(*this, sink);
        }
        else
        {
            throw new exception();
        }

        uint64_t attrSize = (uint64_t)attributes.size();
        writeVarInt(sink, attrSize);
        for(int i = 0; i < (int)attrSize; i++) {
            vector<uint8_t> attriData = attributes[i].data;
            uint8_t usage = attributes[i].usage;

            if(usage == TransactionAttributeUsage::ContractHash || usage == TransactionAttributeUsage::Vote ||
                    (usage >= TransactionAttributeUsage::Hash1 && usage <= TransactionAttributeUsage::Hash15)) {
                sink.write_bytes(&attriData[0], 32);
            }
            else if (usage == TransactionAttributeUsage::ECDH02 || usage == TransactionAttributeUsage::ECDH03)
            {
                sink.write_bytes(&attriData[1], 32);
            }
            else if (usage == TransactionAttributeUsage::Script)
            {
                sink.write_bytes(&attriData[0], 20);
            }
            else if (usage == TransactionAttributeUsage::DescriptionUrl)
            {
                uint8_t len = attriData.size();
                sink.write_byte(len);
                sink.write_bytes(&attriData[0], len);
            }
            else if (usage == TransactionAttributeUsage::Description || usage >= TransactionAttributeUsage::Remark)
            {
                int len = (int)attriData.size();
                writeVarInt(sink, (unsigned int)len);
                sink.write_bytes(&attriData[0], len);
            }
            else
            {
                throw new exception();
            }
        }

        uint32_t countInputs = (uint32_t) inputs.size();
        writeVarInt(sink, countInputs);
        for(uint32_t i = 0; i < countInputs; i++) {
            TransactionInput input = inputs[i];
            sink.write_bytes(&input.hash[0], input.hash.size());
            sink.write_2_bytes_little_endian(input.index);
        }

        uint32_t countOutputs = (uint32_t)outputs.size();
        writeVarInt(sink, countOutputs);

        for(uint32_t j = 0; j < countOutputs; j++) {
            TransactionOutput output = outputs[j];
            sink.write_bytes(output.assetId);

            sink.write_8_bytes_little_endian(output.value.value);
            sink.write_bytes(output.toAddress);
        }

    }

    void Transaction::Serialize(writer& sink)
    {
        SerializeUnsigned(sink);

        uint64_t size = (uint64_t) witnesses.size();
        writeVarInt(sink, size);

        for(int i = 0; i < (int)size; i++) {
            Witness _witness = witnesses[i];
            writeVarInt(sink, (uint64_t) _witness.InvocationScript.size());
            sink.write_bytes(&_witness.InvocationScript[0], _witness.InvocationScript.size());
            writeVarInt(sink, (uint64_t) _witness.VerificationScript.size());
            sink.write_bytes(&_witness.VerificationScript[0], _witness.VerificationScript.size());
        }
    }

    void Transaction::Deserialize(reader& sink)
    {
        this->type = (TransactionType)sink.read_byte();
        this->version = sink.read_byte();

        if(this->type == TransactionType::ContractTransaction) {
            extdata = NULL;
        }
        else if(this->type == TransactionType::InvocationTransaction) {
            extdata = new InvokeTransData();
        }
        else
        {
            throw new exception();
        }

        if(extdata != NULL) {
            extdata->Deserialize(*this, sink);
        }

        uint64_t countAttri = readVarInt(sink);
        for(uint64_t i = 0; i < countAttri; i++) {
            data_chunk attriData;
            uint8_t usage = sink.read_byte();

            if(usage == TransactionAttributeUsage::ContractHash || usage == TransactionAttributeUsage::Vote ||
                    (usage >= TransactionAttributeUsage::Hash1 && usage <= TransactionAttributeUsage::Hash15)) {
                attriData = sink.read_bytes(32);
            }
            else if(usage == TransactionAttributeUsage::ECDH02 || usage == TransactionAttributeUsage::ECDH03) {
                attriData.push_back(usage);
                data_chunk tmp = sink.read_bytes(32);
                attriData.insert(attriData.end(), tmp.begin(), tmp.end());
            }
            else if(usage == TransactionAttributeUsage::Script) {
                attriData = sink.read_bytes(20);
            }
            else if(usage == TransactionAttributeUsage::DescriptionUrl) {
                uint8_t len = sink.read_byte();
                attriData = sink.read_bytes(len);
            }
            else if(usage == TransactionAttributeUsage::Description || usage >= TransactionAttributeUsage::Remark) {
                uint32_t len = (uint32_t)readVarInt(sink, 65535);
                attriData = sink.read_bytes(len);
            }
            else
            {
                throw new exception();
            }
        }

        uint64_t countInputs = readVarInt(sink);
        for(uint64_t i = 0; i < countInputs; i++) {
            TransactionInput input;
            input.hash = sink.read_bytes(32);
            input.index = sink.read_2_bytes_little_endian();

            this->inputs.push_back(input);
        }

        uint64_t countOutputs = readVarInt(sink);
        for(uint64_t j = 0; j < countOutputs; j++) {
            TransactionOutput output;

            output.assetId = sink.read_bytes(32);
            output.value.value = sink.read_8_bytes_little_endian();
            output.toAddress = sink.read_bytes(20);

            this->outputs.push_back(output);
        }
    }
}
