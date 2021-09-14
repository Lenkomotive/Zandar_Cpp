////-----------------------------------------------------------------------------
/// game.h
///
/// 
/// Authors: Mario Kaurin
///-----------------------------------------------------------------------------

#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "card.h"
#include "deck.h"
#include <iostream>
#include <vector>

///-----------------------------------------------------------------------------
/// Game contains game specific data like the board and the player information
/// and gameplay relevant functions
class Game
{
  private:
    ///-------------------------------------------------------------------------
    /// board_ is a vector of Card* which contains the cards on the board
    std::vector<Card*> board_;

    ///-------------------------------------------------------------------------
    /// player is a vector of Player* which contains all player instances
    std::vector<Player*> player_;

    ///-------------------------------------------------------------------------
    /// names_ is a vector of strings which is initialised in the constructor
    ///        and used to create Player-instances
    std::vector<std::string> names_;

    ///-------------------------------------------------------------------------
    /// target_ is the target points to get
    int target_;

    ///-------------------------------------------------------------------------
    /// num_palyers_ is the number of players
    int num_players_;

    ///-------------------------------------------------------------------------
    /// This helper function prints "‾" for a given number of times
    /// @param int resize_factor    this is the given number
    void dynamicOverline(int resize_factor) const;

    ///-------------------------------------------------------------------------
    /// This helper function prints " " for a given number of times
    /// @param int resize_factor    this is the given number
    void dynamicSpace(int resize_factor) const;

    ///-------------------------------------------------------------------------
    /// This function prints all cards which are in the vector of Card* board_.
    void printBoard() const;

    ///-------------------------------------------------------------------------
    /// This function prints the results of a round
    void printResults(Player* player) const;


  public:
    ///-------------------------------------------------------------------------
    /// Constructor initialises board_, player_ and names_ with ()
    Game();

    ///-------------------------------------------------------------------------
    /// Copy-Constuctor not needed
    /// @param const Game& game   this is the game that is copied
    Game(const Game& game) = delete; 

    ///-------------------------------------------------------------------------
    /// This function starts a game and creates players
    void run();

    ///-------------------------------------------------------------------------
    /// This function uses the vector of string names_ and creates new players 
    /// and stores them in the vector of Player* player_.
    void createPlayers();

    ///-------------------------------------------------------------------------
    /// This function returns the target-score
    int getTarget() const;

    ///-------------------------------------------------------------------------
    /// This function returns a card from board at a given position
    Card* getCardFromBoard(int position) const;

    ///-------------------------------------------------------------------------
    /// This function returns the target-score
    int getNumPlayers() const;

    ///-------------------------------------------------------------------------
    /// This function returns the target-score
    int getNumCards() const;

    ///-------------------------------------------------------------------------
    /// This function returns the player vector
    std::vector<Player*> getPlayers() const;

    ///-------------------------------------------------------------------------
    /// This function returns a player at a given position in the vector.
    /// @param int position   this is the index in the vector
    /// @return Player*       this is the Player* at given index
    Player* getPlayer (int position) const;

    ///-------------------------------------------------------------------------
    /// This function adds a card to the vector of Cards* board_.
    /// @param Card* card   this is the card to add to the board.
    void addToBoard(Card* card);

    ///-------------------------------------------------------------------------
    /// This function deals the first 4 cards to the board
    /// @param Deck* deck   this is the adress of the deck
    void dealToBoard(Deck* deck);

    ///-------------------------------------------------------------------------
    /// This function deals 4 cards to each of the players
    /// @param Deck* deck   this is the adress of the deck
    void dealToPlayers(Deck* deck);

    ///-------------------------------------------------------------------------
    /// This function prints the board and the player-points table.
    void printField() const;

    ///-------------------------------------------------------------------------
    /// This function returns the maximum points of all players.
    /// @return int   this is the maximum points of the certain player
    int getMaxPoints() const;

    ///-------------------------------------------------------------------------
    /// This function adds cards from board to a players stack
    /// @param std::string board_card_position this is the position of cards in vector
    /// @param int player_position        this is the position of player in vector
    void addToPlayersStack(std::string board_card_position, int player_position);

    ///-------------------------------------------------------------------------
    /// This function add all remaining card left on deck to the player who
    /// took the last cards
    /// @param int last_player    this is the player in player_ vector
    void clearBoard(int last_player);

    ///-------------------------------------------------------------------------
    /// This function counts all clubs and checks whether the player has any
    /// special cards. Futhermore it counts the cards in stack and gives points
    /// to the players based on that information
    void calcPoints();

    ///-------------------------------------------------------------------------
    /// This function function clears the players stack for the next round
    void clearGame();


    ///-------------------------------------------------------------------------
    /// Destructor
    ~Game();
};
#endif //GAME_H