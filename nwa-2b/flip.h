#ifndef FLIP_CLASS
#define FLIP_CLASS

#include <iostream>
#include "d_except.h"
#include "d_node.h"

//club is 0, diamond is 1, heart is 2, spade is 3

using namespace std;

class card
{
public:
	card(int newValue, int newSuit);
	card(const card &aCard);
	void setValue(int newValue);
	void setSuit(int newSuit);
	int getValue() const;
	int getSuit() const;
	friend ostream &operator << (ostream &ostr, const card &aCard);
	card &operator = (const card &c);
private:
	int value;
	int suit;
};

card::card(int newValue = 1, int newSuit = 0){
	setValue(newValue);
	setSuit(newSuit);
}
card& card::operator=(const card &c)
{
	setValue(c.getValue());
	setSuit(c.getSuit());
	return *this;
}

card::card(const card &aCard)
{
	setValue(aCard.getValue());
	setSuit(aCard.getSuit());
}

void card::setValue(int newValue)
{
	//setting the card value to newValue
	//Exception handling of invalid value range
	if (newValue < 1 || newValue > 13)
	{throw rangeError("Invalid card value");}
	else {value = newValue;}
}
void card::setSuit(int newSuit)
{
	//setting the card suit to newSuit
	//Exception handling of invalid suit range (0 representing clubs, and so on.
	if (!(newSuit == 0 || newSuit == 1 || newSuit == 2 || newSuit == 3))
	{
		throw baseException("Invalid Suit");
	}

	else{
		suit = newSuit;}
}

int card::getValue() const{
	return value;
}

int card::getSuit() const{
	return suit;
}

ostream &operator(ostream &ostr, const card &aCard)
{
	int pValue = aCard.getValue();
	int pSuit = aCard.getSuit();

	//Value range is 1-13, 10 represents Jack, 11 Queen, and so on.
	if (pValue == 10){
		ostr << "Jack";
	}
	if (pValue == 11){
		ostr << "Queen";
	}
	if (pValue == 12){
		ostr << "King";
	}
	if (pValue == 13){
		ostr << "Ace";
	}
	else{
		ostr << pValue << " ";
	}

	//suit range is 0-3, again 0 representing clubs and so on
	if (pSuit == 0){
		ostr << "Clubs";
	}
	if (pSuit == 1){
		ostr << "Diamonds";
	}
	if (pSuit == 2){
		ostr << "Hearts";
	}
	if (pSuit == 3){
		ostr << "Spades";
	}

	ostr << endl;
}



template<typename T>
class deck{
public:
	deck();
	friend ostream &operator << (ostream &ostr, const deck &aDeck);
	~deck();
	card deal();
	void replace(card n);
	void shuffle();
private:
	node<card> *front; //front pointer to the first card node
};

deck::deck(){
	front = NULL;
	node<card> *nodePtr;

	//Adding cards from the back forward 
	//i represents the suits, from clubs(0) to spades(3), while j represents the card values (including jacks, kings, queen and ace)
	for (int i = 0; i >= 3; i--){
		for (int j = 13; j >= 1; j--){
			nodePtr = new node<card>(card(j,i), front);
			front = nodePtr;
		}
	}
}

void deck::shuffle(){
	/*using a loop, at each step you should detect two nodes from the deck which are selected randomly and swap their values. for loop from 1 to 52*/
}

deck::~deck(){
	node<card> *curr;
	curr = front;
	while(curr!=NULL){
		delete curr->nodeValue;
		curr = curr->next;
	}
}

card deck::deal(){
	node<card> *temp;
	temp = front;
	front = front->next;
	temp->next = NULL;

	return temp->nodeValue;
}
void deck::replace(card n){
	node<card> *curr;
	curr = front;
	while (curr->next!=NULL){
		curr = curr->next;
	}
	curr->next = new node<card>(n);
}

//print the cards in each deck, in order.
friend ostream &operator << (ostream &ostr, const deck &aDeck){
	node<card> *ptr = aDeck.front;

	//Scanning all cards in the deck and printing each one.
	while(ptr!=NULL){
		cout << ptr->nodeValue;
		ptr = ptr->next;
	}
}

#endif