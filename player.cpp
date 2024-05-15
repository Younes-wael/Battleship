#include "player.h"
#include <iostream>

using namespace std;


    /**
   * @brief Player constructor.
   * @param[in] playerName The player's name.
   *
   * The attribute \ref m_playerName shall be initialized with the
   * `playerName` parameter.
   *
   * The attributes \ref m_gamesWon and \ref m_gamesLost
   * shall be initialized with 0.
   */
  player::player(const string& playerName) : m_playerName(playerName), m_gamesWon(0),m_gamesLost(0) {
  }


    /**
   * @brief Get games won.
   * @return The number of games which were won by this player.
   */
    int  player::getGamesWon() const{
        return m_gamesWon;
    }

    /**
   * @brief Get games lost.
   * @return The number of games which were lost by this player.
   */
    int  player::getGamesLost() const{
        return m_gamesLost;
    }

    /**
   * @brief Get games played.
   * @return The total number of games this player has played.
   *
   * \see getGamesWon
   * \see getGamesLost
   */
    int  player::getGamesPlayed() const{
        return m_gamesWon+m_gamesLost;
    }

    /**
   * @brief Add another won game.
   *
   * This shall increase the number of won games by 1.
   */
    void  player::addGameWon(){
        m_gamesWon++;
    }

    /**
   * @brief Add another lost game.
   *
   * This shall increase  the number of lost games by 1
   */
    void  player::addGameLost(){
        m_gamesLost++;
    }

    /**
   * @brief Get the player's name
   * @return The player's name
   */
    string  player::getName(){
        return m_playerName;
    }

