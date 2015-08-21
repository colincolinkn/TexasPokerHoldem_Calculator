//
//  player.h
//  TexasHoldemCalc
//
//  Created by Kangning Chen on 2015-07-03.
//  Copyright (c) 2015 Kangning Chen. All rights reserved.
//

#ifndef __TexasHoldemCalc__player__
#define __TexasHoldemCalc__player__

#include <stdio.h>

#include <iostream>
#include <vector>
#include "card.h"

typedef enum : int {
    NONE,         // for start
    HIGH,
    PAIR,
    TWO_PAIR,
    THREE_OF_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_KIND,
    STRAIGHT_FLUSH
} SuiteType;

/*std::string intToStringPoker(int val) {
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
}*/

inline std::string ToString(SuiteType suitetype) {
    switch (suitetype) {
        case HIGH:
            return "High Cards";
        case PAIR:
            return "One Pair";
        case TWO_PAIR:
            return "Two Pairs";
        case THREE_OF_KIND:
            return "Three of Kind";
        case STRAIGHT:
            return "Straight";
        case FLUSH:
            return "Flush";
        case FULL_HOUSE:
            return "Full House";
        case FOUR_OF_KIND:
            return "Four of Kind";
        case STRAIGHT_FLUSH:
            return "Straigh Flush";
        default:
            return "Invalid Input";
    }
}

class Player {
    std::vector<Card*> all_cards;
    int vals[15];
    int cols[4];
    
    SuiteType suitetype;
    std::vector<int> sorted_cards;
public:
    int winHands;
    int splitHands;
    
    int getNumHands();
    void readCard(Card* card);
    
    void removeCards(int n);
    
    SuiteType getSuiteType();
    std::vector<int> getSortedCards();
    
    std::string toString();
    
    Player();
    
    void genSuite();
};

int compare(Player l, Player r);

#endif /* defined(__TexasHoldemCalc__player__) */
