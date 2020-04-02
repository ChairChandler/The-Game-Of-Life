#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QLabel>
#include <QColor>
#include <QTranslator>
#include "sizedialog.h"
#include "data2d.h"
#include "supervisedvar.h"
#include "map.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected slots:
    void nextRound();
    void speedChanged(int value);
    void onActionChangeNumberToSurvive();
    void onActionChangeNumberToRevive();
    void onActionChangeAmountOfPoints();
    void onActionRandomize();
    void onActionStart();
    void onActionPause();
    void onActionStop();
    void onActionChangeAliveCellColor();
    void onActionChangeDeadCellColor();
    void onActionChangeGridColor();
    void onActionChangeSize();
    void onActionChangeRadius();
    void onActionSaveXMLfile();
    void onActionLoadXMLfile();
    void onActionPrint();
    void onActionChangeLanguage();
    void onActionTutorial();
    void onActionAuthor();

private:
    QTranslator m_polishLanguage;
    Ui::MainWindow *ui;
    QGraphicsScene *m_scene;
    QLabel *m_activeLabelStep;
    QTimer *m_timer;

    int m_radius = 1;

    const int m_MinNextRoundsIntervalMs = 250, m_MaxNextRoundsIntervalMs = 1000;
    int m_nextRoundsIntervalMs = 1000;

    //size means amount of squares on the axis
    const size_t m_MinSize = 4, m_MaxSize = 100;
    size_t m_sizeX = 100, m_sizeY = 100;

    unsigned m_minAmountToRevive = 0, m_maxAmountToRevive = static_cast<unsigned>(m_sizeX*m_sizeY);
    unsigned m_amountToRevive = 3;

    unsigned m_minAmountToSurvive = 0, m_maxAmountToSurvive = static_cast<unsigned>(m_sizeX*m_sizeY);
    unsigned m_amountToSurvive = 3;

    size_t m_minPointsAmount = 1, m_maxPointsAmount = static_cast<unsigned>(m_sizeX*m_sizeY);
    size_t m_pointsAmount = 4;

    Map m_gameMap;
    Data2D<QGraphicsRectItem*> m_areas; //provide fast access to the squares on the map

    QColor m_aliveCellColor, m_deadCellColor, m_gridColor;

    void createGrid();
    void colorize();

    //supervised variable is used to actualize the value of the label its assigned to
    class RoundCounter: public SupervisedVar<int>
    {
    public:
        explicit RoundCounter(MainWindow *super);
        void set(const int &val);
    private:
        MainWindow *m_super;
    } m_step;
};

#endif // MAINWINDOW_H
