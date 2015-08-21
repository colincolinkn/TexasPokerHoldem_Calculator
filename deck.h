//
//  deck.h
//  TexasHoldemCalc
//
//  Created by Kangning Chen on 2015-07-03.
//  Copyright (c) 2015 Kangning Chen. All rights reserved.
//

#ifndef __TexasHoldemCalc__deck__
#define __TexasHoldemCalc__deck__

#include <stdio.h>

#include <iostream>
#include <vector>
#include "card.h"

class Deck {
    std::vector<Card*> inValidCards;
public:
    std::vector<Card*> validCards;
    
    Deck();
    
    void Shuffle(int n);
    
    void Shuffle();
    
    Card* Deal();
    
    Card* Deal(int index);
    
    Card* Deal(int val, Color col);
    
    ~Deck();
};


#endif /* defined(__TexasHoldemCalc__deck__) */
