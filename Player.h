//
// Created by Thai on 10.07.2022.
//

#ifndef MILL_PLAYER_H
#define MILL_PLAYER_H
#include <iostream>
#include <string>
#include "Board.h"

using namespace std;

class Player {
public:
    Player(string name, char colour, Board* boardAddress);
    string getPlayerName() const; //getter-Funktion für Spielernamen
    Point* choosePointOnBoard(); //Wahl eines Punktes vom Spielfeld
    pair<int,int> playerInput_toInt(string input); //verarbeitet den string Input und returned int Paar für row und col
    void placeChip(); //Platzieren des Chips an der gewünschten Stelle
    void moveChip(); //Bewegung des Chips zu anliegenden Punkten oder beliebig wenn jumpEnabled=true
    void removeChipFromBoard(); //entfernt Chip an ausgewählten Punkt
    char getChipColour() const;
    void setJumpEnabled(bool value);
    short getRemainingChips();
    void decreaseChipsOnBoard(); //chipsOnBoard -1
    short getChipsOnBoard() const;
    void setOpponent(Player *value);

private:
    string playerName; //Name des Spielers
    char chipColour; //Farbe
    Player* opponent_Address= nullptr; //Pointer(Adresse) vom gegnerischen Spieler;
    //um dessen Farbe einzusehen und seine Chips auf dem Feld zu nehmen
    Board* board_Address; //Pointer von dem Spielfeld, für den Zugriff auf das Spielfeld
    short remainingChips=9; //Chips, welche in der Anfangsphase gelegt werden müssen
    short chipsOnBoard=0; //Anzahl eigener Chips auf dem Feld
    bool jumpEnabled=false; //Spieler darf 'springen' wenn er nur noch 3 Chips hat
};


#endif //MILL_PLAYER_H
