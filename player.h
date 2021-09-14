//------------------------------------------------------------------------------
// player.h
//
// 
// Authors: Mario Kaurin
//------------------------------------------------------------------------------

#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include <string>
#include <vector>
#include <iostream>

///-----------------------------------------------------------------------------
/// Player is a model of a player. 
class Player
{
  private:
    ///-------------------------------------------------------------------------
    /// name_ is the name of the player.
    std::string name_;

    ///-------------------------------------------------------------------------
    /// points_ is the amount of points the player has collected during the game
    int points_;

    ///-------------------------------------------------------------------------
    /// mala_ is true if player has 2 of clubs in stack
    bool mala_;

    ///-------------------------------------------------------------------------
    /// velika_ is true if player has 10 of diamond in stack
    bool velika_;

    ///-------------------------------------------------------------------------
    /// clubs_ is the amount of cards of type clubs in stack
    int clubs_;

    ///-------------------------------------------------------------------------
    /// hand_ is the vector that contains the players cards in his/her hand
    std::vector<Card*> hand_;

    ///-------------------------------------------------------------------------
    /// stack_ contains the collected cards
    std::vector<Card*> stack_;


  public:
    ///-------------------------------------------------------------------------
    /// Constructor without parameters
    Player() = delete;

    ///-------------------------------------------------------------------------
    /// Constructor that inistialises name_ with name, points_ with 0 and hand_
    ///             with ()
    /// @param std::string name   this initialises name_
    Player(std::string name);

    ///-------------------------------------------------------------------------
    /// Copy-Constructor not needed
    /// @param const Player& player   this is the player that is copied
    Player(const Player& player) = delete;

    ///-------------------------------------------------------------------------
    /// This function returns the name of the player
    /// @return std::string   this is the players name
    std::string getName() const;

    ///-------------------------------------------------------------------------
    /// This function returns the length of a players name
    /// @return int   this is the length of the name
    int getNameLen() const;

    ///-------------------------------------------------------------------------
    /// This function returns the value of a card at a given position in hand_
    /// @param int position   this is the position of the card in hand
    /// @return int           this is the cards value
    int getCardValue(int position) const;

    ///-------------------------------------------------------------------------
    /// This function returns the numbers of cards the player holds
    /// @return int   this is the number of cards
    int getHandSize() const;

    ///-------------------------------------------------------------------------
    /// This function returns the nstack of the player
    /// @return std::vector<Card*>    this is the stack
    std::vector<Card*> getStack() const;

    ///-------------------------------------------------------------------------
    /// This function returns the points a players has during the game
    /// @return int   this is the amount of points
    int getPoints() const;

    ///-------------------------------------------------------------------------
    /// This function returns the boolean value whether a player has the 
    /// 2 of clubs
    bool getMala() const;

    ///-------------------------------------------------------------------------
    /// This function returns the boolean value whether a player has the 
    /// 10 of diamond
    bool getVelika() const;

    ///-------------------------------------------------------------------------
    /// This function returns the amount of cards of type clubs in a players
    /// stack
    int getClubs() const;

    ///-------------------------------------------------------------------------
    /// This function sets the variable mala_ to a given value
    /// @param bool result    this is the value
    void setMala(bool value);

    ///-------------------------------------------------------------------------
    /// This function sets the variable velika_ to a given value
    /// @param bool result    this is the value
    void setVelika(bool value);

    ///-------------------------------------------------------------------------
    /// This function sets the variable velika_ to a given value
    /// @param bool result    this is the value
    void setClubs(int value);

    ///-------------------------------------------------------------------------
    /// This function adds 1 to clubs_ once a club card is found in stack
    void addClub();

    ///-------------------------------------------------------------------------
    /// This function adds points to a player account
    /// @param const int points   this the amount of points to be added
    void addPoints(const int points);

    ///-------------------------------------------------------------------------
    /// This function adds a card to the players hand
    /// @param Card* card   this is the card to be added
    void addCard(Card* card);

    ///-------------------------------------------------------------------------
    /// This function adds a card to the players stack
    /// @param Card* card   this is the card to be added
    void addToStack(Card* card);

    ///-------------------------------------------------------------------------
    /// This function removes a card from players hand at a given position and
    /// adds it to the players stack.
    /// @param int position   this is the position
    void cardToStack(int position);

    ///-------------------------------------------------------------------------
    /// This function removes a card from players hand at a given position and
    /// and returns the pointer to this card so the card can be added to the 
    /// board.
    /// @param int card_put_position   this is the position in players hand
    /// @return Card*                  this is the card to add to board
    Card* getCardForBoard(int card_put_position);

    ///-------------------------------------------------------------------------
    /// This operator prints the players name, its cards and the position of 
    /// the cards in its hand
    /// @param std::ostream& stream   this is the out stream
    /// @param const Player& p        this is the player which is to be printed
    /// @return std::stream ostream&  this is the output stream
    friend std::ostream& operator<<(std::ostream& stream, const Player& player);


    ///-------------------------------------------------------------------------
    /// Destructor
    ~Player();
};
#endif // PLAYER_H