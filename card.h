//------------------------------------------------------------------------------
// card.h
//
// 
// Authors: Mario Kaurin
//------------------------------------------------------------------------------

#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>

///-----------------------------------------------------------------------------
/// CardType is a enum class of cardtypes
enum class CardType
{
  DIAMOND, HEART, CLUBS, SPADE
};

///-----------------------------------------------------------------------------
/// Card is a model of a card
class Card
{
  private:
    ///-------------------------------------------------------------------------
    /// type_ is the type of the card
    CardType type_;

    ///-------------------------------------------------------------------------
    /// picture_ is the picture of the card
    std::string picture_;
    
    ///-------------------------------------------------------------------------
    /// value_ is the value of the card
    int value_;


  public:
    ///-------------------------------------------------------------------------
    /// Constructor without parameters
    ///
    Card() = delete;

    ///-------------------------------------------------------------------------
    /// Constructor with multiple parametes
    /// @param CardType type       this initialises type_
    /// @param std::string picture this initialises picture_
    /// @param int value           this initialises value_
    Card(CardType type, std::string picture, int value);

    ///-------------------------------------------------------------------------
    /// Copy-Constuctor not needed
    /// @param const Card& c    this is the card that is copied
    Card(const Card& c) = delete;

    ///-------------------------------------------------------------------------
    /// This function returns the cards type
    /// @return Cardtype    this is the type
    CardType getType () const;

    ///-------------------------------------------------------------------------
    /// This function returnes the cards picture
    /// @return std::string   this is the picture
    std::string getPicture () const;

    ///-------------------------------------------------------------------------
    /// This function returns the cards value
    /// @return int   this is the value
    int getValue () const;

    ///-------------------------------------------------------------------------
    /// This operator checks if given card it of a given type
    /// @param const CardType& other    this is the card type to compare
    /// @return bool                    this is the result (true/false)
    bool operator== (const CardType& other);


    ///-------------------------------------------------------------------------
    /// Destructor
    ~Card();
};
#endif // CARD_H