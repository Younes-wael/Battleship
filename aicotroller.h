#ifndef AICOTROLLER_H
#define AICOTROLLER_H
#include "gameboard.h"
#include "random.h"


struct coordinate{
    int x;
    int y;
};
class aiController
{

public:
    aiController();
    static coordinate shoot(gameBoard& board);
};

#endif // AICOTROLLER_H
