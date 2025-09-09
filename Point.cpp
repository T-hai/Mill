//
// Created by ... on 10.07.2022.
//

#include "Point.h"

Point::Point(int row, int col)
{
    point_row=row;
    point_col=col;
    neighbouringPoints.clear();
}

void Point::addNeighbourPoint(Point *neighbourPoint)
{
    neighbouringPoints.push_back(neighbourPoint);
}

bool Point::isNeighbour(Point *point)
{
    bool is_a_Neighbour=false;
    //hier wird geschaut, ob der übergebene Punkt in dem Vektor mit den aufgelisteten Nachbarn vorhanden ist
    for (unsigned long long i=0;i<neighbouringPoints.size();i++)
    {
        if (neighbouringPoints[i]==point)
            is_a_Neighbour=true; //wenn ja, wird der als false gesetzte boolean zu true
    }
    return is_a_Neighbour;
}

void Point::changeValue(char newValue)
{
    value=newValue;
}

char Point::getValue() const
{
    return value;
}

int Point::getPoint_row() const
{
    return point_row;
}

int Point::getPoint_col() const
{
    return point_col;
}


