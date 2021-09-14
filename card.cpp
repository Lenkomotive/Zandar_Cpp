//------------------------------------------------------------------------------
// card.cpp
//
// 
// Authors: Mario Kaurin
//------------------------------------------------------------------------------

#include "card.h"
#include <iostream>

using std::string;

//------------------------------------------------------------------------------
Card::Card(CardType type, std::string picture, int value)
: type_(type), picture_(picture), value_(value)
{
}

//------------------------------------------------------------------------------
CardType Card::getType () const
{
  return type_;
}

//------------------------------------------------------------------------------
string Card::getPicture () const
{
  return picture_;
}

//------------------------------------------------------------------------------
int Card::getValue () const
{
  return value_;
}

//------------------------------------------------------------------------------
bool Card::operator==(const CardType& other)
{
  return (this->getType()  == other);
}

//------------------------------------------------------------------------------
Card::~Card()
{
}