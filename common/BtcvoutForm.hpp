//
//  BtcvoutForm.hpp
//  Test
//
//  Created by xgc on 12/22/17.
//  Copyright © 2017 xgc. All rights reserved.
//

#ifndef BtcvoutForm_hpp
#define BtcvoutForm_hpp

#include <string>
using namespace std;

class BtcvoutForm
{
public:
    BtcvoutForm() {coinBase = false;}
    BtcvoutForm(string hash, uint64_t value, int n, bool coinBase);
    
    string getHash();
    void setHash(string hash);
    uint64_t getValue();
    void setValue(uint64_t value);
    int getN();
    void setN(int n);
    bool getCoinBase();
    void setCoinBase(bool coinBase);
private:
    string hash;
    uint64_t value;
    int n;
    bool coinBase;
};

#endif /* BtcvoutForm_hpp */
