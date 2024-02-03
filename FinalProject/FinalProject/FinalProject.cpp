#include <map>
#include <iostream>
#include <vector>
#include <string>
#include "BlackJack.h"
#include "Player.h"
#include "Dealer.h"
#include <cstdlib>
using namespace std;
void calculateResult(Player p, Dealer d);
void playGame(Dealer d, Player p);


void playGame(Dealer d, Player p) {
	p.getInitialTwoCards();
	p.getGivenTwoCardInfo();
	d.getInitialTwoCardsforDealer();
	d.showDealerFirstCardInfo();
	p.userPrompt();
	if (p.getUserInput() == 'x') {
		cout << "-------------------" << endl;
		cout << "Game ends!" << endl;
		cout << "-------------------" << endl;
		exit(0);
		return;
	}
	if (p.getUserInput() != 'x') {	
		while (p.getUserInput() != 's') {
			if (p.getTotalHand() > 21) {
				cout << "------------------------------------" << endl;
				cout << "You got busted!" << endl;
				cout << "Total Hand: " << p.getTotalHand() << endl;
				cout << "Dealer wins!" << endl;
				cout << "------------------------------------" << endl;
				break;
			}
			if (p.getUserInput() == 'x') {
				break;
			}
			p.userPrompt();
			
		
		}
		if (p.getUserInput() == 's') {
			d.playAgainstPlayer(p);
			calculateResult(p, d);
		}
		else {
			playGame(d, p);
		}
		
		
	}

}
void calculateResult(Player p, Dealer d) {
	if (d.isBusted()) {
		playGame(d,p);
	}
	
	if (d.is_Dealer_onStand()) {
		if (d.getTotalHand() > p.getTotalHand()) {
			cout << "-----------------------------------" << endl;
			cout << "Dealer wins!" << endl;
			cout << "Your Hand total: " << p.getTotalHand() << endl;
			cout << "Dealer's Hand total: " << d.getTotalHand() << endl;
			cout << "-----------------------------------" << endl;
			cout << endl;
			playGame(d, p);
		}
		else if (d.getTotalHand() == p.getTotalHand()) {
			cout << "------------------------------------" << endl;
			cout << "Its Draw!" << endl;
			cout << "Your Hand total: " << p.getTotalHand() << endl;
			cout << "Dealer's Hand total: " << d.getTotalHand() << endl;
			cout << "------------------------------------" << endl;
			cout << endl;
			playGame(d, p);
		}
		else {
			cout << "------------------------------------" << endl;
			cout << "You Win!" << endl;
			cout << "Your Hand total: " << p.getTotalHand() << endl;
			cout << "Dealer's Hand total: " << d.getTotalHand() << endl;
			cout << "------------------------------------" << endl;
			cout << endl;
			playGame(d, p);
		}
	}
	
	
}
void showResults(Player p, Dealer d,map<int,vector<int>>&MyMap, int curTotal) {
	vector<int>results(3,0);
	if (MyMap.find(curTotal) == MyMap.end()) {
		MyMap[curTotal] = results;
	}
	if (p.getTotalHand() > 21) {
		//cout << "You got busted! Your hand total: " << p.getTotalHand() << endl;
		MyMap[curTotal].at(2)+=1; return;
	}
	if (d.is_Dealer_onStand()) {
		if (d.getTotalHand() > p.getTotalHand()) {
			//cout << "Dealer wins! Dealer hand total: " << d.getTotalHand() << " > " << "Your hand total: " << p.getTotalHand() << endl;
			MyMap[curTotal].at(2) += 1; return;

		}
		if (d.getTotalHand() == p.getTotalHand()) {
			//cout << "It's Draw!" << endl;
			MyMap[curTotal].at(1) += 1; return;
		}
		if (d.getTotalHand() < p.getTotalHand()) {
			//cout << "You Win!" << endl;
			MyMap[curTotal].at(0) += 1; return;
		}
	}
	if (p.isPlayerTookStand()) {
		d.playAgainstPlayer(p);
		if (d.getTotalHand() > 21) {
			//cout << "Dealer got busted!" << " Dealer's Hand total: " << d.getTotalHand() << endl;
			MyMap[curTotal].at(0)++; return;
		}
		if (d.getTotalHand() < p.getTotalHand()) {
			//cout << "You Win!" << endl;
			MyMap[curTotal].at(0)++; return;
		}
	}
	
}
void generate_Hands(Player p, Dealer d) {
	/*
	loop through 100000 times and 
	each time-->called RandCard function for player--> randomly hit or stand then stop
	dealer play against the player-->Calculate results!
	Print result--> Player starting hand value if he hits or stands--> win lose or draw?
	if(cardSize<100)-->	resetBack to 312 cards;
	
	*/
	int CurrentHandTotal{};
	map<int, vector<int>>myMapForHit;
	map<int, vector<int>>myMapForStand;
	for (int i = 0; i < 100000; i++) {
		p.getInitialTwoCards();
		//cout << "For Starting Hand-->" << p.getTotalHand() << endl;
		CurrentHandTotal = p.getTotalHand();
		d.getInitialTwoCardsforDealer();
		int RandValue = rand() % 2;
		if (RandValue == 1) {
			//hits
			p.Hit();
			d.playAgainstPlayer(p);
			showResults(p, d, myMapForHit,CurrentHandTotal);
		}
		else {
			//cout << "Player stands!" << endl;
			p.Stand();
			d.playAgainstPlayer(p);
			showResults(p, d, myMapForStand,CurrentHandTotal);
		}
		cout << endl;
		cout << endl;
	}

	cout << "When we HIT from starting hand total:::" << endl;
	cout << endl;
	cout << "Starting hand Total\t\tWin\tDraw\tLoss" << endl;
	for (auto i = myMapForHit.begin(); i != myMapForHit.end(); i++) {
		cout << i->first <<"\t\t\t\t" << i->second.at(0) <<'\t' << i->second.at(1)<<"\t" << i->second.at(2) << endl;
	}
	cout << endl;
	cout << endl;
	cout << "When we STAND from starting hand total:::" << endl;
	cout << endl;
	cout << "Starting hand total\t\tWin\tDraw\tLoss" << endl;
	for (auto i = myMapForStand.begin(); i != myMapForStand.end(); i++) {
		cout << i->first <<"\t\t\t\t" << i->second.at(0) << '\t' << i->second.at(1) <<"\t" << i->second.at(2) << endl;
	}
	cout << endl;
	cout << endl;
}
int main()
{
	BlackJack myBlackjack;
	Player johnSmith;
	Dealer abraham;
	int dollarAmount{};
	int totalCash{};
	//cout << "Place your bet: $"; cin >> dollarAmount; cout << endl;
	srand(time(NULL));
	playGame(abraham, johnSmith);
	//generate_Hands(johnSmith, abraham);
	
	
	
	
	
}
