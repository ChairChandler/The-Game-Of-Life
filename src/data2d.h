#ifndef DATA2D_H
#define DATA2D_H

#include <QVector>

//Class of 2 dimensional vector of data
template<class T>
class Data2D: private QVector<T>
{
private:
    int m_sizeX, m_sizeY;
public:
    explicit Data2D(size_t sizeX, size_t sizeY): m_sizeX(sizeX), m_sizeY(sizeY), QVector<T> (sizeX*sizeY) {}
    void resize(const size_t &sizeX, const size_t &sizeY)
    {
        m_sizeX = sizeX;
        m_sizeY = sizeY;
        QVector<T>::resize(sizeX * sizeY);
    }

    T& operator()(const size_t &x, const size_t &y)
    {
        int offset = static_cast<int>( x*m_sizeY + y);
        return this->operator[](offset);
    }

    using QVector<T>::begin;
    using QVector<T>::end;
};

#endif // DATA2D_H
