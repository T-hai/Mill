//
// Created by ... on 10.07.2022.
//
#ifndef MILL_BOARD_H
#define MILL_BOARD_H
#include<iostream>
#include<vector>
#include"point.h"

using namespace std;

class Board {
public:
    Board(); //erzeugung des zwei dimensionalen board arrays
    void addPointsToBoard(); //fügt Punkte dem Board zu
    void makeNeighbourConnections(); //"verbindet" die Punkte
    void addHorizontalNeighbours(Point* p); //fügt horizontal die Nachbarn hinzu
    void addVerticalNeighbours(Point* p); // same, nur vertikal
    void printBoard(); //Ausgabe des Spielfeldes
    Point* get_chosenPoint(int row, int col); //liefert den Wert des 2 dimensionalen boardArrays and der übergebenen Reihe und Spalte
    bool allChipsInMill(char colour); //schaut, ob alle Chips der übergebenen Farbe in einer Mühle sind
    bool millCreated(Point* placedChip); //schaut, ob der übergebene Punkt in einer Mühle ist
    bool checkForHorizontalMill(Point* placedChip); //prüft die horizontale Reihe
    bool checkForVerticalMill(Point* placedChip); //same, nur vertikal
    void deletePoints(); //löschen aller Punkte + PVec.clear

private:
    Point* boardArray2D[7][7]={};  //Spielfeld, welches nullptr und Pointer von den Punkten enthält
    vector<Point*>PVec; //Hilfsvektor, welcher alle Punkt-Pointer enthält.
    //sehr hilfreich im Debugger(um zu schauen, ob die Nachbarn stimmen)
    //, da sonst das 2D boardArray aufgeklappt werden müsste
};


#endif //MILL_BOARD_H
