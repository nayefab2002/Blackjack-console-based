#pragma once
#include<map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace std;

class BlackJack {
protected:
	class Card {
	public:
		string name;
		string suit;
		int value;
		Card(string name="", string suit="", int value=0) {
			this->name = name; this->suit = suit; this->value = value;
		}
		string getName() { return this->name; }
		string getSuit() { return this->suit; }
		int getValue() { return this->value; }
		void setAceValue(Card& card, int numValue) {
			card.value = numValue;
		}
	};
	class Deck {
	public:
		int numSuits = 4;
		int numRanks = 13;
		int numCards = numSuits * numRanks;
		
		
		vector<Card> getDeck() {
			vector<Card>cards;
			string suit = "";
			string name = "";
			int value = 0;
			int CardIndex = 0;
			for (int i = 1; i <= numSuits; i++) {
				for (int j = 1; j <= numRanks; j++) {
					switch (i) {
					case 1:suit = "Clubs"; break;
					case 2:suit = "Diamonds"; break;
					case 3:suit = "Hearts"; break;
					case 4:suit = "Spades"; break;
					}
					switch (j)
					{
					case 1:name = "Ace"; value = 1; break;
					case 2:name = "Two"; value = 2; break;
					case 3:name = "Three"; value = 3; break;
					case 4:name = "Four"; value = 4; break;
					case 5:name = "Five"; value = 5; break;
					case 6:name = "Six"; value = 6; break;
					case 7:name = "Seven"; value = 7; break;
					case 8:name = "Eight"; value = 8; break;
					case 9:name = "Nine"; value = 9; break;
					case 10:name = "Ten"; value = 10; break;
					case 11:name = "Jack"; value = 10; break;
					case 12:name = "Queen"; value = 10; break;
					case 13:name = "King"; value = 10; break;
					default:
						break;
					}
					Card newCard = Card(name, suit, value);
					cards.push_back(newCard);
				}
				

			}
			
			return cards;
		}
		vector<Card> getSixDeckCards() {
			vector<Card> sixDecksCards;
			for (int i = 0; i < 6; i++) {
				auto oneDeckCards = getDeck();
				for (int i = 0; i < oneDeckCards.size(); i++) {
					sixDecksCards.push_back(oneDeckCards.at(i));
				}
			}
			return sixDecksCards;
		}
	};
	Deck myDeck;
	vector<Card> myCards = myDeck.getSixDeckCards();
	int currentShoeSize = myCards.size();

	
	
public:
	Card CallRandomCard() {
		
		if (this->myCards.size() < 100) {
			resetCards();
		}
		int RandValue = rand() % this->myCards.size();
		Card randomCard= this->myCards.at(RandValue);
		this->currentShoeSize--;
		this->myCards.erase(myCards.begin() + RandValue);
		return randomCard;
	}
	void swapCards(vector<Card>Cards,int firstIndex, int secondIndex) {
		Card temp = Cards.at(firstIndex);
		Cards.at(firstIndex) = Cards.at(secondIndex);
		Cards.at(secondIndex) = temp;
	}
	void shuffleCards(vector<Card>Cards) {
		int numCards = Cards.size();
		srand(time(0));
		for (int i = 0; i < numCards; i++) {
			int randValue = i + (rand() % (numCards - i));
			swapCards(Cards,i,randValue);
		}
	}
	int getShoeSize() { return this->myCards.size(); }
	void resetCards() {
		this->myCards = myDeck.getSixDeckCards();
	}
};