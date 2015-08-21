//
//  player.cpp
//  TexasHoldemCalc
//
//  Created by Kangning Chen on 2015-07-03.
//  Copyright (c) 2015 Kangning Chen. All rights reserved.
//

#include "player.h"

using namespace std;

int Player::getNumHands() {
    return (int)all_cards.size();
}

void Player::readCard(Card* card) {
    all_cards.push_back(card);
    vals[card->val]++;
    cols[card->col]++;
}

void Player::removeCards(int n) {
    while (all_cards.size() > n) {
        Card* lastCard = all_cards.back();
        vals[lastCard->val]--;
        cols[lastCard->col]--;
        all_cards.pop_back();
    }
    suitetype = SuiteType::NONE;
    sorted_cards.clear();
}

SuiteType Player::getSuiteType() {
    return suitetype;
}

vector<int> Player::getSortedCards() {
    return sorted_cards;
}

string Player::toString() {
    string res = ToString(suitetype) + " ";
    for (int i = 0; i < sorted_cards.size(); i++) {
        res += intToStringPoker(sorted_cards[i]) + " ";
    }
    return  res;
}

Player::Player() {
    suitetype = SuiteType::NONE;
    for (int i = 1; i < 15; i++) {
        vals[i] = 0;
    } for (int i = 0; i < 4; i++) {
        cols[i] = 0;
    }
    winHands = 0;
    splitHands = 0;
}

void Player::genSuite() {
    if (suitetype != SuiteType::NONE) return;
    
    sorted_cards.clear();
    /*
     STRAIGHT_FLUSH
     */
    int max_suite_col = 0;
    int suite_col = -1;
    for (int i = 0; i < 4; i++) {
        if (cols[i] > max_suite_col) {
            max_suite_col = cols[i];
            suite_col = i;
        }
    }
    
    bool is_flush = false;
    
    int table[15]; // vals on most color
    for (int i = 0; i < 15; i++) {
        table[i] = 0;
    }
    
    for(int i = 0; i < all_cards.size(); i++) {
        if (all_cards[i]->col == suite_col)
            table[all_cards[i]->val]++;
        if (all_cards[i]->val == 14) {
            table[1]++;
        }
    }
    
    if (max_suite_col >= 5) {
        is_flush = true;
        
        int count = 0;
        for (int i = 14; i > 0 ; i--) {
            if (table[i] > 0) {
                count++;
            } else {
                count = 0;
            }
            if (count == 5) {
                suitetype = SuiteType::STRAIGHT_FLUSH;
                sorted_cards.push_back(i); // store first element of straight in sorted_cards;
                return;
            }
        }
    }
    /*
     FOUR_OF_KIND
     */
    for (int i = 14; i > 0; i--) {
        if (vals[i] == 4) {
            suitetype = SuiteType::FOUR_OF_KIND;
            sorted_cards.push_back(i);
            for (int j = 14; j > 1; j--) {
                if (j == i) continue;
                if (vals[j] > 0) {
                    sorted_cards.push_back(j); // second large
                    return;
                }
            }
        }
    }
    
    /*
     FULL HOUSE
     */
    bool is_three_kinds = false;
    int three_of_kinds_val = -1;
    for (int i = 14; i > 0; i--) {
        if (vals[i] == 3) {
            is_three_kinds = true;
            three_of_kinds_val = i;
            for (int j = 14; j > 1; j--) {
                if (j == i) continue;
                if (vals[j] >= 2) {
                    sorted_cards.push_back(i);
                    sorted_cards.push_back(j); // second large
                    suitetype = SuiteType::FULL_HOUSE;
                    return;
                }
            }
        }
    }
    
    /*
     FLUSH
     */
    if (is_flush) {
        suitetype = SuiteType::FLUSH;
        for (int i = 14; i > 1 ; i--) {
            if (table[i] > 0) {
                sorted_cards.push_back(i);
            }
        }
        return;
    }
    
    
    /*
     STRAIGHT
     */
    int count = 0;
    for (int i = 14; i > 0 ; i--) {
        if (i == 1 && vals[14] > 0) {
            count++;
        } else if (vals[i] > 0) {
            count++;
        } else {
            count = 0;
        }
        if (count == 5) {
            suitetype = SuiteType::STRAIGHT;
            sorted_cards.push_back(i); // store first element of straight in sorted_cards;
            return;
        }
    }
    
    /*
     THREE_OF_KIND
     */
    if (is_three_kinds) {
        suitetype = SuiteType::THREE_OF_KIND;
        sorted_cards.push_back(three_of_kinds_val);
        int j;
        for (j = 14; j > 1; j--) {
            if (j == three_of_kinds_val) continue;
            if (vals[j] > 0 && sorted_cards.size() < 3) {
                sorted_cards.push_back(j); // largest high card
            }
        }
        return;
    }
    
    /*
     TWO_PAIR, ONE_PAIR and HIGH_CARDS
     */
    for (int i = 14; i > 1; i--) {
        if (vals[i] == 2 && sorted_cards.size() < 2) {
            sorted_cards.push_back(i);
        }
    }
    
    if (sorted_cards.size() == 2) {
        // two pairs
        for (int j = 14; j > 1; j--) {
            if (vals[j] > 0 && j != sorted_cards[0] && j != sorted_cards[1]) {
                sorted_cards.push_back(j);
                suitetype = SuiteType::TWO_PAIR;
                return;
            }
        }
    } else if (sorted_cards.size() == 1) {
        // one pair
        for (int j = 14; j > 1; j--) {
            if (vals[j] == 1 && sorted_cards.size() < 4) {
                sorted_cards.push_back(j);
            }
        }
        suitetype = SuiteType::PAIR;
        return;
    } else {
        // high cards
        for (int j = 14; j > 1; j--) {
            if (vals[j] == 1 && sorted_cards.size() < 5) {
                sorted_cards.push_back(j);
            }
        }
        suitetype = SuiteType::HIGH;
        return;
    }
}

int compare(Player l, Player r) {
    if (l.getSuiteType() < r.getSuiteType()) {
        return -1;
    } else if (l.getSuiteType() > r.getSuiteType()){
        return 1;
    } else {
        vector<int> sorted_l = l.getSortedCards();
        vector<int> sorted_r = r.getSortedCards();
        for (int i = 0; i < sorted_l.size(); i++) {
            if (sorted_l[i] < sorted_r[i]) {
                return -1;
            } else if (sorted_l[i] > sorted_r[i]) {
                return 1;
            }
        }
        return 0;
    }
}