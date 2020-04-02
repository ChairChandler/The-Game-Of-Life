#ifndef MAP_H
#define MAP_H

#include <cstdlib>
#include "data2d.h"

class Map
{
public:
    using PointStatus = bool;
    static const PointStatus Dead = false;
    static const PointStatus Alive = true;

    explicit Map(const size_t &sizeX, const size_t &sizeY, const unsigned &numberToRevive, const unsigned &numberToSurvive, const int &radius = 1);
    explicit Map(const size_t &sizeX, const size_t &sizeY, const unsigned &numberToRevive, const unsigned &numberToSurvive, const size_t &pointsAmount, const int &radius = 1);
    PointStatus& operator()(size_t x, size_t y);


    void randomize();
    void randomize(const size_t &pointsAmount);

    //Continue game, next round
    void next();

    void setRadius(const int &radius);
    void setNumberToRevive(const size_t &numberToRevive);
    void setNumberToSurvive(const size_t &numberToSurvive);
    void resize(const size_t &sizeX, const size_t &sizeY);

    //Load the game map from the beginning time point
    void reset();
    size_t getNumberOfAlivePoints();

private:
    using PointsMap = Data2D<PointStatus>;

    int m_radius;
    quint32 m_sizeX, m_sizeY;
    size_t m_numberToRevive, m_numberToSurvive;
    PointsMap m_points;
    PointsMap m_originalPoints;
    size_t calculateAlivesNeighbours(const size_t &x, const size_t &y);
};

#endif // MAP_H
