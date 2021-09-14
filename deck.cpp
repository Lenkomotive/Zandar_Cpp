//------------------------------------------------------------------------------
// deck.cpp
//
// 
// Authors: Mario Kaurin
//------------------------------------------------------------------------------

#include "deck.h"
#include <fstream>
#include <cstdlib>
#include <ctime>

using std::vector;
using std::string;
using std::cout;
using std::endl;

//------------------------------------------------------------------------------
Deck::Deck(): deck_()
{
}

//------------------------------------------------------------------------------
vector<Card*> Deck::getDeck() const
{
  return deck_;
}

//------------------------------------------------------------------------------
void Deck::initDeck()
{
  std::ifstream cardfile("cardfile.txt");
  string card;
  CardType type = CardType::HEART;
  int value = 1;

  while (getline (cardfile, card))
  {
    if(card == "SPADE")
    {
      type = CardType::SPADE;
      value = 1;
      continue;
    }
    if(card == "DIAMOND")
    {
      type = CardType::DIAMOND;
      value = 1;
      continue;
    }
    if(card == "CLUBS")
    {
      type = CardType::CLUBS;
      value = 1;
      continue;
    }
    deck_.push_back(new Card(type, card, value));
    value++;
  }
  cardfile.close();
}

//------------------------------------------------------------------------------
void Deck::shuffle()
{
  Card* temp;
  int range = 52;
  int swap = 0;
  int deck = 51;

  srand((int)time(0));

  for(int loop = 0; loop < 52; loop++)
  {
    swap = (rand() % 52);
    temp = deck_.at(swap);
    deck_.at(swap) = deck_.at(deck);
    deck_.at(deck) = temp;
    deck--;
    range--;
  }
}

//------------------------------------------------------------------------------
int Deck::getDeckSize() const
{
  return static_cast<int>(deck_.size());
}

//------------------------------------------------------------------------------
Card* Deck::operator-()
{
  Card* last = deck_.back();
  deck_.pop_back();
  return last;
}

//------------------------------------------------------------------------------
bool Deck::operator!= (const int& target)
{
  return (this->getDeckSize() != target);
}

//------------------------------------------------------------------------------
Deck::~Deck()
{
}
