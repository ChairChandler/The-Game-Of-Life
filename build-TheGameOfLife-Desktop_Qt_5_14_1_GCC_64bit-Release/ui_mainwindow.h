/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionStart;
    QAction *actionStop;
    QAction *actionRandomize;
    QAction *actionChange_amount_to_revive;
    QAction *actionChange_amount_to_survive;
    QAction *actionPause;
    QAction *actionChange_amount_of_points;
    QAction *actionChange_alive_cell_color;
    QAction *actionChange_dead_cell_color;
    QAction *actionChange_size;
    QAction *actionChange_grid_color;
    QAction *actionSave_XML_file;
    QAction *actionLoad_XML_file;
    QAction *actionPrint;
    QAction *actionChange_language;
    QAction *actionChange_radius;
    QAction *actionAuthor;
    QAction *actionTutorial;
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *activeLabelStep;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QVBoxLayout *verticalLayout;
    QSlider *speedSlider;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QMenuBar *menuBar;
    QMenu *menuTest;
    QMenu *menuSettings;
    QMenu *menuInformation;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(673, 551);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setFocusPolicy(Qt::NoFocus);
        MainWindow->setContextMenuPolicy(Qt::NoContextMenu);
        QIcon icon;
        icon.addFile(QString::fromUtf8("ico.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setWindowOpacity(29.000000000000000);
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        MainWindow->setToolButtonStyle(Qt::ToolButtonIconOnly);
        actionStart = new QAction(MainWindow);
        actionStart->setObjectName(QString::fromUtf8("actionStart"));
        actionStop = new QAction(MainWindow);
        actionStop->setObjectName(QString::fromUtf8("actionStop"));
        actionRandomize = new QAction(MainWindow);
        actionRandomize->setObjectName(QString::fromUtf8("actionRandomize"));
        actionChange_amount_to_revive = new QAction(MainWindow);
        actionChange_amount_to_revive->setObjectName(QString::fromUtf8("actionChange_amount_to_revive"));
        actionChange_amount_to_survive = new QAction(MainWindow);
        actionChange_amount_to_survive->setObjectName(QString::fromUtf8("actionChange_amount_to_survive"));
        actionPause = new QAction(MainWindow);
        actionPause->setObjectName(QString::fromUtf8("actionPause"));
        actionChange_amount_of_points = new QAction(MainWindow);
        actionChange_amount_of_points->setObjectName(QString::fromUtf8("actionChange_amount_of_points"));
        actionChange_alive_cell_color = new QAction(MainWindow);
        actionChange_alive_cell_color->setObjectName(QString::fromUtf8("actionChange_alive_cell_color"));
        actionChange_dead_cell_color = new QAction(MainWindow);
        actionChange_dead_cell_color->setObjectName(QString::fromUtf8("actionChange_dead_cell_color"));
        actionChange_size = new QAction(MainWindow);
        actionChange_size->setObjectName(QString::fromUtf8("actionChange_size"));
        actionChange_grid_color = new QAction(MainWindow);
        actionChange_grid_color->setObjectName(QString::fromUtf8("actionChange_grid_color"));
        actionSave_XML_file = new QAction(MainWindow);
        actionSave_XML_file->setObjectName(QString::fromUtf8("actionSave_XML_file"));
        actionLoad_XML_file = new QAction(MainWindow);
        actionLoad_XML_file->setObjectName(QString::fromUtf8("actionLoad_XML_file"));
        actionPrint = new QAction(MainWindow);
        actionPrint->setObjectName(QString::fromUtf8("actionPrint"));
        actionChange_language = new QAction(MainWindow);
        actionChange_language->setObjectName(QString::fromUtf8("actionChange_language"));
        actionChange_radius = new QAction(MainWindow);
        actionChange_radius->setObjectName(QString::fromUtf8("actionChange_radius"));
        actionAuthor = new QAction(MainWindow);
        actionAuthor->setObjectName(QString::fromUtf8("actionAuthor"));
        actionTutorial = new QAction(MainWindow);
        actionTutorial->setObjectName(QString::fromUtf8("actionTutorial"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        centralWidget->setContextMenuPolicy(Qt::NoContextMenu);
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(10, 50, 651, 471));
        sizePolicy1.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy1);
        graphicsView->setContextMenuPolicy(Qt::NoContextMenu);
        graphicsView->setAcceptDrops(false);
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::NoBrush);
        graphicsView->setBackgroundBrush(brush);
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(10, 10, 341, 31));
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label, 0, Qt::AlignTop);

        activeLabelStep = new QLabel(layoutWidget);
        activeLabelStep->setObjectName(QString::fromUtf8("activeLabelStep"));
        activeLabelStep->setText(QString::fromUtf8("0"));

        horizontalLayout_2->addWidget(activeLabelStep, 0, Qt::AlignLeft|Qt::AlignTop);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2, 0, Qt::AlignTop);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        speedSlider = new QSlider(layoutWidget1);
        speedSlider->setObjectName(QString::fromUtf8("speedSlider"));
        speedSlider->setOrientation(Qt::Horizontal);
        speedSlider->setInvertedAppearance(true);
        speedSlider->setInvertedControls(false);
        speedSlider->setTickPosition(QSlider::NoTicks);
        speedSlider->setTickInterval(0);

        verticalLayout->addWidget(speedSlider);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 0, 1, 1, 1, Qt::AlignHCenter);

        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 0, 2, 1, 1, Qt::AlignHCenter);

        label_6 = new QLabel(layoutWidget1);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 0, 3, 1, 1, Qt::AlignRight|Qt::AlignTop);


        verticalLayout->addLayout(gridLayout);


        horizontalLayout->addLayout(verticalLayout);

        splitter->addWidget(layoutWidget1);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 673, 20));
        menuTest = new QMenu(menuBar);
        menuTest->setObjectName(QString::fromUtf8("menuTest"));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        menuInformation = new QMenu(menuBar);
        menuInformation->setObjectName(QString::fromUtf8("menuInformation"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuTest->menuAction());
        menuBar->addAction(menuSettings->menuAction());
        menuBar->addAction(menuInformation->menuAction());
        menuTest->addAction(actionStart);
        menuTest->addAction(actionPause);
        menuTest->addAction(actionStop);
        menuTest->addAction(actionSave_XML_file);
        menuTest->addAction(actionLoad_XML_file);
        menuTest->addAction(actionPrint);
        menuSettings->addSeparator();
        menuSettings->addAction(actionRandomize);
        menuSettings->addSeparator();
        menuSettings->addAction(actionChange_amount_to_revive);
        menuSettings->addAction(actionChange_amount_to_survive);
        menuSettings->addAction(actionChange_amount_of_points);
        menuSettings->addSeparator();
        menuSettings->addAction(actionChange_alive_cell_color);
        menuSettings->addAction(actionChange_dead_cell_color);
        menuSettings->addAction(actionChange_grid_color);
        menuSettings->addSeparator();
        menuSettings->addAction(actionChange_size);
        menuSettings->addAction(actionChange_radius);
        menuSettings->addSeparator();
        menuSettings->addAction(actionChange_language);
        menuInformation->addAction(actionTutorial);
        menuInformation->addAction(actionAuthor);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "The game of life", nullptr));
        actionStart->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
