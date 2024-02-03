#pragma once
#include "BlackJack.h"
#include <string>
#include<vector>
#include <iostream>
using namespace std;

class Player:public BlackJack {
protected:
	
	Card Card1{};
	Card Card2 {};
	
	int CurrentHandTotal = 0;
	char userInput;
	bool isStand = false;
	bool isPlayerBusted = false;

	void checkForAce(Card& card) {
		if (card.getName() == "Ace") {
			if (this->CurrentHandTotal <= 10) {
				card.setAceValue(card, 11);
			}
			else {
				card.setAceValue(card, 1);
			}
		}
	}
public:
	
	Card getFirstCard() { return this->Card1; }
	Card getSecondCard() { return this->Card2; }
	int getFirstCardValue() { return this->Card1.getValue(); }
	int getSecondCardValue() { return this->Card2.getValue(); }
	string getFirstCardName() { return this->Card1.getName(); }
	string getSecondCardName() { return this->Card2.getName(); }
	string getFirstCardSuitName() { return this->Card1.getSuit(); }
	string getSecondCardSuitName() { return this->Card2.getSuit(); }
	int getTotalHand() { return this->CurrentHandTotal; }
	void getInitialTwoCards() {
		this->Card1 = CallRandomCard();
		this->Card2 = CallRandomCard();
		checkForAce(this->Card1);
		checkForAce(this->Card2);
		this->CurrentHandTotal = this->Card1.getValue() + this->Card2.getValue();
	}
	
	void getGivenTwoCardInfo() {
		cout << "--------------------------------------------------" << endl;
		cout << "Your Initial two Cards' information::" << endl;
		cout << "Card #1" << endl;
		cout << "Name: " << getFirstCardName() << " Suit: " << getFirstCardSuitName() << " Value: " << getFirstCardValue() << endl;
		cout << "Card #2" << endl;
		cout << "Name: " << getSecondCardName() << " Suit: " << getSecondCardSuitName() << " Value: " << getSecondCardValue() << endl;
		cout << "----------------------------------------------------" << endl;
		cout << endl;
	}
	void userPrompt() {
		cout << "Hit or Stand?\n press H or h for Hit\n press S or s for Stand\n press x or X for Exit" << endl;
		cin >> this->userInput;
		if (this->userInput == 's' || this->userInput == 'S') {
			Stand();
			
		}
		else if (this->userInput == 'h' || this->userInput == 'H') {
			Hit();
		}
		else if (this->userInput == 'x' || this->userInput == 'X') {
			return;
		}
		else {
			cout << "Invalid input!" << endl;
		}
	}
	char getUserInput() { return this->userInput; }
	bool isBlackJack() {
		return this->CurrentHandTotal == 21;
	}
	bool canHit() { return this->CurrentHandTotal <= 21; }
	bool canStand() { return this->CurrentHandTotal <= 21; }
	bool isBusted() { return this->CurrentHandTotal > 21; }
	
	void Hit() {
		Card newCard = CallRandomCard();
		//comment this part out for NOW!
		checkForAce(newCard);
		
		cout << "----------------------------------------------" << endl;
		cout << "Hit Called!" << endl;
		cout << "Card Info::" << endl;
		cout << "Name: " << newCard.getName() << " Suit: " << newCard.getSuit() << " Value: " << newCard.getValue() << endl;
		cout << "----------------------------------------------" << endl;
		this->CurrentHandTotal += newCard.getValue();
		/*if (this->CurrentHandTotal > 21) {
			cout << "You got Busted!" << endl;
			cout << "Dealer wins!" << endl;
			return;
		}*/
	}
	bool isPlayerTookStand() { return this->isStand; }
	void Stand() {
		//cout << "Dealer's turn!" << endl;
		this->isStand = true;
		
	}
};