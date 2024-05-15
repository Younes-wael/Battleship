#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include "battleship.h"

int main()
{
    string name1, name2;
    cout<<"Enter player 1 name: ";
    cin>>name1;
    battleship newbattleship(name1,"KI");
    while(true){
        newbattleship.play();
    }
    return 0;
}
