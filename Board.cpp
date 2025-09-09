//
// Created by ... on 10.07.2022.
//

#include "Board.h"

Board::Board()
{
    //in der Schleife werden zunächst alle Adressen auf dem boardArray auf den NullPointer gesetzt
    for (int i=0; i<7; i++){
        for (int j=0; j<7; j++){
            boardArray2D[i][j]=nullptr;
        }
    }
    addPointsToBoard(); //Kommentar dazu in board.h
    makeNeighbourConnections(); //Kommentar dazu in board.h
}
void Board::addPointsToBoard()
{
    vector<pair<int,int>>coordinatesVector;
    //hier werden int Paare, welche die Koordinaten der Punkte im 2d boardArray sind gebildet
    //und an den Vektor mit den Koordinatenpaaren angehängt
    coordinatesVector.push_back(make_pair(0,0));
    coordinatesVector.push_back(make_pair(0,3));
    coordinatesVector.push_back(make_pair(0,6));
    coordinatesVector.push_back(make_pair(1,1));
    coordinatesVector.push_back(make_pair(1,3));
    coordinatesVector.push_back(make_pair(1,5));
    coordinatesVector.push_back(make_pair(2,2));
    coordinatesVector.push_back(make_pair(2,3));
    coordinatesVector.push_back(make_pair(2,4));
    coordinatesVector.push_back(make_pair(3,0));
    coordinatesVector.push_back(make_pair(3,1));
    coordinatesVector.push_back(make_pair(3,2));
    coordinatesVector.push_back(make_pair(3,4));
    coordinatesVector.push_back(make_pair(3,5));
    coordinatesVector.push_back(make_pair(3,6));
    coordinatesVector.push_back(make_pair(4,2));
    coordinatesVector.push_back(make_pair(4,3));
    coordinatesVector.push_back(make_pair(4,4));
    coordinatesVector.push_back(make_pair(5,1));
    coordinatesVector.push_back(make_pair(5,3));
    coordinatesVector.push_back(make_pair(5,5));
    coordinatesVector.push_back(make_pair(6,0));
    coordinatesVector.push_back(make_pair(6,3));
    coordinatesVector.push_back(make_pair(6,6));

    //anhand des lokal erzeugten Koordinatenvektors werden alle Punkte in der for-Schleife erstellt
    //das board an den Stellen des Koordinatenvektors bekommt den Pointer/Adresse
    //der erzeugten Punkte zugewiesen und ist somit an der Stelle ein nullptr mehr.
    //Anschließend wird die Adresse des Punktes auch an den Hilfsvektor PVec zugewiesen
    for (auto i : coordinatesVector)
    {
        Point* p= new Point(i.first,i.second);
        boardArray2D[i.first][i.second] = p;
        PVec.push_back(p);
    }
}
void Board::makeNeighbourConnections()
{
    //der Hilfsvektor PVec mit allen Punkten des Spielfelds wird durchgegangen
    //dabei werden horizontale und vertikale "Nachbarn" zum privaten Vektor-Attribut 'neighbouringPoints'
    //von der Klasse Point hinzugefügt, welcher bei allen Punkten noch leer ist
    for (auto & i : PVec)
    {
        addHorizontalNeighbours(i);
        addVerticalNeighbours(i);
    }

}
void Board::addHorizontalNeighbours(Point *p)
{
    int row_toCheck = p->getPoint_row();
    //Prüfung ob Reihe vom übergebenen Punkt p = 3 (mittlere Reihe mit 6 Schnittpunkten,
    //anstatt 3 Schnittpunkten wie bei den anderen Reihen)
    if (row_toCheck!=3){
        for (int j=p->getPoint_col()+1; j<7; j++){     //gehe die Spalten 'rechts' vom übergebenen durch
            if (boardArray2D[row_toCheck][j]==nullptr) //bei einem nullptr wird weiter gemacht
                continue;
            else{
                //sobald ein gültiger Punkt-Pointer gefunden wurde,
                //wird dieser dem Punkt hinzugefügt
                //der Vektor mit "Nachbar-Pointern" füllt sich
                p->addNeighbourPoint(boardArray2D[row_toCheck][j]);
                break;
                //die Schleife in dieser Richtung wird mit break abgebrochen,
                //da es nur einen Nachbarn in dieser Richtung gibt
            }
        }
        //hier passiert dasselbe wie oben, nur nach links statt rechts
        for (int j=p->getPoint_col()-1; j>=0; j--){
            if (boardArray2D[row_toCheck][j]==nullptr)
                continue;
            else{
                p->addNeighbourPoint(boardArray2D[row_toCheck][j]);
                break;
            }
        }
    }
    else {
        //hier ist die Reihe = 3,
        //daher wird zusätzlich die Spalte des übergebenen Punktes überprüft
        int col_toCheck=p->getPoint_col();
        /*anhand folgendes Bildes lässt sich der folgende Part etwas besser erklären
            0   1   2   3   4   5   6
          0 +-----------+-----------+ 0
            |           |           |
          1 |   +-------+-------+   | 1
            |   |       |       |   |
          2 |   |   +---+---+   |   | 2
            |   |   |       |   |   |
          3 +---+---+       +---+---+ 3
            |   |   |       |   |   |
          4 |   |   +---+---+   |   | 4
            |   |       |       |   |
          5 |   +-------+-------+   | 5
            |           |           |
          6 +-----------+-----------+ 6
            0   1   2   3   4   5   6*/

        //bei Reihe 3 und spalte 0 oder 4 wird (horizontal) nur das Rechte hinzugefügt
        if (col_toCheck==0 || col_toCheck==4)
            p->addNeighbourPoint(boardArray2D[row_toCheck][col_toCheck+1]);
            //bei Reihe 1 oder 5 werden links und rechts die Nachbarn hinzugefügt
        else if (col_toCheck==1 || col_toCheck==5){
            p->addNeighbourPoint(boardArray2D[row_toCheck][col_toCheck-1]);
            p->addNeighbourPoint(boardArray2D[row_toCheck][col_toCheck+1]);
        }
        else if (col_toCheck==2 || col_toCheck==6){ //hier nur der Nachbar links
            p->addNeighbourPoint(boardArray2D[row_toCheck][col_toCheck-1]);
        }
    }
}
void Board::addVerticalNeighbours(Point *p)
{
    //diese Methode funktioniert genauso wie die addHorizontalNeighbor-Methode
    //nur werden hier Vertikal die Nachbarn hinzugefügt
    int col_toCheck = p->getPoint_col();
    if (col_toCheck!=3){
        for (int i=p->getPoint_row()+1; i<7; i++){
            if (boardArray2D[i][col_toCheck]==nullptr)
                continue;
            else{
                p->addNeighbourPoint(boardArray2D[i][col_toCheck]);
                break;
            }
        }
        for (int i=p->getPoint_row()-1; i>=0; i--){
            if (boardArray2D[i][col_toCheck]==nullptr)
                continue;
            else{
                p->addNeighbourPoint(boardArray2D[i][col_toCheck]);
                break;
            }
        }
    }
    else{
        int row_toCheck=p->getPoint_row();
        if (row_toCheck==0 || row_toCheck==4)
            p->addNeighbourPoint(boardArray2D[row_toCheck+1][col_toCheck]);
        else if (row_toCheck==1 || row_toCheck==5){
            p->addNeighbourPoint(boardArray2D[row_toCheck+1][col_toCheck]);
            p->addNeighbourPoint(boardArray2D[row_toCheck-1][col_toCheck]);
        }
        else if (row_toCheck==2 || row_toCheck==6){
            p->addNeighbourPoint(boardArray2D[row_toCheck-1][col_toCheck]);
        }
    }
}
void Board::printBoard()
{
    cout<<"  A   B   C   D   E   F   G "<<endl;
    cout<<"1 "<<PVec[0]->getValue()<<"-----------"<<PVec[1]->getValue()<<"-----------"<<PVec[2]->getValue()<<" 1"<<endl;
    cout<<"  |           |           |"<<endl;
    cout<<"2 |   "<<PVec[3]->getValue()<<"-------"<<PVec[4]->getValue()<<"-------"<<PVec[5]->getValue()<<"   | 2"<<endl;
    cout<<"  |   |       |       |   |"<<endl;
    cout<<"3 |   |   "<<PVec[6]->getValue()<<"---"<<PVec[7]->getValue()<<"---"<<PVec[8]->getValue()<<"   |   | 3"<<endl;
    cout<<"  |   |   |       |   |   |"<<endl;
    cout<<"4 "<<PVec[9]->getValue()<<"---"<<PVec[10]->getValue()<<"---"<<PVec[11]->getValue()<<"       "<<PVec[12]->getValue()<<"---"<<PVec[13]->getValue()<<"---"<<PVec[14]->getValue()<<" 4"<<endl;
    cout<<"  |   |   |       |   |   |"<<endl;
    cout<<"5 |   |   "<<PVec[15]->getValue()<<"---"<<PVec[16]->getValue()<<"---"<<PVec[17]->getValue()<<"   |   | 5"<<endl;
    cout<<"  |   |       |       |   |"<<endl;
    cout<<"6 |   "<<PVec[18]->getValue()<<"-------"<<PVec[19]->getValue()<<"-------"<<PVec[20]->getValue()<<"   | 6"<<endl;
    cout<<"  |           |           |"<<endl;
    cout<<"7 "<<PVec[21]->getValue()<<"-----------"<<PVec[22]->getValue()<<"-----------"<<PVec[23]->getValue()<<" 7"<<endl;
    cout<<"  A   B   C   D   E   F   G"<<endl<<endl;

}
Point* Board::get_chosenPoint(int row, int col)
{
    return boardArray2D[row][col];
}