#if QT_CONFIG(shortcut)
        actionStart->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+F1", nullptr));
#endif // QT_CONFIG(shortcut)
        actionStop->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
#if QT_CONFIG(shortcut)
        actionStop->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+F3", nullptr));
#endif // QT_CONFIG(shortcut)
        actionRandomize->setText(QCoreApplication::translate("MainWindow", "Randomize", nullptr));
        actionChange_amount_to_revive->setText(QCoreApplication::translate("MainWindow", "Change amount to revive", nullptr));
#if QT_CONFIG(tooltip)
        actionChange_amount_to_revive->setToolTip(QCoreApplication::translate("MainWindow", "Amount of neighbours to live.", nullptr));
#endif // QT_CONFIG(tooltip)
        actionChange_amount_to_survive->setText(QCoreApplication::translate("MainWindow", "Change amount to survive", nullptr));
#if QT_CONFIG(tooltip)
        actionChange_amount_to_survive->setToolTip(QCoreApplication::translate("MainWindow", "Amount of neighbours to die.", nullptr));
#endif // QT_CONFIG(tooltip)
        actionPause->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
#if QT_CONFIG(shortcut)
        actionPause->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+F2", nullptr));
#endif // QT_CONFIG(shortcut)
        actionChange_amount_of_points->setText(QCoreApplication::translate("MainWindow", "Change number of points", nullptr));
        actionChange_alive_cell_color->setText(QCoreApplication::translate("MainWindow", "Change alive cell color", nullptr));
        actionChange_dead_cell_color->setText(QCoreApplication::translate("MainWindow", "Change dead cell color", nullptr));
        actionChange_size->setText(QCoreApplication::translate("MainWindow", "Change size", nullptr));
        actionChange_grid_color->setText(QCoreApplication::translate("MainWindow", "Change grid color", nullptr));
        actionSave_XML_file->setText(QCoreApplication::translate("MainWindow", "Save XML file", nullptr));
        actionLoad_XML_file->setText(QCoreApplication::translate("MainWindow", "Load XML file", nullptr));
        actionPrint->setText(QCoreApplication::translate("MainWindow", "Print", nullptr));
        actionChange_language->setText(QCoreApplication::translate("MainWindow", "Change language", nullptr));
        actionChange_radius->setText(QCoreApplication::translate("MainWindow", "Change radius", nullptr));
        actionAuthor->setText(QCoreApplication::translate("MainWindow", "Author", nullptr));
        actionTutorial->setText(QCoreApplication::translate("MainWindow", "Tutorial", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Step:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Speed", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "x1", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "x2", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "x3", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "x4", nullptr));
        menuTest->setTitle(QCoreApplication::translate("MainWindow", "Game", nullptr));
        menuSettings->setTitle(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        menuInformation->setTitle(QCoreApplication::translate("MainWindow", "Information", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
