//
//  main.cpp
//  PokerProbCalc
//
//  Created by Kangning Chen on 2015-06-03.
//  Copyright (c) 2015 Kangning Chen. All rights reserved.
//

#include <iostream>
#include <vector>

#include "player.h"
#include "deck.h"

using namespace std;

int readCard(string c) {
    if (c.length() == 2) {
        return 10;
    } else if (c[0] > '1' && c[0] <= '9') {
        return c[0]-'0';
    } else if (c[0] == 'J') {
        return 11;
    } else if (c[0] == 'Q') {
        return 12;
    } else if (c[0] == 'K') {
        return 13;
    } else if (c[0] == 'A') {
        return 14;
    }
    return 0;
}

vector<int> judgeWinners(vector<Player>& players) {
    vector<int> winners;
    winners.push_back(0);
    for (int i = 1; i < players.size(); i++) {
        int result = compare(players[i], players[winners[0]]);
        if (result == -1) continue;
        else if (result == 0) {
            winners.push_back(i);
        } else {
            winners.clear();
            winners.push_back(i);
        }
    }
    
    if (winners.size() == 1){
        players[winners[0]].winHands++;
    } else {
        for (int i = 0; i < winners.size(); i++) {
            players[winners[i]].splitHands++;
        }
    }
    
    return winners;
}

int main(int argc, const char * argv[]) {
    Deck d;
    int M = 100000; // Num of trials
    
    //cout << "Please Enter The Num of Players" << endl;
    int N; cin >> N;
    vector<Player> players(N);
    
    for (int i = 0; i < N; i++){
        //cout << "Please Enter the Hole Hands for player " << i+1 << endl;
        string card1str, card2str;
        cin >> card1str >> card2str;
        Card* X1 = NULL; Card* X2 = NULL;
        while (true) {
            X1 = d.Deal(readCard(card1str.substr(1)), readCard(card1str[0]));
            X2 = d.Deal(readCard(card2str.substr(1)), readCard(card2str[0]));
            if (X1 == NULL || X2 == NULL) {
                cout << "The cards are invalid Please re-enter" << endl;
            } else {
                break;
            }
        }
        players[i].readCard(X1);
        players[i].readCard(X2);
    }
    
    for (int n = 0; n <= 5; n++){
        switch (n) {
            case 0:
                cout << "-------------------Pre Flop--------------------" << endl; break;
            case 4:
                cout << "-------------------Flop------------------------" << endl; break;
            case 5:
                cout << "-------------------Turn------------------------" << endl; break;
            /*case 5:
                cout << "-------------------River-----------------------" << endl; break;*/
            default:
                break;
        }
        
        if (n > 0) {
            Card *X = NULL;
            while (true) {
                string cardstr;
                cin >> cardstr;
                X = d.Deal(readCard(cardstr.substr(1)), readCard(cardstr[0]));
                if (X == NULL) {
                     cout << "The card " << n << " is invalid Please re enter" << endl;
                } else break;
            }
            for (int i = 0; i < N; i++){
                players[i].readCard(X);
            }
        }
        if (n == 1 || n == 2) continue;// No need for first and second FLOP card
        
        /*
         Monte Carlo
         */
        
        int trials = 0;
        if (n == 5) trials = 10000; // no more need if all cards come out
        while (trials++ < M) {
            while (players[0].getNumHands() != 7) {
                Card* new_card = d.Deal();
                //cout << new_card->toString() << " ";
                for (int i = 0; i < N; i++) {
                    players[i].readCard(new_card);
                }
            }
            //cout << endl;
            for (int i = 0; i < N; i++) {
                players[i].genSuite();
            }
            
            vector<int> winners = judgeWinners(players);
            
            if (n == 5) {
                if (winners.size() == 1){
                    cout << "Winner: Player " << winners[0] + 1 << endl;
                } else {
                    cout << "Split by: " << endl;
                    for (int i = 0; i < winners.size(); i++) {
                        cout << "Player " << i+1 << endl;
                    }
                }
                for (int i = 0; i < N; i++) {
                    cout << "Player " << i+1 << " hands: " << players[i].toString() << endl;
                }
                return 0;
            }
            
            d.Shuffle(N*2+n); // keep the player's cards and shuffle remainings
            for (int i = 0; i < N; i++) {
                players[i].removeCards(2+n);
            }
        }
        
        cout << "/* Monte Carlo Simulation */" << endl;
        for (int i = 0; i < N; i++) {
            cout << "Player " << i+1 << ": win " << players[i].winHands << " split " << players[i].splitHands << endl;
            players[i].winHands = 0;
            players[i].splitHands = 0;
        }
        
        
        /*
         Calculate Actual Prob for Turn and River
         */
        if (n == 4 || n == 3) {
            int remainningCards = (int)d.validCards.size();
            
            for (int i = 0; i < remainningCards; i++) {
                if (n == 3) {
                    for (int k = i+1; k < remainningCards; k++) {
                        for (int j = 0; j < N; j++) {
                            players[j].readCard(d.validCards[i]);
                            players[j].readCard(d.validCards[k]);
                            players[j].genSuite();
                        }
                        vector<int> winners = judgeWinners(players);
                        for (int i = 0; i < N; i++) {
                            players[i].removeCards(2+n);
                        }
                    }
                }
                
                if (n == 4) {
                    for (int j = 0; j < N; j++) {
                        players[j].readCard(d.validCards[i]);
                        players[j].genSuite();
                    }
                    vector<int> winners = judgeWinners(players);
                    for (int i = 0; i < N; i++) {
                        players[i].removeCards(2+n);
                    }
                }
                
            }
            
            int totalHands = remainningCards;
            if (n == 3) {
                totalHands = remainningCards * (remainningCards-1)/2;
            }
            
            cout << "/* Actual Probability */" << endl;
            for (int i = 0; i < N; i++) {
                cout << "Player " << i+1 << ": win rate " << players[i].winHands/(double)totalHands << " split rate " << players[i].splitHands/(double)totalHands << endl;
                players[i].winHands = 0;
                players[i].splitHands = 0;
            }
        }
    }
    return 0;
}
