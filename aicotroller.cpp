#include "aicotroller.h"

aiController::aiController()
{

}

coordinate aiController::shoot(gameBoard& board){
    bool notHit=false;
    coordinate shootingCoordinate{1,1};
    while(notHit==false){
        shootingCoordinate.x=getRandom(1,10);
        shootingCoordinate.y=getRandom(1,10);
        if(board.getEnemyBoard()[shootingCoordinate.x][shootingCoordinate.y]=='.')
            notHit=true;

    }
      return shootingCoordinate;
}
