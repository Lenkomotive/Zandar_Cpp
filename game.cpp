//------------------------------------------------------------------------------
// game.cpp
//
// 
// Authors: Mario Kaurin
//------------------------------------------------------------------------------

#include "game.h"
#include <bits/stdc++.h> // erase
#include <string>

using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::endl;

//------------------------------------------------------------------------------
Game::Game(): board_(), player_(), names_()
{
}

//------------------------------------------------------------------------------
void Game::run()
{
  // get number of players
  cout << "How many players want to play Žandar?\nEnter here: ";
  cin >> num_players_;

  // get players names and pushback into name_vector
  cout << "\nPlease enter the player names\n";
  for(int player = 1; player <= num_players_; player ++)
  {
    cout << "Player " << player << ": ";
    string name;
    cin >> name;
    names_.push_back(name);
  }

  // get target score
  cout << "\nUp to what target-score do You wish to play?\nEnter here: ";
  cin >> target_;
  cout << "\n\n";

  // create players with gathered data
  createPlayers();
}

//------------------------------------------------------------------------------
void Game::createPlayers()
{
  for(auto &name: names_)
  {
    player_.push_back(new Player(name));
  }
}

//------------------------------------------------------------------------------
int Game::getTarget() const
{
  return target_;
}

//------------------------------------------------------------------------------
Card* Game::getCardFromBoard(int position) const
{
  return board_.at(position - 1);
}

//------------------------------------------------------------------------------
int Game::getNumPlayers() const
{
  return num_players_;
}

//------------------------------------------------------------------------------
int Game::getNumCards() const
{
  return board_.size();
}

vector<Player*> Game::getPlayers() const
{
  return player_;
} 

//------------------------------------------------------------------------------
Player* Game::getPlayer(int position) const
{
  return player_.at(position - 1);
}

//------------------------------------------------------------------------------
void Game::addToBoard(Card* card)
{
  board_.push_back(card);
}

//------------------------------------------------------------------------------
void Game::dealToBoard(Deck* deck)
{
  for(int i = 1; i <= 4; i++)
    addToBoard(-*deck);
}

//------------------------------------------------------------------------------
void Game::dealToPlayers(Deck* deck)
{
  for(auto &player : player_)
  {
    for(int i = 1; i <= 4; i++)
      player->addCard(-*deck);
  }
}

//------------------------------------------------------------------------------
void Game::printField() const
{
  // Pointer to last player
  Player* last = player_.at(player_.size() - 1);

  // variables for dynamic board
  bool need_resize = false;
  if(board_.size() > 5)
    need_resize = true;
  int resize_factor = (board_.size() - 5) * 4;
  
  cout << "――――――――――――――――――――――――――――――――――――――――――――――\n";
  // space board to player-points table
  cout << "                         ";
  if(need_resize)
    dynamicSpace(resize_factor);

  //                         name|name2
  for(auto player: player_)
  {
    cout << player->getName();
    if(player != last)
      cout << "|";
  }

  // ‾‾‾BOARD‾‾‾‾‾‾‾‾‾‾‾    ‾‾‾‾‾|‾‾‾‾‾‾
  cout << "\n‾‾‾BOARD‾‾‾‾‾‾‾‾‾‾‾‾";
  if(need_resize)
    dynamicOverline(resize_factor);

  cout << "    ‾";

  for(auto player: player_)
  {
    int len = player->getNameLen();
    for(int i = 0; i < len; i++)
      cout << "‾";
    if(player != last)
      cout << "|";
  }
  cout << "‾\n";

  //                          0  |  0  
  cout << "                         ";
  if(need_resize)
    dynamicSpace(resize_factor);

  for(auto player: player_)
  {
    // len = length of name, center = middle position 
    int len = player->getNameLen();
    int center = (len % 2 == 0) ? len / 2 : len / 2 + 1;

    // print prespaces and player-point
    for(int prespace = 0; prespace < center - 1; prespace++)
      cout << " ";
    cout << player->getPoints();

    // print postspaces and seperator
    // offset = if len even, position is printed to the left of center
    int offset = (len % 2 == 0) ? 0 : 1;
    for(int postspace = 0; postspace < center - offset; ++postspace)
      cout << " ";
    if(player != last)
      cout << "|";
  }

  // 🃑  🃑  🃑  🃑 
  // 1   2  3   4 
  printBoard();

  // ‾‾‾PLAYER‾‾‾‾‾‾‾‾‾‾
  cout << "\n‾‾‾PLAYER‾‾‾‾‾‾‾‾‾‾‾";
  if(need_resize)
    dynamicOverline(resize_factor);
}

