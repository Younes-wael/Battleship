#include "gameboard.h"
#include <array>
#include "random.h"
#include <iostream>
using namespace std;
/**
   * @brief GameBoard constructor
   *
   * This shall initialize the enemy board (attribute \ref m_enemyBoard) with
   * dot characters '.'. The player's ships can either be placed here also, or
   * later by calling \ref randomPlaceShips.
   *
   *
   */
gameBoard::gameBoard(){
    for(int r=0;r<10;r++){
        for(int c=0;c<10;c++){
            m_enemyBoard[r][c]='.';
        }

    }
}
array<array<char, 10>, 10> gameBoard::getEnemyBoard(){
    return m_enemyBoard;
}
/**
   * @brief Prints the player's board.
   *
   * This function prints the player's board to the console screen. You are
   * relatively free to be creative here, but make sure that all ships are
   * displayed properly.
   *
   * Some suggestions are:
   *
   *   - A location containing water is represented by printing '.'
   *   - A location containing an intact (e.g. undamaged) ship part is
   * represented by its ship number (e.g. the ships index in the array)
   *   - A location containing a damaged ship part of an **unsunken ship** is
   * represented by an 'X'
   *   - A location containing a part of a sunken ship is represented by an 'S'
   *
   * You can, as mentioned before, use other characters, but those four types of
   * locations should be distinguishable from another.
   */
void gameBoard::printBoard(){

    for (int row = 0; row < 10; ++row) {
        for (int col = 0; col < 10; ++col) {
            bool shipPart = false;
            for (int i=0;i<m_ships.size();i++) {
                if (m_ships[i].hasPartIn(row, col)) {
                    shipPart = true;
                    if (m_ships[i].isSunk()) {
                        cout << "S ";  // Part of a sunken ship
                    } else if (m_ships[i].getPartIn(row,col).isDamaged()) {
                        cout << "X ";  // Damaged part of an unsunken ship
                    } else {
                        cout << i<< " ";  // Intact ship part
                    }
                }
            }
            if (!shipPart) {
               cout << ". ";  // Water
            }
        }
       cout << endl;
    }
}

/**
   * @brief Prints the 'cheat sheet', containing markings where this player has
   * hit or missed.
   *
   * When trying to hit the other player's ships, it does not make sense to
   * shoot the same location more than once. In order to 'memorize' those
   * locations, the two-dimensional array is used. In there, the characters have
   * the following meanings:
   *
   *   - '.' represents a location which has not yet beens shot
   *   - 'X' represents a hit ship at that locations
   *   - 'O' represents a shot into open water
   *
   * As with \ref printBoard you are free to change the characters if you fancy
   * something else.
   */
void gameBoard::printEnemyBoard(){
    for(int r=0;r<10;r++){
        for(int c=0;c<10;c++){
            cout<<m_enemyBoard[r][c]<<" ";
        }
        cout<<endl;
    }
}

/**
   * @brief The enemy player's shot on our board
   * @param[in] row The row where we are being shot
   * @param[in] col The column where we are being shot
   * @return True if the shot hit any of our ships, false otherwise.
   *
   * This function is called when the enemy is trying to hit any of our ships.
   * Generally a shot is directed at a specific location denoted by `row` and
   * `col`.
   *
   * If there is a ship part at that location, that part shall be damaged by
   * that shot.
   *
   * \see Part::setDamaged
   * \see printBoard
   */
bool gameBoard::hit(int row, int col){
    for(size_t i=0;i<m_ships.size();i++)
        if (m_ships[i].hasPartIn(row,col)){
            m_ships[i].getPartIn(row,col).setDamaged();
            return true;}
    return false;
}

/**
   * @brief Mark locations on the enemy board where we already shot at
   * @param[in] row The row where we shot
   * @param[in] col The column where we shot
   * @param[in] wasHit True if the shot was a hit (e.g. we hit a ship)
   *
   * This function shall make a mark on the 'cheat sheet'. The mark shall be
   * different depending on if we hit something there.
   *
   * \see hit
   * \see printEnemyBoard
   */
void gameBoard::mark(int row, int col, bool wasHit){
    if(wasHit)m_enemyBoard[row][col]='X';
    else m_enemyBoard[row][col]='O';
}

// Checks if a ship can be placed at a specified location and direction
bool gameBoard::canPlaceShip(int row, int col, int shipLength, Direction direction) {
    for (int k = 0; k < shipLength; ++k) {
        int checkRow = row;
        int checkCol = col;

        if (direction == Direction::north) checkRow -= k;
        else if (direction == Direction::east) checkCol += k;
        else if (direction == Direction::south) checkRow += k;
        else if (direction == Direction::west) checkCol -= k;

        if (checkRow < 0 || checkRow > 9 || checkCol < 0 || checkCol > 9) {
            return false;  // Ship is out of bounds
        }

        for (auto existingShip : m_ships) {
            if (existingShip.hasPartIn(checkRow, checkCol)) {
               return false;  // Ship intersects with an existing ship
            }
        }
    }

    return true;  // Ship can be placed at the specified location
}

/**
   * @brief Randomly place ships.
   *
   * This function randomly places ships on the board, e.g. it populates the
   * \ref m_ships vector.
   *
   * The following ships shall be placed:
   *   - 1 'Dreadnought' with 5 parts
   *   - 2 'Cruisers' with 4 parts
   *   - 3 'Destroyers' with 3 parts
   *   - 4 'Submarines' with 2 parts
   *
   * The ships shall be placed so that:
   *   - No ships intersect each other
   *   - No ship has parts outside the playing area
   *   - When this is called for both players, the resulting placements shall be
   * different
   *
   *
   */
void gameBoard::randomPlaceShips() {
    for (int i = 0; i < m_ships.size(); ++i) {
        int shipLength = 5;
        if (i > 0) shipLength = 4;
        if (i > 2) shipLength = 3;
        if (i > 5) shipLength = 2;

        bool shipPlaced = false;
        while (!shipPlaced) {
            int random_row = getRandom(0, 9);
            int random_col = getRandom(0, 9);
            int random_direction = getRandom(0, 3);

            if (canPlaceShip(random_row, random_col, shipLength, static_cast<Direction>(random_direction))) {
                    ship newShip(random_row, random_col, shipLength, static_cast<Direction>(random_direction));
                    m_ships[i] = newShip;
                    shipPlaced = true;
            }
        }
    }
}


/**
   * @brief Test if all ships are sunk
   * @return True if all ships on this board are sunk
   *
   * This function is used to determine if the player hast lost the game. As a
   * reminder: The player has lost the game when she has no floating ship left.
   */
bool gameBoard::allShipsSunk(){
    int sunkedShips=0;
    for (auto& testedship : m_ships) {
        if(testedship.isSunk())sunkedShips++;
    }
    if(sunkedShips==10)return true;
    return false;
}
