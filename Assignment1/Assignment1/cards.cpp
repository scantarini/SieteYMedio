#include <cstdlib>
#include <iostream>
#include "cards.h"

/*
You might or might not need these two extra libraries
#include <iomanip>
#include <algorithm>
*/


/* *************************************************
Card class
************************************************* */

/*
Default constructor for the Card class.
It could give repeated cards. This is OK.
Most variations of Blackjack are played with
several decks of cards at the same time.
*/
Card::Card() {
	int r = 1 + rand() % 4;
	switch (r) {
	case 1: suit = OROS; break;
	case 2: suit = COPAS; break;
	case 3: suit = ESPADAS; break;
	case 4: suit = BASTOS; break;
	default: break;
	}

	r = 1 + rand() % 10;
	switch (r) {
	case  1: rank = AS; break;
	case  2: rank = DOS; break;
	case  3: rank = TRES; break;
	case  4: rank = CUATRO; break;
	case  5: rank = CINCO; break;
	case  6: rank = SEIS; break;
	case  7: rank = SIETE; break;
	case  8: rank = SOTA; break;
	case  9: rank = CABALLO; break;
	case 10: rank = REY; break;
	default: break;
	}
}

// Accessor: returns a string with the suit of the card in Spanish 
string Card::get_spanish_suit() const {
	string suitName;
	switch (suit) {
	case OROS:
		suitName = "oros";
		break;
	case COPAS:
		suitName = "copas";
		break;
	case ESPADAS:
		suitName = "espadas";
		break;
	case BASTOS:
		suitName = "bastos";
		break;
	default: break;
	}
	return suitName;
}

// Accessor: returns a string with the rank of the card in Spanish 
string Card::get_spanish_rank() const {
	string rankName;
	switch (rank) {
	case AS:
		rankName = "As";
		break;
	case DOS:
		rankName = "Dos";
		break;
	case TRES:
		rankName = "Tres";
		break;
	case CUATRO:
		rankName = "Cuatro";
		break;
	case CINCO:
		rankName = "Cinco";
		break;
	case SEIS:
		rankName = "Seis";
		break;
	case SIETE:
		rankName = "Siete";
		break;
	case SOTA:
		rankName = "Sota";
		break;
	case CABALLO:
		rankName = "Caballo";
		break;
	case REY:
		rankName = "Rey";
		break;
	default: break;
	}
	return rankName;
}



// Accessor: returns a string with the suit of the card in English 
// This is just a stub! Modify it to your liking.
string Card::get_english_suit() const {
	string suitName;
	switch (suit) {
	case OROS:
		suitName = "coins";
		break;
	case COPAS:
		suitName = "cups";
		break;
	case ESPADAS:
		suitName = "spades";
		break;
	case BASTOS:
		suitName = "clubs";
		break;
	default: break;
	}
	return suitName;
}

// Accessor: returns a string with the rank of the card in English 
// This is just a stub! Modify it to your liking.
string Card::get_english_rank() const {
	string rankName;
	switch (rank) {
	case AS:
		rankName = "Ace";
		break;
	case DOS:
		rankName = "Two";
		break;
	case TRES:
		rankName = "Three";
		break;
	case CUATRO:
		rankName = "Four";
		break;
	case CINCO:
		rankName = "Five";
		break;
	case SEIS:
		rankName = "Six";
		break;
	case SIETE:
		rankName = "Seven";
		break;
	case SOTA:
		rankName = "Jack";
		break;
	case CABALLO:
		rankName = "Knight";
		break;
	case REY:
		rankName = "King";
		break;
	default: break;
	}
	return rankName;
}



// Assigns a numerical value to card based on rank.
// AS=1, DOS=2, ..., SIETE=7, SOTA=10, CABALLO=11, REY=12
int Card::get_rank() const {
	return static_cast<int>(rank) + 1;
}

// Comparison operator for cards
// Returns TRUE if card1 < card2
bool Card::operator < (Card card2) const {
	return rank < card2.rank;
}



/* *************************************************
Hand class
************************************************* */
// Implemente the member functions of the Hand class here.
Hand::Hand()
{
	scoreTotal = 0;
}
void Hand::SetScoreTotal(double newValue)
{
	scoreTotal = newValue;
}
double Hand::GetScoreTotal() const
{
	return scoreTotal;
}
void Hand::InsertCard()
{
	Card newCard;
	double cardScore;

	// Increase the cumulative points of the cards in the hand (add 0.5 if newCard is a face card)
	cardScore = newCard.get_rank();
	if (cardScore > 7) scoreTotal += 0.5;
	else scoreTotal += cardScore;


	// Adds a card to an empty hand
	if (cards.empty())
	{
		cards.push_back(newCard);
		return;
	}

	// Adds a card to an existing hand such that the elements of the vector increase in rank as the index increases (adds card in order)
	for (int i = 0; i < cards.size(); i++)
	{
		if (newCard < cards[i])
		{
			cards.insert(cards.begin() + i, newCard);
			break;
		}
	}


}
void Hand::Clear()
{
	// remove the cards from the hand as well as the points associated with the hand
	SetScoreTotal(0);
	cards.clear();
}


/* *************************************************
Player class
************************************************* */
// Implemente the member functions of the Player class here.
Player::Player()
{
	bet = 0;
	SetBank(100);
}
// This is the implementation for the provided constructor. It is not necessary.
Player::Player(int m)
{
	money = m;
}

// This modifies the amount of money the player has
void Player::SetBank(int newBankBalance)
{
	money += newBankBalance;
}

// This returns the amount of money the player has
int Player::GetBank() const
{
	return money;
}

void Player::SetBet()
{
	bool acceptableInput = false;

	// Takes in the player's bet
	// Error checks for negative numbers, non-integer types, and inputs that exceed the amount of money the player has.
	do 
	{
		cout << "You have $" << GetBank() << ". ";
		cout << "Enter bet: ";
		if (!(cin >> bet))
		{
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Invalid: Input must be a number. Please try again\n";
		}
		else if (!bet)
			cout << "Invalid: Player cannot bet $0. Please try again.\n";
		else if (bet < 0)
			cout << "Invalid: Input must be positve. Please try again.\n";
		else
			acceptableInput = true;
	} while (!acceptableInput);
}