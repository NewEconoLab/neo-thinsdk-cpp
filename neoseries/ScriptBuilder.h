//
// Created by Administrator on 2018/3/18.
//

#ifndef TEST_SCRIPTBUILDER_H
#define TEST_SCRIPTBUILDER_H

#include <json/json.h>
#include "helper.h"
#include "OpCode.h"
#include "bignum.h"

using namespace Json;

namespace neo
{
    class ScriptBuilder {
    public:
        ScriptBuilder();
        ScriptBuilder* Emit(OpCode op, vector<uint8_t> arg);
        ScriptBuilder* EmitAppCall(vector<uint8_t> scriptHash, bool useTailCall = false);
        ScriptBuilder* EmitJump(OpCode op, short offset);
        ScriptBuilder* EmitPushNumber(CBigNum number);
        ScriptBuilder* EmitPushBool(bool data);
        ScriptBuilder* EmitPushBytes(vector<uint8_t> data);
        ScriptBuilder* EmitPushString(string data);
        ScriptBuilder* EmitSysCall(string api);
        ScriptBuilder* EmitParamJson(Json::Value param);
        bool getParamBytes(string str, vector<uint8_t>& data);
        void toRawData(vector<uint8_t>& rawdata);
    private:
        data_chunk data;
        data_sink stream;
        ostream_writer sink;
    };
}



#endif //TEST_SCRIPTBUILDER_H