// helper function for printField()
void Game::dynamicOverline(int resize_factor) const
{
  for(int overline = 0; overline < resize_factor; overline++)
    cout << "‾";
}

// helper function for printField()
void Game::dynamicSpace(int resize_factor) const
{
  for(int space = 0; space < resize_factor; space++)
    cout << " ";
}

// helper function for printField()
void Game::printBoard() const
{
  cout << "\n ";
  for(auto &element: board_)
    cout << element->getPicture() << "   ";
  cout << "\n ";
  int size = board_.size();
  for(int position = 0; position < size; position++)
    cout << position + 1 << "   ";
  cout << "\n";
}

//------------------------------------------------------------------------------
int Game::getMaxPoints() const
{
  int max = player_.at(0)->getPoints();
  for(auto player: player_)
  {
    if(player->getPoints() > max)
      max = player->getPoints();
  }
  return max;
}

//------------------------------------------------------------------------------
void Game::addToPlayersStack(string board_card_position, int player_position)
{
  reverse(board_card_position.begin(),board_card_position.end());
  int len = board_card_position.length();
  for(int i = 0; i < len; i++)
  {
    int card_position = (board_card_position.at(i) - '0');
    Card* current = getCardFromBoard(card_position);
    player_.at(player_position - 1)->addToStack(current);
    board_.erase(board_.begin() + card_position - 1);
  }
}

//------------------------------------------------------------------------------
void Game::clearBoard(int last_player)
{
  string all_cards;
  for(int i = 1; i <= getNumCards(); i++)
    all_cards += std::to_string(i);
  addToPlayersStack(all_cards, last_player);
}

//------------------------------------------------------------------------------
void Game::calcPoints()
{
  int max_stack = 0, max_clubs = 0;
  Player* stack_points, *clubs_points;

  for(auto player: player_)
  {
    for(auto card: player->getStack())
    {
      if(card->getType() == CardType::CLUBS && card->getValue() == 2)
      {
        player->setMala(true);
        player->addPoints(1);
      }
      if(card->getType() == CardType::DIAMOND && card->getValue() == 10)
      {
        player->setVelika(true);
        player->addPoints(1);
      }
      if(card->getType() == CardType::CLUBS)
        player->addClub();
    }

    if(player->getClubs() > max_clubs)
    {
      max_clubs = player->getClubs();
      clubs_points = player;
    }

    if(static_cast<int>(player->getStack().size()) > max_stack)
    {
      max_stack = player->getStack().size();
      stack_points = player;
    }
  }

  for(auto player: player_)
  {
    if(player == clubs_points)
      player->addPoints(1);
    if(player == stack_points)
      player->addPoints(2);
    printResults(player);
  }

}

//------------------------------------------------------------------------------
void Game::printResults(Player* player) const
{
  cout <<                 player->getName();
  cout << ": mala: "   << player->getMala();
  cout << "| velika: " << player->getVelika();
  cout << "| clubs: "  << player->getClubs();
  cout << "| stack: "  << player->getStack().size();
  cout << "| points: " << player->getPoints() << endl;
}


void Game::clearGame()
{
  for(auto player: player_){
    player->getStack().clear();
    player->setMala(false);
    player->setVelika(false);
    player->setClubs(0);
  }
}

//------------------------------------------------------------------------------
Game::~Game()
{
}