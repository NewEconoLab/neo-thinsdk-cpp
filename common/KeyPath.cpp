//
//  KeyPath.cpp
//  Test
//
//  Created by xgc on 12/19/17.
//  Copyright © 2017 xgc. All rights reserved.
//

#include "KeyPath.hpp"

KeyPath::KeyPath()
{
    path1 = -1;
    path2 = -1;
    path3 = -1;
    path4 = -1;
    path5 = -1;
    hd1 = false;
    hd2 = false;
    hd3 = false;
    hd4 = false;
    hd5 = false;
}

int KeyPath::getPath1()
{
    return path1;
}

int KeyPath::getPath2()
{
    return path2;
}

int KeyPath::getPath3()
{
    return path3;
}

int KeyPath::getPath4()
{
    return path4;
}

int KeyPath::getPath5()
{
    return path5;
}

string KeyPath::getSymbol()
{
    return symbol;
}

bool KeyPath::getHd1()
{
    return hd1;
}

bool KeyPath::getHd2()
{
    return hd2;
}

bool KeyPath::getHd3()
{
    return hd3;
}

bool KeyPath::getHd4()
{
    return hd4;
}

bool KeyPath::getHd5()
{
    return hd5;
}

void KeyPath::setPath1(int path1)
{
    this->path1 = path1;
}

void KeyPath::setPath2(int path2)
{
    this->path2 = path2;
}

void KeyPath::setPath3(int path3)
{
    this->path3 = path3;
}

void KeyPath::setPath4(int path4)
{
    this->path4 = path4;
}

void KeyPath::setPath5(int path5)
{
    this->path5 = path5;
}

void KeyPath::setSymbol(string symbol)
{
    this->symbol = symbol;
}

void KeyPath::setHd1(bool hd1)
{
    this->hd1 = hd1;
}

void KeyPath::setHd2(bool hd2)
{
    this->hd2 = hd2;
}

void KeyPath::setHd3(bool hd3)
{
    this->hd3 = hd3;
}

void KeyPath::setHd4(bool hd4)
{
    this->hd4 = hd4;
}

void KeyPath::setHd5(bool hd5)
{
    this->hd5 = hd5;
}
