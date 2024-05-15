#include "battleship.h"
#include <array>
#include <iostream>
#include "aicotroller.h"

/**
   * @brief Battleship constructor
   * @param[in] player1Name Name of the first player
   * @param[in] player2Name Name of the second player*/

battleship::battleship(const string& player1Name, const string& player2Name): m_players{player(player1Name), player(player2Name)}{

}

/**
   * @brief Play one game of Battleships!
   *
   * This functions shall do the following:
   *
   *   - Initialize both players game boards:
   *     - The ships shall be placed at randomized locations
   *     - The 'cheat sheets' shall be empty
   *     - This can easily be achieved by creating new \ref GameBoard objects
   * and storing them in \ref m_boards, overwriting the old boards which may be
   * there already
   *
   * Then, do the following in a loop:
   *   1. Determine the active Player either by random coin toss or first player
   * always gets to start
   *   2. Print both the game board and the 'cheat sheet' for the active player
   *   3. Ask the active player a location she wants to shoot at
   *   4. Call the \ref GameBoard::hit function for that location on the
   * **inactive** Player's board
   *   5. Inform the active player if she hit something and make the correct
   * mark on the cheat sheet
   *   6. Switch the players, e.g. active player becomes inactive and inactive
   * Player becomes active
   *   7. Repeat Steps 1 to 6 until one player has lost
   *   8. Exit the function
   *
   */
void battleship::play(){
    m_boards[0] = gameBoard();
    m_boards[1] = gameBoard();
    m_boards[0].randomPlaceShips();
    m_boards[1].randomPlaceShips();
    bool gameOver = false;
    bool player1Turn = true;
    while (!gameOver) {
        // Determine active and inactive players and their boards
        player& activePlayer = m_players[player1Turn ? 0 : 1];
        player& inactivePlayer = m_players[player1Turn ? 1 : 0];
        gameBoard& activeBoard = m_boards[player1Turn ? 0 : 1];
        gameBoard& inactiveBoard = m_boards[player1Turn ? 1 : 0];

        // Print game board and cheat sheet for the active player
        activeBoard.printBoard();
        cout<<endl<<"cheat sheet:"<<endl;
        activeBoard.printEnemyBoard();
        // Get input from the active player about the shot location
        int row, col;
        if(player1Turn){
        cout << "Where would you like to strike: ";
        cin >> row >> col;
        }
        else{
        row= aiController::shoot(activeBoard).x;
        col= aiController::shoot(activeBoard).y;
        cout<<"ai striked in: "<<row<<" "<<col<<endl;
        }

        // Call hit function on the inactive player's board
        bool hitResult = inactiveBoard.hit(row-1, col-1);

        // Mark the shot on the active player's cheat sheet

        activeBoard.mark(row-1, col-1, hitResult);

        // Inform the active player about the hit result
        if (hitResult) {
            cout << "You hit a ship!" << endl;
        } else {
            cout << "You missed!" << endl;
        }

        // Check if any player has lost
        if (inactiveBoard.allShipsSunk()) {
            gameOver = true;
            // Update game stats for the players
            activePlayer.addGameWon();
            inactivePlayer.addGameLost();

            // Display game result
            cout << "Game Over!" << endl;
            cout << "Player 1 Games Won: " << m_players[0].getGamesWon() << endl;
            cout << "KI Games Won: " << m_players[1].getGamesWon() << endl;
            cout << "Player 1 Games lost: " << m_players[0].getGamesLost() << endl;
            cout << "KI Games lost: " << m_players[1].getGamesLost() << endl;
            cout<<"Games played: "<<m_players[0].getGamesPlayed()<<endl;
        }

        // Switch players
        player1Turn = !player1Turn;
    }

}

