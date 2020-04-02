#include "map.h"
#include <QRandomGenerator>

Map::Map(const size_t &sizeX, const size_t &sizeY, const unsigned &numberToRevive, const unsigned &numberToSurvive, const int &radius):
    m_sizeX(static_cast<quint32>(sizeX)),
    m_sizeY(static_cast<quint32>(sizeY)),
    m_points(m_sizeX, m_sizeY),
    m_originalPoints(m_sizeX, m_sizeY)
{
    m_numberToSurvive = numberToSurvive;
    m_numberToRevive = numberToRevive;
    m_radius = radius;

    randomize();
}

Map::Map(const size_t &sizeX, const size_t &sizeY, const unsigned &numberToRevive, const unsigned &numberToSurvive, const size_t &pointsAmount, const int &radius):
    m_sizeX(static_cast<quint32>(sizeX)),
    m_sizeY(static_cast<quint32>(sizeY)),
    m_points(m_sizeX, m_sizeY),
    m_originalPoints(m_sizeX, m_sizeY)
{
    m_numberToSurvive = numberToSurvive;
    m_numberToRevive = numberToRevive;
    m_radius = radius;

    randomize(pointsAmount);
}

Map::PointStatus& Map::operator()(size_t x, size_t y)
{
    return m_points(x, y);
}

void Map::randomize()
{
    for(PointStatus &point: m_points)
        point = Dead;

    quint32 pointsAmount = QRandomGenerator::system()->bounded(0L, m_sizeX * m_sizeY);

    for(quint32 i=0; i<pointsAmount; i++)
    {
        while(true)
        {
            quint32 x, y;

            x = QRandomGenerator::system()->bounded(0L, m_sizeX);
            y = QRandomGenerator::system()->bounded(0L, m_sizeY);

            if(!m_points(x, y))
            {
                m_points(x, y) = true;
                break;
            }
        }
    }

    m_originalPoints = m_points;
}

void Map::randomize(const size_t &pointsAmount)
{
    for(PointStatus &point: m_points)
        point = Dead;

    for(size_t i=0; i<pointsAmount; i++)
    {
        while(true)
        {
            quint32 x, y;

            x = QRandomGenerator::system()->bounded(0L, m_sizeX);
            y = QRandomGenerator::system()->bounded(0L, m_sizeY);

            if(!m_points(x, y))
            {
                m_points(x, y) = true;
                break;
            }
        }
    }

    m_originalPoints = m_points;
}

void Map::next()
{
    PointsMap points = m_points;

    for(size_t i=0; i<m_sizeX; i++)
    {
        for(size_t j=0; j<m_sizeY; j++)
        {
           size_t amountAlives = calculateAlivesNeighbours(i, j);

           if(m_points(i, j) && amountAlives < m_numberToSurvive) //if point is alive and ...
               points(i, j) = false;
           else if(!m_points(i, j) && amountAlives >= m_numberToRevive) //if point is dead and ...
               points(i, j) = true;
        }
    }

    m_points = points;
}

void Map::setNumberToSurvive(const size_t &numberToSurvive)
{
    m_numberToSurvive = numberToSurvive;
}

void Map::setRadius(const int &radius)
{
    m_radius = radius;
}

void Map::setNumberToRevive(const size_t &numberToRevive)
{
    m_numberToRevive = numberToRevive;
}

void Map::resize(const size_t &sizeX, const size_t &sizeY)
{
    m_sizeX = static_cast<quint32>(sizeX);
    m_sizeY = static_cast<quint32>(sizeY);

    m_points.resize(sizeX, sizeY);
    m_originalPoints.resize(sizeX, sizeY);

    randomize();
}

size_t Map::calculateAlivesNeighbours(const size_t &x, const size_t &y)
{
    int sX = static_cast<int>(m_sizeX), sY = static_cast<int>(m_sizeY);

    //more than 0 and less than max size(max squares)
    auto inRange = [&sX, &sY](int x, int y) -> bool
        {return x>0 && y>0 && x < sX && y < sY;};


    int iX = static_cast<int>(x), iY = static_cast<int>(y);
    size_t amountAlives = 0;


    for(int i = iX-m_radius; i <= iX+m_radius; i++)
        for(int j = iY-m_radius; j <= iY+m_radius; j++)
        {
            size_t uI, uJ;

            uI = static_cast<size_t>(i);
            uJ = static_cast<size_t>(j);

            if(inRange(i, j) && m_points(uI, uJ) && !(i == iX && j == iY))
                amountAlives++;
        }


    return amountAlives;
}

size_t Map::getNumberOfAlivePoints()
{
    size_t sum = 0;
    for(size_t i=0; i<m_sizeX; i++)
        for(size_t j=0; j<m_sizeY; j++)
        {
            if(m_points(i, j))
                sum++;
        }

    return sum;
}

void Map::reset()
{
    m_points = m_originalPoints;
}
