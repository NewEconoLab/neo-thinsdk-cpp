//
// Created by Administrator on 2018/3/18.
//

#include "ScriptBuilder.h"
#include "utils/Common.h"

namespace neo
{
    ScriptBuilder::ScriptBuilder():
            stream(data), sink(stream)
    {

    }

    ScriptBuilder* ScriptBuilder::Emit(OpCode op, vector<uint8_t> arg)
    {
        sink.write_byte((uint8_t)op);
        if (arg.size() != 0)
            sink.write_bytes(&arg[0], arg.size());
        return this;
    }

    ScriptBuilder* ScriptBuilder::EmitAppCall(vector<uint8_t> scriptHash, bool useTailCall)
    {
        if(scriptHash.size() != 20) {
            throw new exception();
        }
        return Emit(useTailCall ? OpCode::TAILCALL : OpCode::APPCALL, scriptHash);
    }

    ScriptBuilder* ScriptBuilder::EmitJump(OpCode op, short offset)
    {
        if (op != OpCode::JMP && op != OpCode::JMPIF && op != OpCode::JMPIFNOT && op != OpCode::CALL)
            throw new exception();
        byte_array<2> tmArray;
        std::memcpy(tmArray.data(), (uint8_t*) &offset, sizeof(short));
        vector<uint8_t> voffset(tmArray.begin(), tmArray.end());
        return Emit(op, voffset);
    }

    ScriptBuilder* ScriptBuilder::EmitPushNumber(CBigNum number)
    {
        vector<uint8_t> dummyData;
        if (number == -1) return Emit(OpCode::PUSHM1, dummyData);
        if (number == 0) return Emit(OpCode::PUSH0, dummyData);
        if (number > 0 && number <= 16) {
            OpCode code = (OpCode)(OpCode::PUSH1 - 1 + (uint8_t)number.getuint());
            return Emit(code, dummyData);
        }

        return EmitPushBytes(number.getvch());
    }

    ScriptBuilder* ScriptBuilder::EmitPushBool(bool data)
    {
        vector<uint8_t> dummyData;
        return Emit(data ? OpCode::PUSHT : OpCode::PUSHF, dummyData);
    }

    ScriptBuilder* ScriptBuilder::EmitPushBytes(vector<uint8_t> data)
    {
        vector<uint8_t> dummyData;
        int size = data.size();
        if (size <= (int)OpCode::PUSHBYTES75)
        {
            sink.write_byte((uint8_t)size);
            sink.write_bytes(&data[0], size);
        }
        else if (size < 0x100)
        {
            Emit(OpCode::PUSHDATA1, dummyData);
            sink.write_byte((uint8_t)size);
            sink.write_bytes(&data[0], size);
        }
        else if (size < 0x10000)
        {
            Emit(OpCode::PUSHDATA2, dummyData);
            sink.write_2_bytes_little_endian((uint16_t)size);
            sink.write_bytes(&data[0], size);
        }
        else// if (data.Length < 0x100000000L)
        {
            Emit(OpCode::PUSHDATA4, dummyData);
            sink.write_4_bytes_little_endian((uint32_t)size);
            sink.write_bytes(&data[0], size);
        }
        return this;
    }

    ScriptBuilder* ScriptBuilder::EmitPushString(string str)
    {
        vector<uint8_t> hexdata;
        hexdata.assign(str.begin(), str.end());
        EmitPushBytes(hexdata);
        return this;
    }

    ScriptBuilder* ScriptBuilder::EmitSysCall(string api)
    {
        if(api.length() == 0)
            throw new exception();
        vector<uint8_t> hexdata;
        hexdata.assign(api.begin(), api.end());

        int len = hexdata.size();
        if(len == 0 || len > 252)
            throw new exception();
        vector<uint8_t> arg;
        arg.push_back((uint8_t)len);
        arg.insert(arg.end(), hexdata.begin(), hexdata.end());
        return Emit(OpCode::SYSCALL, arg);
    }

