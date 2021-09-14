///-----------------------------------------------------------------------------
/// deck.h
///
/// 
/// Authors: Mario Kaurin
///-----------------------------------------------------------------------------

#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <string>
#include <iostream>
#include <vector>

///-----------------------------------------------------------------------------
/// Deck is a model of a card deck
class Deck
{
  private:
    ///-------------------------------------------------------------------------
    /// deck_ is the Card-deck of 52 Cards
    ///
    std::vector <Card*> deck_;


  public:
    ///-------------------------------------------------------------------------
    /// Constructor
    Deck();

    ///-------------------------------------------------------------------------
    /// Copy-Constructor
    /// @param const Deck& deck   this is the deck that is copied
    Deck(const Deck& deck) = delete;


    ///-------------------------------------------------------------------------
    /// This function returns the vector of Card* deck_
    /// @return std::vector<Card*>    this is the deck
    std::vector<Card*> getDeck() const;

    ///-------------------------------------------------------------------------
    /// This function initialises the deck_ with Card*
    void initDeck();

    ///-------------------------------------------------------------------------
    /// This function shuffles the card in the deck randomly
    void shuffle();

    ///-------------------------------------------------------------------------
    /// This function returns the number of cards in the deck
    /// @return int   this is the number of cards
    int getDeckSize() const;

    ///-------------------------------------------------------------------------
    /// This operator deletes the last card of the deck and returns the pointer
    /// @return Card*   this is the pointer to the last card
    Card* operator-();

    ///-------------------------------------------------------------------------
    /// This operator checks whether the target points are reached
    /// @param const int& target    this is the target value
    /// @return bool                this is the result (true/false)
    bool operator!= (const int& target);

    ///-------------------------------------------------------------------------
    /// Destructor
    ~Deck();
};
#endif // DECK_H