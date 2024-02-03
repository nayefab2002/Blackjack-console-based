#pragma once
#include "BlackJack.h"
#include <vector>
#include <string>
#include "Player.h"
using namespace std;

class Dealer : public BlackJack{
private:
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
	Card Card1 {};
	Card Card2 {};
	int CurrentHandTotal = 0;
	
	bool isStand = false;

public:
	void getInitialTwoCardsforDealer() {
		this->Card1 = CallRandomCard();
		this->Card2 = CallRandomCard();
		checkForAce(this->Card1);
		checkForAce(this->Card2);
		this->CurrentHandTotal = this->Card1.getValue() + this->Card2.getValue();
	}
	int getFirstFaceUpCardValue() {
		return this->Card1.getValue();
	}
	void showDealerFirstCardInfo() {
		cout << "----------------------------------------------" << endl;
		cout << "Dealer first Card information" << endl;
		cout << "Name: " << this->Card2.getName() << " Suit: " << this->Card2.getSuit() << " Value: " << this->Card2.getValue() << endl;
		cout << "----------------------------------------------" << endl;
		cout << endl;
	}
	bool isBusted() {
		return this->CurrentHandTotal > 21;
	}
	bool canHit() {
		return this->CurrentHandTotal <= 17;
	}
	bool canStand() {
		return this->CurrentHandTotal > 17;
	}

	bool is_Dealer_onStand() { return this->isStand; }

	int getTotalHand() { return this->CurrentHandTotal; }

	void playAgainstPlayer(Player& player) {
		int playerFirstCard = player.getFirstCardValue();
		int playerSecondCard = player.getSecondCardValue();
		int total = playerFirstCard + playerSecondCard;
		if (this->CurrentHandTotal >= 17 && this->CurrentHandTotal <= 21) {
			Stand();
			cout << "Dealer stands!" << endl;
			cout << "Dealer's Hand total: " << this->CurrentHandTotal << endl;
			cout << endl;

		}
		while (this->CurrentHandTotal < 17) {
			cout << "Dealer Hits!" << endl;
			Hit();
		}
		
			
	}
	void Hit() {
		
		Card newCard= CallRandomCard();
		checkForAce(newCard);
		this->CurrentHandTotal += newCard.getValue();
		if (this->CurrentHandTotal > 21) {
			cout << "Dealer got Busted!" << endl;
			cout << "Dealer's Hand total: " << this->CurrentHandTotal << endl;
			return;
			
		}
		if (this->CurrentHandTotal >= 17 && this->CurrentHandTotal <= 21) {
			Stand();
			cout << "Dealer stands!" << endl;
			cout << "Dealer's Hand total: " << this->CurrentHandTotal << endl;
			return;
			
		}
		
	}
	void Stand() {
		this->isStand = true;
	}
};