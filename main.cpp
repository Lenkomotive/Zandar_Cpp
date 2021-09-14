//------------------------------------------------------------------------------
// main.cpp
//
// 
// Authors: Mario Kaurin
//------------------------------------------------------------------------------

#include "card.h"
#include "player.h"
#include "deck.h"
#include "game.h"

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


int calcBoardSum(string &board_card, Game* game);                               // forward decleration
int getNextPlayer(int current, int num);
int getPosition(int hand_size);
string getPositions();
int takeOrPut();


enum GlobalVariables                                                            // enum GlobalVariables
{
  EMPTY = 0,
  TAKE = 1,
  PUT = 2,
  JACK = 11,
};


int main()
{

  Game game;                                                                    // create game
  Game* game_ptr = &game;
  game.run();

  Deck deck;                                                                    // creating deck
  Deck* deck_ptr = &deck;

  int num_players = game.getNumPlayers();                                       // determine number of players
  int player_position = 1;                                                      // game starts with first player
  int last_to_take = 1;                                                         // position of player who took last cards (gets all cards from board in the end)
  Player* current_player = game.getPlayer(player_position);                     // pointer to the current player

  while(game.getMaxPoints() < game.getTarget())                                 // while target-score is not reached
  {
    deck.initDeck();                                                            // fill deck with 52 cards
    deck.shuffle();                                                             // shuffle cards in deck
    game.dealToBoard(deck_ptr);                                                 // deal 4 cards to board

    while(deck.getDeckSize() != EMPTY)                                          //playing while deck is not empty
    {
      game.dealToPlayers(deck_ptr);                                             // deal cards to players
      for(int round = 1; round <= num_players * 4; round++)                     // loop for every card (player_num * 4)
      {
        game.printField();                                                      // print game field 
        cout << *current_player;                                                // print players cards
        int hand_size = current_player->getHandSize();                          // hand_size is a parameter for getPosition
        switch (takeOrPut())                                                    // decide whether to take cards or put one down
        {
        case TAKE:                                                              // case TAKE cards from board
          {
            bool correct_sum = false;
            while(!correct_sum)
            {
              int player_hand_pos = getPosition(hand_size);                     // choosing card from hand
              int player_card = current_player->getCardValue(player_hand_pos);  // determine card value
              switch (player_card)                                              // JACK takes entire board, other cards only sum
              {
                case JACK:                                                      // case JACK
                {
                  current_player->cardToStack(player_hand_pos);                 // put players card to stack
                  string all_cards;
                  for(int i = 1; i <= game.getNumCards(); i++)                  
                    all_cards += to_string(i);
                  game.addToPlayersStack(all_cards, player_position);           // add all cards from board to players stack
                  correct_sum = true;
                  last_to_take = player_position;                               // player who took the last cards
                  break;
                }
                default:                                                        // case everything except JACK
                {
                  string board_card_position = getPositions();                  // choosing which cards to take from board
                  int board_sum = calcBoardSum(board_card_position, game_ptr);  // calculating sum of given cards on board
                  if(board_sum == player_card)                                  // check if wanted sum is correct
                  {
                    current_player->cardToStack(player_hand_pos);               // erase players card, erase cards from board and add to players stack
                    game.addToPlayersStack(board_card_position, player_position);
                    correct_sum = true;                                         // escape while loop
                    last_to_take = player_position;                             // player who took the last cards
                  }
                  break;
                }
              }
            }
            player_position = getNextPlayer(player_position, num_players);      // next player
            current_player = game.getPlayer(player_position);                                                                   // while correct_sum is not true
          }
          break;
        case PUT:                                                               // case PUT card to board
         {
            Card* put_card = current_player->getCardForBoard(getPosition(hand_size));// get card pointer and remove from hand
            game.addToBoard(put_card);                                          // add card to board
            player_position = getNextPlayer(player_position, num_players);      // next player
            current_player = game.getPlayer(player_position);
            break;
          }
        }
      }                                                                         // for loop for every card of all players
    }                                                                           // while decksize != EMPTY
    
    game.clearBoard(last_to_take);                                              // deal remainig card to player who took last
    game.calcPoints();                                                          // count points
    game.clearGame();
  }
    
}                                                                               // main


///-----------------------------------------------------------------------------
/// This function returns a player at a given position in the vector.
/// @param int position   this is the index in the vector
/// @return Player*       this is the Player* at given index
int calcBoardSum(string &board_card_position, Game* game)
{
  int board_sum = 0;
  for(size_t i = 0; i < board_card_position.length(); i++)
  {
    int card_position = board_card_position.at(i) - '0';
    board_sum += game->getCardFromBoard(card_position)->getValue();
  }
  return board_sum;
}

///-------------------------------------------------------------------------
/// This function returns a player at a given position in the vector.
/// @param int position   this is the index in the vector
/// @return Player*       this is the Player* at given index
int getNextPlayer(int current, int num)
{ 
  int next = (current < num)? current + 1 : 1;
  return next;
}

///-------------------------------------------------------------------------
/// This function returns a player at a given position in the vector.
/// @param int position   this is the index in the vector
/// @return Player*       this is the Player* at given index
int takeOrPut()
{
  char decision; // t=take, p= put
  while(decision != 't' && decision != 'p')
  {
    cout << "put or take? (p/t): ";
    cin >> decision;
  }
  int dec = (decision == 't')? TAKE : PUT;
  return dec;
}

///-------------------------------------------------------------------------
/// This function returns a player at a given position in the vector.
/// @param int position   this is the index in the vector
/// @return Player*       this is the Player* at given index
int getPosition(int hand_size)
{
  bool correct_input = false;
  int position = 0;
  while(!correct_input)
  {
    cout << "Choose a card in your hand: ";
    cin >> position;
    if(position <= hand_size && position > 0)
      correct_input  = true;    
  }
  return position;
}

///-------------------------------------------------------------------------
/// This function returns a player at a given position in the vector.
/// @param int position   this is the index in the vector
/// @return Player*       this is the Player* at given index
string getPositions()
{
  cout << "Which cards do you want to take? Enter here: ";
  string positions;
  cin >> positions;
  return positions;
}