bool Board::allChipsInMill(char colour)
{
    bool allInMill=false;
    for (unsigned long long i=0;i<PVec.size();i++)
    {
        if (PVec[i]->getValue()==colour)
        {
            if(millCreated(PVec[i]))
                allInMill=true;
            else {
                allInMill=false;
                break;
            }
        }
    }
    return allInMill;
}
bool Board::millCreated(Point* placedChip)
{
    //wenn horizontal oder vertikal ein true geliefert wird, returned diese Funktion auch true
    return checkForHorizontalMill(placedChip) || checkForVerticalMill(placedChip);
}
bool Board::checkForHorizontalMill(Point *placedChip)
{
    bool mill = false;
    int row_toCheck = placedChip->getPoint_row();
    //ähnlich wie bei der Suche der Nachbarn wird geschaut, ob der platzierte Chip in Reihe 3 ist, oder nicht
    if (row_toCheck!=3){
        for (int j=0; j<7; j++){
            if (boardArray2D[row_toCheck][j]==nullptr)
                continue;
            else{
                if (boardArray2D[row_toCheck][j]->getValue()==placedChip->getValue()){
                    mill= true; //boolean mill wird auf true gesetzt, wenn der Farbe gleich ist
                    continue;   //Schleife soll weiter gehen
                }
                else{
                    mill=false; //boolean mill wird auf true gesetzt, wenn der Farbe gleich ist
                    break;      //Schleife wird unterbrochen, da keine Mühle mehr vorliegen kann
                }
            }
        }
    }
    else{
        //hier wieder der Spezialfall, wenn die Mitte betroffen ist
        //die andere Verzweigung lässt sich nicht mehr umsetzen, da 6 Punkte sonst überprüft werden
        int col_toCheck=placedChip->getPoint_col();

        if (col_toCheck==0 || col_toCheck==4){
            // die nächsten beiden Punkte rechts werden geprüft
            if (boardArray2D[row_toCheck][col_toCheck+1]->getValue()==placedChip->getValue() && boardArray2D[row_toCheck][col_toCheck+2]->getValue()==placedChip->getValue())
                mill= true;
        }

        else if (col_toCheck==1 || col_toCheck==5){
            //links und rechts die Punkte werden geprüft
            if (boardArray2D[row_toCheck][col_toCheck-1]->getValue()==placedChip->getValue() && boardArray2D[row_toCheck][col_toCheck+1]->getValue()==placedChip->getValue())
                mill= true;
        }
        else if (col_toCheck==2 || col_toCheck==6)
            // die nächsten beiden linken Punkte werden geprüft
            if (boardArray2D[row_toCheck][col_toCheck-1]->getValue()==placedChip->getValue() && boardArray2D[row_toCheck][col_toCheck-2]->getValue()==placedChip->getValue())
                mill= true;
    }

    return mill;
}
bool Board::checkForVerticalMill(Point *placedChip)
{
    //wieder analog zu checkForHorizontalMill
    bool mill = false;
    int col_toCheck = placedChip->getPoint_col();
    if (col_toCheck!=3){
        for (int i=0; i<7; i++){
            if (boardArray2D[i][col_toCheck]==nullptr)
                continue;
            else{
                if (boardArray2D[i][col_toCheck]->getValue()==placedChip->getValue()){
                    mill= true;
                    continue;
                }
                else{
                    mill=false;
                    break;
                }
            }
        }
    }
    else{
        int row_toCheck=placedChip->getPoint_row();

        if (row_toCheck==0 || row_toCheck==4){
            if (boardArray2D[row_toCheck+1][col_toCheck]->getValue()==placedChip->getValue() && boardArray2D[row_toCheck+2][col_toCheck]->getValue()==placedChip->getValue())
                mill= true;
        }

        else if (row_toCheck==1 || row_toCheck==5){
            if (boardArray2D[row_toCheck-1][col_toCheck]->getValue()==placedChip->getValue() && boardArray2D[row_toCheck+1][col_toCheck]->getValue()==placedChip->getValue())
                mill= true;
        }
        else if (row_toCheck==2 || row_toCheck==6)
            if (boardArray2D[row_toCheck-1][col_toCheck]->getValue()==placedChip->getValue() && boardArray2D[row_toCheck-2][col_toCheck]->getValue()==placedChip->getValue())
                mill= true;
    }

    return mill;
}

void Board::deletePoints()
{
    for (unsigned long long i=0; i<PVec.size();i++)
        delete PVec[i];

    PVec.clear();
}

