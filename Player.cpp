//
// Created by ... on 10.07.2022.
//

#include "Player.h"

Player::Player(string name, char colour, Board *boardAddress)
{
    playerName=name;
    chipColour=colour;
    board_Address=boardAddress;
}

char Player::getChipColour() const
{
    return chipColour;
}

string Player::getPlayerName() const
{
    return playerName;
}

Point *Player::choosePointOnBoard()
{
    int row, col;
    bool validPoint=false;
    while (!validPoint) {
        cout<<"Aktueller Spieler: "<<playerName<<endl;
        string input;
        cout<<"Waehle einen Punkt: (z.B. A1)"<<endl;
        cin>>input;

        row = playerInput_toInt(input).first;
        col = playerInput_toInt(input).second;

        //hier soll geschaut werden, ob der Punkt außerhalb des Bretts liegt
        if (row<0 || row>6 || col<0 || col>6){
            cout<<"Punkt liegt außerhalb vom Feld";
            continue;
        }
        //wenn das Feld nicht ein NullPointer ist, ist der Punkt gültig
        if (board_Address->get_chosenPoint(row,col)!=nullptr)
            validPoint=true;
    }
    //adresse vom ausgesuchten Punkt wird returned
    return board_Address->get_chosenPoint(row,col);
}

pair<int, int> Player::playerInput_toInt(string input)
{
    int row = int(input[1]) - 49;
    int col = int(input[0]-65);
    return make_pair(row,col);

}

void Player::placeChip()
{
    bool chipPlaced=false;

    while (!chipPlaced) {
        Point* temp = choosePointOnBoard();
        if (temp->getValue()==chipColour || temp->getValue()==opponent_Address->getChipColour())
            cout<<"Punkt ist bereits belegt."<<endl;
        else {
            temp->changeValue(chipColour);
            remainingChips--;
            chipsOnBoard++;
            chipPlaced=true;

            if (board_Address->millCreated(temp))
                removeChipFromBoard();
        }
    }
}

void Player::moveChip()
{
    Point* start;
    Point* target;
    bool startValid=false;
    while (!startValid) {
        cout<<"Waehle einen Startpunkt (z.B A1):"<<endl;
        Point* tempStart=choosePointOnBoard();
        if (tempStart->getValue()==chipColour){  //schaut, ob der Spieler seine eigene Farbe ausgesucht hat
            startValid=true;
            start=tempStart;
        }
        else
            cout<<"Ungueltiger Startpunkt. Bitte versuche es noch einmal!"<<endl;
    }

    bool targetValid=false;
    while (!targetValid) {
        cout<<"Waehle Zielpunkt (z.B A1):"<<endl;
        Point* tempTarget=choosePointOnBoard();
        if (!jumpEnabled){ //wenn er noch nicht springen kann:
            if(tempTarget->isNeighbour(start) && tempTarget->getValue()=='+'){ //ist ziel 'Nachbar' und leer?
                targetValid=true;
                target=tempTarget;
            }
            else
                cout<<"Ungueltiger Zielpunkt. Bitte versuche es noch einmal!"<<endl;
        }
        else{
            if (tempTarget->getValue()=='+'){ //wenn der Spieler springen kann, wird nur geschaut ob das Zielfeld leer ist
                targetValid=true;
                target=tempTarget;
            }
            else{
                cout<<"Ungueltiger Zielpunkt. Bitte versuche es noch einmal!"<<endl;
            }
        }
    }
    target->changeValue(start->getValue()); //ziel bekommt den wert von start
    start->changeValue('+'); //start ist leer

    // wenn mit dem bewegten Chip eine Mühle erzeugt wird, kann ein gegnerischer Chip entfernt werden
    if (board_Address->millCreated(target))
        removeChipFromBoard();
}

void Player::removeChipFromBoard()
{
    board_Address->printBoard();
    cout<<playerName<<": Du kannst einen gegnerischen Chip vom Feld entfernen!"<<endl;
    bool chipRemoved=false;

    //solange kein Chip entfernt wurde, geht die Schleife weiter
    while (!chipRemoved) {
        Point* temp = choosePointOnBoard();

        if (temp->getValue()=='+')
            cout<<"Kein Chip ausgesucht"<<endl;
        else if (temp->getValue()==chipColour)
            cout<<"Der Chip ist in deiner Farbe!"<<endl;
            //ist der ausgesuchte Chip in einer Mühle und sind alle gegnerischen NICHT in einer Mühle
        else if (board_Address->millCreated(temp) && !board_Address->allChipsInMill(opponent_Address->getChipColour()))
            cout<<"Der Chip ist in einer Muehle und kann nicht entfernt werden"<<endl;
        else {
            temp->changeValue('+'); //Anzeige wird auf '+' gesetzt
            opponent_Address->decreaseChipsOnBoard(); //Anzahl gegnerischer Chips auf dem Feld -1
            chipRemoved=true; //Chip wurde entfernt, Condition um Schleife zu verlassen ist true
        }
    }
}

void Player::setJumpEnabled(bool value)
{
    jumpEnabled = value;
}

short Player::getRemainingChips()
{
    return remainingChips;
}

void Player::decreaseChipsOnBoard()
{
    chipsOnBoard--;
}

short Player::getChipsOnBoard() const
{
    return chipsOnBoard;
}

void Player::setOpponent(Player *value)
{
    opponent_Address = value;
}