    ScriptBuilder* ScriptBuilder::EmitParamJson(Json::Value param)
    {
        if(param.isBool()) {
            EmitPushBool(param.asBool());
        }
        else if(param.isInt()) {
            EmitPushNumber(param.asInt());
        }
        else if(param.isInt64()) {
            EmitPushNumber(param.asInt64());
        }
        else if(param.isArray()) {
            int size = param.size();
            for(int i = size - 1; i >= 0; i--) {
                EmitParamJson(param[i]);
            }
            EmitPushNumber(size);
            vector<uint8_t> dummyData;
            Emit(OpCode::PACK, dummyData);
        }
        else if(param.isString()) {
            string str = param.asString();
            vector<uint8_t> hexdata;
            getParamBytes(str, hexdata);
            EmitPushBytes(hexdata);
        }
        else {
            throw new exception();
        }
        return this;
    }

    bool ScriptBuilder::getParamBytes(string str, vector<uint8_t>& data)
    {
        if(str[0] != '(')
            return false;

        string strData;

        if(str.find("(str)") == 0) {
            strData = str.substr(5);
            std::copy(strData.begin(), strData.end(), data.begin());
        }
        else if(str.find("(string)") == 0) {
            strData = str.substr(8);
            std::copy(strData.begin(), strData.end(), data.begin());
        }
        else if(str.find("(bytes)") == 0) {
            strData = str.substr(7);
            data = fromUserHex(strData);
        }
        else if(str.find("([])") == 0) {
            strData = str.substr(4);
            data = fromUserHex(strData);
        }
        else if(str.find("(address)") == 0) {
            strData = str.substr(9);
            short_hash pubHash = getPublicKeyHashFromAddress(strData);
            data.assign(pubHash.begin(), pubHash.end());
        }
        else if(str.find("(addr)") == 0) {
            strData = str.substr(6);
            short_hash pubHash = getPublicKeyHashFromAddress(strData);
            data.assign(pubHash.begin(), pubHash.end());
        }
        else if(str.find("(integer)") == 0) {
            strData = str.substr(9);

            BIGNUM *bn = BN_new();
            int ret = BN_dec2bn(&bn, strData.c_str());
            char* pHex = BN_bn2hex(bn);

            CBigNum num;
            num.SetHex(pHex);

            data = num.getvch();
            BN_free(bn);
            OPENSSL_free(pHex);
        }
        else if(str.find("(int)") == 0) {
            strData = str.substr(5);

            BIGNUM *bn = BN_new();
            int ret = BN_dec2bn(&bn, strData.c_str());
            char* pHex = BN_bn2hex(bn);

            CBigNum num;
            num.SetHex(pHex);

            data = num.getvch();
            BN_free(bn);
            OPENSSL_free(pHex);
        }
        else if(str.find("(hexinteger)") == 0) {
            strData = str.substr(12);

            data = fromUserHex(strData);
            reverse(data.begin(), data.end());
        }
        else if(str.find("(hexint)") == 0) {
            strData = str.substr(8);

            data = fromUserHex(strData);
            reverse(data.begin(), data.end());
        }
        else if(str.find("(hex)") == 0) {
            strData = str.substr(5);

            data = fromUserHex(strData);
            reverse(data.begin(), data.end());
        }
        else if(str.find("(hex256)") == 0 || str.find("(int256)") == 0) {
            strData = str.substr(8);

            data = fromUserHex(strData);
            if(data.size() != 32)
                return false;
            reverse(data.begin(), data.end());
        }
        else if(str.find("(uint256)") == 0) {
            strData = str.substr(9);

            data = fromUserHex(strData);
            if(data.size() != 32)
                return false;
            reverse(data.begin(), data.end());
        }
        else if(str.find("(hex160)") == 0 || str.find("(int160)") == 0) {
            strData = str.substr(8);

            data = fromUserHex(strData);
            if(data.size() != 20)
                return false;
            reverse(data.begin(), data.end());
        }
        else if(str.find("(uint160)") == 0) {
            strData = str.substr(9);

            data = fromUserHex(strData);
            if(data.size() != 20)
                return false;
            reverse(data.begin(), data.end());
        }
        else {
            return false;
        }

        return true;
    }

    void ScriptBuilder::toRawData(vector<uint8_t>& rawdata)
    {
        stream.flush();
        rawdata.assign(data.begin(), data.end());
    }
}
