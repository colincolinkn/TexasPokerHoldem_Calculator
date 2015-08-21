//
//  deck.cpp
//  TexasHoldemCalc
//
//  Created by Kangning Chen on 2015-07-03.
//  Copyright (c) 2015 Kangning Chen. All rights reserved.
//

#include "deck.h"


Deck::Deck() {
    for (int i = 0; i < 52; i++) {
        Color col = Color(i/13);
        int val = i%13 + 2;
        Card* c = new Card(val, col);
        validCards.push_back(c);
    }
}

void Deck::Shuffle(int n) {
    while (inValidCards.size() > n) {
        validCards.push_back(inValidCards.back());
        inValidCards.pop_back();
    }
}

void Deck::Shuffle() {
    Shuffle(0);
}

Card* Deck::Deal() {
    int mod = (int)validCards.size();
    int k = rand()%mod;
    Card* newCard = validCards[k];
    inValidCards.push_back(newCard);
    validCards.erase(validCards.begin()+k);
    return newCard;
}

Card* Deck::Deal(int index) { // try dealing one card
    if (validCards.size() > 0) {
        return validCards[index];
    }
    return NULL;
}

Card* Deck::Deal(int val, Color col) {
    for (int i = 0; i< validCards.size(); i++) {
        if (validCards[i]->val == val && validCards[i]->col == col) {
            Card* newCard = validCards[i];
            inValidCards.push_back(newCard);
            validCards.erase(validCards.begin()+i);
            return newCard;
        }
    }
    return NULL;
}

Deck::~Deck() {
    for (int i = 0; i < validCards.size(); i++) {
        delete validCards[i];
    }
    for (int i = 0; i < inValidCards.size(); i++) {
        delete inValidCards[i];
    }
}
