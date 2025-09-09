//
// Created by Thai on 10.07.2022.
//

#ifndef MILL_GAME_H
#define MILL_GAME_H
#include "Player.h"


class Game {
public:
    Game();
    void menu(); //einfaches Benutzermenü mit 3 Optionen
    void rules(); //Anzeige der Regeln mit 'cout'
    void play(); //das eigentliche Spiel
    void gameOver(Player* player1, Player* player2,Board* board); //schaut wenn, das Spiel vorbei ist, wer gewonnen hat
    bool chooseToContinue(); //Entscheidung, ob Spiel fortgesetzt werden soll; kann bei Bedarf herausgenommen werden
    void showPlayerStatus(Player* player1, Player* player2); //Anzeige der Spielstände
private:
    bool continueGame=true;
};


#endif //MILL_GAME_H
