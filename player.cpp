//------------------------------------------------------------------------------
// player.cpp
//
// 
// Authors: Mario Kaurin
//------------------------------------------------------------------------------

#include "player.h"
#include <string>

using std::string;
using std::cout;
using std::endl;

//------------------------------------------------------------------------------
Player::Player(std::string name)
: name_(name), points_(0), mala_(false), velika_(false), clubs_(0),
  hand_(), stack_()
{
}

//------------------------------------------------------------------------------
string Player::getName() const
{
  return name_;
}

//------------------------------------------------------------------------------
int Player::getNameLen() const
{
  return static_cast<int>(name_.length());
}

//------------------------------------------------------------------------------
int Player::getCardValue(int position) const
{
  return hand_.at(position - 1)->getValue();
}

//------------------------------------------------------------------------------
int Player::getHandSize() const
{
  return static_cast<int>(hand_.size());
}

//------------------------------------------------------------------------------
std::vector<Card*> Player::getStack() const
{
  return stack_;
}

//------------------------------------------------------------------------------
int Player::getPoints() const
{
  return points_;
}

//------------------------------------------------------------------------------
bool Player::getMala() const
{
  return mala_;
}

//------------------------------------------------------------------------------
bool Player::getVelika() const
{
  return velika_;
}

//------------------------------------------------------------------------------
int Player::getClubs() const
{
  return clubs_;
}

//------------------------------------------------------------------------------
void Player::setMala(bool value)
{
  mala_ = value;
}

//------------------------------------------------------------------------------
void Player::setVelika(bool value)
{
  velika_ = value;
}

//------------------------------------------------------------------------------
void Player::setClubs(int value)
{
  clubs_ = value;
}

//------------------------------------------------------------------------------
void Player::addClub()
{
  clubs_++;
}

//------------------------------------------------------------------------------
void Player::addPoints(const int points)
{
  points_ += points;
}

//------------------------------------------------------------------------------
void Player::addCard(Card* card)
{
  hand_.push_back(card);
}

//------------------------------------------------------------------------------
void Player::addToStack(Card* card)
{
  stack_.push_back(card);
}

//------------------------------------------------------------------------------
void Player::cardToStack(int position)
{
  stack_.push_back(hand_.at(position - 1));
  hand_.erase(hand_.begin() + position - 1);
}

//------------------------------------------------------------------------------
Card* Player::getCardForBoard(int card_put_position)
{
  Card* for_board = hand_.at(card_put_position - 1);
  hand_.erase(hand_.begin() + card_put_position - 1);
  return for_board;
}

//------------------------------------------------------------------------------
std::ostream& operator<< (std::ostream& stream, const Player& player) 
{
  stream << "\n\n" << player.getName() << ": ";
  for(auto& element: player.hand_)
    stream << element->getPicture() << "  ";
  stream << "\n";
  int len = player.getNameLen() + 2;
  for(int space = 0; space < len; space++)
    stream << " ";
  int size = player.getHandSize();
  for(int position = 1; position <= size; position++)
    if(position < 10)
      stream << position << "  ";
    else
      stream << position << " ";
  stream << "\n――――――――――――――――――――――――――――――――――――――――――――――\n";
  return stream;
}

//------------------------------------------------------------------------------
Player::~Player()
{
}