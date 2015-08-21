//
//  card.cpp
//  TexasHoldemCalc
//
//  Created by Kangning Chen on 2015-07-03.
//  Copyright (c) 2015 Kangning Chen. All rights reserved.
//

#include "card.h"
#include <iostream>

using namespace std;

Card::Card(int _val, Color _col) {
    this->val = _val;
    this->col = _col;
    str = intToStringPoker(_val);
}

string Card::toString() {
    string res = "";
    res += ToChar(col);
    res += str;
    return res;
}