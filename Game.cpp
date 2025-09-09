//
// Created by ... on 10.07.2022.
//

#include "Game.h"

Game::Game()
{

}

void Game::menu()
{
    char input='x';
    while (input!='3') {
        cout<<"Menu"<<endl;
        cout<<"=================="<<endl;
        cout<<"1: Starte Spiel"<<endl;
        cout<<"2: Regeln"<<endl;
        cout<<"3: Beenden"<<endl;
        cout<<"=================="<<endl;
        cout<<"Eingabe: ";
        cin>>input;
        switch (input) {
            case '1': play();
                break;
            case '2': rules();
                break;
            case '3': cout<<"Beende das Spiel..."<<endl;
                return;
            default: cout<<"Ungültige Eingabe!"<<endl;
        }
    }
}

void Game::rules()
{
    cout<<"Mühle"<<endl;
    cout<<"Phase 1: Placing pieces\n"
        <<"The game begins with an empty board.\n"
        <<"The players determine who plays first, then take turns placing their men one per play on empty points.\n"
        <<"If a player is able to place three of their pieces on contiguous points in a straight line, vertically or horizontally, they have formed a mill\n"
        <<"and may remove one of their opponent's pieces from the board and the game, with the caveat that a piece in an opponent's mill can only be removed if no other pieces are available.\n"
        <<"After all men have been placed, phase two begins. "<<endl;

    cout<<"Phase 2: Moving pieces\n"
        <<"Players continue to alternate moves, this time moving a man to an adjacent point.\n"
        <<"A piece may not 'jump' another piece.\n"
        <<"Players continue to try to form mills and remove their opponent's pieces as in phase one.\n"
        <<"A player can 'break' a mill by moving one of his pieces out of an existing mill,\n"
        <<"then moving it back to form the same mill a second time (or any number of times),\n"
        <<"each time removing one of his opponent's men.\n"
        <<"The act of removing an opponent's man is sometimes called 'pounding' the opponent.\n"
        <<"When one player has been reduced to three men, phase three begins."<<endl;

    cout<<"Phase 3: 'Flying'\n"
        <<"When a player is reduced to three pieces,\n"
        <<"there is no longer a limitation on that player of moving to only adjacent points:\n"
        <<"The player's men may 'fly' (or 'hop' or 'jump') from any point to any vacant point."<<endl;
}

void Game::play()
{
    Board* newBoard = new Board();
    newBoard->printBoard();

    string name1, name2;
    cout<<"Namen der Spieler"<<endl;
    cout<<"Player 1: ";
    cin>>name1;

    cout<<"Player 2: ";
    cin>>name2;

    Player* player1= new Player(name1,'W',newBoard);
    Player* player2= new Player(name2,'B',newBoard);

    player1->setOpponent(player2); //beide Spieler erhalten die Pointer des jeweils anderen
    player2->setOpponent(player1); //damit man auf die Attribute (Farbe, anzahl chips auf Feld) des anderen Spielers zugreifen kann

    Player* currentPlayer = player1;
    Player* otherPlayer= player2;
    //Phase 1 des Spiels, wo beide Spiele ihre Chips auf das Brett legen
    //Schleife endet, wenn beide keine Chips "in der Hand" (=>remainingChips) zum Legen haben
    //oder das Spiel nicht mehr weitergespielt werden soll ->chooseToContinue()
    while (player1->getRemainingChips()>0 || player2->getRemainingChips()>0) {
        currentPlayer->placeChip();
        newBoard->printBoard();
        showPlayerStatus(player1,player2);
        swap(currentPlayer,otherPlayer); //swapping players
        if(!chooseToContinue()){
            continueGame=false;
            break;
        }
    }

    //Phase 2 und 3 des Spiels
    //es wird so lange gespielt, solange beide Spieler mind. 3 Chips auf dem Feld haben
    //und das Spiel weitergespielt werden soll ->chooseToContinue()
    while (currentPlayer->getChipsOnBoard()>2 && otherPlayer->getChipsOnBoard()>2&&continueGame){
        if (currentPlayer->getChipsOnBoard()==3)
            currentPlayer->setJumpEnabled(true);
        currentPlayer->moveChip();
        newBoard->printBoard();
        if (otherPlayer->getChipsOnBoard()==2)
            gameOver(currentPlayer,otherPlayer,newBoard);
        swap(currentPlayer,otherPlayer);

        continueGame=chooseToContinue();
    }
    gameOver(currentPlayer,otherPlayer,newBoard);
}

void Game::gameOver(Player *player1, Player *player2, Board *board)
{
    if (player1->getChipsOnBoard()==2)
        cout<<player2->getPlayerName()<<" gewinnt!!!"<<endl<<endl;
    else if (player2->getChipsOnBoard()==2)
        cout<<player1->getPlayerName()<<" gewinnt!!!"<<endl<<endl;
    else
        cout<<"Das Spiel ist vorbei. Es gibt keinen Gewinner! "<<endl<<endl;

    //löschen aller Objekte im
    board->deletePoints();
    delete board;
    delete player1;
    delete player2;
    menu();
}

bool Game::chooseToContinue()
{
    char choice='x';
    while (choice!='j' && choice!='n') {
        cout<<"Fortfahren? ('j' oder 'n')"<<endl;
        cin>>choice;
    }
    if (choice=='j')
        return true;
    else
        return false;
}

void Game::showPlayerStatus(Player *player1, Player *player2)
{
    int gesamt1= player1->getRemainingChips()+player1->getChipsOnBoard();
    int gesamt2= player2->getRemainingChips()+player2->getChipsOnBoard();

    cout<<"                  "<<player1->getPlayerName()<<"\t"<<player2->getPlayerName()<<endl;
    cout<<"Unplatzierte Chips:"<<player1->getRemainingChips()<<"\t"<<player2->getRemainingChips()<<endl;
    cout<<"  Chips auf Brett: "<<player1->getChipsOnBoard()<<"\t"<<player2->getChipsOnBoard()<<endl;
    cout<<"     Chips gesamt: "<<gesamt1<<"\t"<<gesamt2<<endl;

}

