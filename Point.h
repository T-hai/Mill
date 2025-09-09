//
// Created by ... on 10.07.2022.
//

#ifndef MILL_POINT_H
#define MILL_POINT_H
#include<vector>

using namespace std;

class Point {
public:
    Point(int row, int col); //Konstruktor, welcher point_row und point_col mit den übergeben parametern setzt
    void addNeighbourPoint(Point* neighbourPoint); //fügt den übergebenen Punkt zum Vektor hinzu
    bool isNeighbour(Point*point); //schaut ob übergebener Punkt zu den Nachbarn dazugehört und liefert true/false
    void changeValue(char newValue); //änderung von value zu übergebenen value; also ein setter für value

    //getter für die privaten Attribute: value, point_row, point_col
    char getValue() const;
    int getPoint_row() const;
    int getPoint_col() const;

private:
    char value='+'; //Anzeigewert im Feld, zunächst noch '+', da der Punkt "leer" ist
    int point_row;
    int point_col;
    vector<Point*>neighbouringPoints; //Liste mit allen Pointern von den anliegenden Punkten
};


#endif //MILL_POINT_H
