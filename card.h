//
//  card.h
//  TexasHoldemCalc
//
//  Created by Kangning Chen on 2015-07-03.
//  Copyright (c) 2015 Kangning Chen. All rights reserved.
//

#ifndef __TexasHoldemCalc__card__
#define __TexasHoldemCalc__card__

#include <stdio.h>
#include <iostream>

typedef enum : int {
    HEART,
    CLUB,
    SPADE,
    DIAMOND,
    INVALID
} Color;

inline Color readCard(char c) {
    switch (c) {
        case 'H':
            return Color::HEART;
        case 'S':
            return Color::SPADE;
        case 'D':
            return Color::DIAMOND;
        case 'C':
            return Color::CLUB;
        default:
            return Color::INVALID;
    }
}

struct Card {
    int val;
    Color col;
    std::string str;
    
    Card(int _val, Color _col);
    
    std::string toString();
};

inline char ToChar (Color col) {
    switch (col) {
        case HEART:
            return 'H';
        case CLUB:
            return 'C';
        case SPADE:
            return 'S';
        case DIAMOND:
            return 'D';
        default:
            return 'N'; // Invalid
    }
}

inline std::string intToStringPoker(int val) {
    std::string str;
    if (val <= 9) {
        str = '0' + val;
    } else if (val == 10) {
        str = "10";
    } else if (val == 11) {
        str = "J";
    } else if (val == 12) {
        str = "Q";
    } else if (val == 13) {
        str = "K";
    } else if (val == 14) {
        str = "A";
    }
    return str;
}

#endif /* defined(__TexasHoldemCalc__card__) */
