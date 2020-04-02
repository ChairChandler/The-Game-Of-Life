#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>
#include <QTimer>
#include <QColorDialog>
#include <QFormLayout>
#include <QSpinBox>
#include <QInputDialog>
#include <QXmlStreamWriter>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QStack>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QTranslator>
#include <QDesktopServices>
#include "qtimerlock.h"

#define TO_STR(x) #x

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_gameMap(m_sizeX, m_sizeY, m_amountToRevive, m_amountToSurvive, m_pointsAmount),
    m_areas(m_sizeX, m_sizeY),
    m_aliveCellColor(QColor(Qt::black)),
    m_deadCellColor(QColor(Qt::white)),
    m_gridColor(QColor(Qt::red)),
    m_step(this)
{
    ui->setupUi(this);
    using Qt::WindowType;

    setWindowFlags(WindowType::Window|WindowType::MSWindowsFixedSizeDialogHint);

    m_scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(m_scene);
    ui->graphicsView->setAlignment(Qt::AlignLeft|Qt::AlignTop);

    m_scene->setBackgroundBrush(QBrush(Qt::white));


    m_activeLabelStep = this->findChild<QLabel*>("activeLabelStep");
    m_activeLabelStep->setNum(m_step.get());


    ui->speedSlider->setRange(m_MinNextRoundsIntervalMs, m_MaxNextRoundsIntervalMs);
    ui->speedSlider->setTickInterval(250);
    ui->speedSlider->setSingleStep(250);
    ui->speedSlider->setTickPosition(QSlider::TickPosition::TicksBelow);
    ui->speedSlider->setValue(m_nextRoundsIntervalMs);

    m_timer = new QTimer(this);
    m_timer->setInterval(m_nextRoundsIntervalMs);

    QObject::connect(ui->speedSlider,
                     &QSlider::valueChanged,
                     this,
                     &MainWindow::speedChanged);

    QObject::connect(m_timer,
                     &QTimer::timeout,
                     this,
                     &MainWindow::nextRound);

    QObject::connect(ui->actionStart,
                     &QAction::triggered,
                     this,
                     &MainWindow::onActionStart);

    QObject::connect(ui->actionPause,
                     &QAction::triggered,
                     this,
                     &MainWindow::onActionPause);

    QObject::connect(ui->actionStop,
                     &QAction::triggered,
                     this,
                     &MainWindow::onActionStop);

    QObject::connect(ui->actionRandomize,
                     &QAction::triggered,
                     this,
                     &MainWindow::onActionRandomize);

    QObject::connect(ui->actionChange_amount_to_survive,
                     &QAction::triggered,
                     this,
                     &MainWindow::onActionChangeNumberToSurvive);

    QObject::connect(ui->actionChange_amount_to_revive,
                     &QAction::triggered,
                     this,
                     &MainWindow::onActionChangeNumberToRevive);

    QObject::connect(ui->actionChange_amount_of_points,
                     &QAction::triggered,
                     this,
                     &MainWindow::onActionChangeAmountOfPoints);

    QObject::connect(ui->actionChange_alive_cell_color,
                     &QAction::triggered,
                     this,
                     &MainWindow::onActionChangeAliveCellColor);

    QObject::connect(ui->actionChange_dead_cell_color,
                     &QAction::triggered,
                     this,
                     &MainWindow::onActionChangeDeadCellColor);

    QObject::connect(ui->actionChange_grid_color,
                     &QAction::triggered,
                     this,
                     &MainWindow::onActionChangeGridColor);

    QObject::connect(ui->actionChange_size,
                     &QAction::triggered,
                     this,
                     &MainWindow::onActionChangeSize);

    QObject::connect(ui->actionChange_radius,
                     &QAction::triggered,
                     this,
                     &MainWindow::onActionChangeRadius);

    QObject::connect(ui->actionSave_XML_file,
                     &QAction::triggered,
                     this,
                     &MainWindow::onActionSaveXMLfile);

    QObject::connect(ui->actionLoad_XML_file,
                     &QAction::triggered,
                     this,
                     &MainWindow::onActionLoadXMLfile);

    QObject::connect(ui->actionPrint,
                     &QAction::triggered,
                     this,
                     &MainWindow::onActionPrint);

    QObject::connect(ui->actionChange_language,
                     &QAction::triggered,
                     this,
                     &MainWindow::onActionChangeLanguage);

    QObject::connect(ui->actionTutorial,
                     &QAction::triggered,
                     this,
                     &MainWindow::onActionTutorial);

    QObject::connect(ui->actionAuthor,
                     &QAction::triggered,
                     this,
                     &MainWindow::onActionAuthor);

    createGrid();
    colorize();
    this->setFixedSize(this->size());
}

void MainWindow::createGrid()
{
    int windowWidthUnitToResize = 0, windowHeightUnitToResize = 0;
    qreal val, width, height;
    size_t widthUnit, heightUnit;

    width = static_cast<qreal>(ui->graphicsView->width());
    height = static_cast<qreal>(ui->graphicsView->height());

    do
    {
        val = width / m_sizeX;
        widthUnit = static_cast<size_t>(qFloor(val));

        if(qAbs(width - widthUnit * m_sizeX) > 0.5)
        {
            if((width - widthUnit * m_sizeX) > 0) //not enough pixels of rectangle
            {
                width--;
                windowWidthUnitToResize--;
            }
            else if((width - widthUnit * m_sizeX) < 0) //too much pixels of rectangle
            {
                width++;
                windowWidthUnitToResize++;
            }
        }

    }while(qAbs(width - widthUnit * m_sizeX) > 0.5); //while we can see not matching rectangle

    do
    {
        val = height / m_sizeY;
        heightUnit = static_cast<size_t>(qFloor(val));

        if(qAbs(height - heightUnit * m_sizeY) > 0.5)
        {
            if((height - heightUnit * m_sizeY) > 0) //not enough pixels of rectangle
            {
                height--;
                windowHeightUnitToResize--;
            }
            else if((height - heightUnit * m_sizeY) < 0) //too much pixels of rectangle
            {
                height++;
                windowHeightUnitToResize++;
            }
        }

    }while(qAbs(height - heightUnit * m_sizeY) > 0.5); //while we can see not matching rectangle

    //resize graphicsView and mainWindow to the new sizes
    ui->graphicsView->resize(static_cast<int>(width), static_cast<int>(height));
    this->resize(this->width() + windowWidthUnitToResize, this->height() + windowHeightUnitToResize);

    //create rectangles
    for(size_t i=0; i<m_sizeX; i++)
    {
        for(size_t j=0; j<m_sizeY; j++)
        {
            m_areas(i, j) = m_scene->addRect(widthUnit*i, heightUnit*j, widthUnit, heightUnit, QPen(m_gridColor), QBrush(m_deadCellColor));
        }
     }
}

void MainWindow::nextRound()
{
     m_gameMap.next();
     colorize();
     m_step.set(m_step.get()+1);
}

void MainWindow::speedChanged(int value)
{
    QTimerLock lk(m_timer);
    m_nextRoundsIntervalMs = value;
    m_timer->setInterval(m_nextRoundsIntervalMs);
}

void MainWindow::colorize()
{
    for(size_t i=0; i<m_sizeX; i++)
    {
        for(size_t j=0; j<m_sizeY; j++)
        {
            if(m_gameMap(i, j) == m_gameMap.Alive)
            {
                m_areas(i, j)->setPen(QPen(m_gridColor));
                m_areas(i, j)->setBrush(QBrush(m_aliveCellColor));
            } else {
                m_areas(i, j)->setPen(QPen(m_gridColor));
                m_areas(i, j)->setBrush(QBrush(m_deadCellColor));
            }
        }
     }
}

void MainWindow::onActionStart()
{
    if(!m_timer->isActive())
        m_timer->start();
}

void MainWindow::onActionPause()
{
    if(m_timer->isActive())
        m_timer->stop();
}

void MainWindow::onActionStop()
{
    if(m_timer->isActive())
        m_timer->stop();

    m_gameMap.reset();
    colorize();
    m_step.set(0);
}

void MainWindow::onActionChangeNumberToSurvive()
{
    QTimerLock lk(m_timer);

    bool ok;
    int val;

    val = QInputDialog::getInt(this, tr("Amount to survive"), tr("Input value"),
                               static_cast<int>(m_amountToSurvive),
                               static_cast<int>(m_minAmountToSurvive),
                               static_cast<int>(m_maxAmountToSurvive), 1, &ok);
    if(ok)
    {
        m_amountToSurvive = static_cast<unsigned>(val);
        m_gameMap.setNumberToSurvive(m_amountToSurvive);
    }
}

void MainWindow::onActionRandomize()
{
    if(m_timer->isActive())
        m_timer->stop();

    m_gameMap.randomize(m_pointsAmount);
    colorize();
    m_step.set(0);
}

void MainWindow::onActionChangeNumberToRevive()
{
    QTimerLock lk(m_timer);

    bool ok;
    int val;

    val = QInputDialog::getInt(this, tr("Amount to revive"), tr("Input value"),
                               static_cast<int>(m_amountToRevive),
                               static_cast<int>(m_minAmountToRevive),
                               static_cast<int>(m_maxAmountToRevive), 1, &ok);
    if(ok)
    {
        m_amountToRevive = static_cast<unsigned>(val);
        m_gameMap.setNumberToRevive(m_amountToRevive);
    }
}

void MainWindow::onActionChangeAmountOfPoints()
{
    QTimerLock lk(m_timer);

    bool ok;
    int val;

    val = QInputDialog::getInt(this, tr("Amount of points"), tr("Input value"),
                               static_cast<int>(m_pointsAmount),
                               static_cast<int>(m_minPointsAmount),
                               static_cast<int>(m_maxPointsAmount), 1, &ok);
    if(ok)
    {
        m_pointsAmount = static_cast<unsigned>(val);
        m_gameMap.randomize(m_pointsAmount);
        colorize();
    }
}

void MainWindow::onActionChangeAliveCellColor()
{
    QTimerLock lk(m_timer);

    QColor color = QColorDialog::getColor();

    if(color.isValid())
    {
        m_aliveCellColor = color;
        colorize();
    }
}

void MainWindow::onActionChangeDeadCellColor()
{
    QTimerLock lk(m_timer);

    QColor color = QColorDialog::getColor();

    if(color.isValid())
    {
        m_deadCellColor = color;
        colorize();
    }
}

void MainWindow::onActionChangeGridColor()
{
    QTimerLock lk(m_timer);

    QColor color = QColorDialog::getColor();

    if(color.isValid())
    {
        m_gridColor = color;
        createGrid();
        colorize();
    }
}

void MainWindow::onActionChangeSize()
{
    QTimerLock lk(m_timer);

    auto [sizes, success] = SizeDialog::getSizes(this, m_MinSize, m_MaxSize);

    if(success)
    {
        lk.disable();

        m_sizeX = sizes.first;
        m_sizeY = sizes.second;

        unsigned product = static_cast<unsigned>(m_sizeX*m_sizeY);

        m_maxAmountToRevive = product;
        m_maxAmountToSurvive = product;
        m_maxPointsAmount = product;

        m_gameMap.resize(m_sizeX, m_sizeY);
        m_areas.resize(m_sizeX, m_sizeY);

        m_gameMap.randomize();
        createGrid();
        colorize();

        m_pointsAmount = m_gameMap.getNumberOfAlivePoints();
    }
}

void MainWindow::onActionChangeRadius()
{
    QTimerLock lk(m_timer);

    bool ok;
    int val;

    val = QInputDialog::getInt(this, tr("Radius"), tr("Input value"),
                               static_cast<int>(m_radius),
                               static_cast<int>(1),
                               static_cast<int>(qMax(m_sizeX, m_sizeY)), 1, &ok);
    if(ok)
    {
        m_radius = val;
        m_gameMap.setRadius(m_radius);
    }
}

void MainWindow::onActionSaveXMLfile()
{
    QTimerLock lk(m_timer);

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save XML file"), tr("untitled.xml"), QString("%1 %2").arg(tr("XML file")).arg("(*.xml)"));

    QFile file(fileName);
    using Flags = QFile::OpenModeFlag;

    file.open(Flags::WriteOnly);
    if(!file.isOpen())
    {
        if(!fileName.isEmpty())
        {
            QMessageBox error;
            error.critical(this, tr("Error"), QString("%1: %2").arg(tr("Cannot save XML file")).arg(fileName));
            error.setFixedSize(500, 200);
        }

        return;
    }

    QXmlStreamWriter writer(&file);

    auto writeColor = [&writer](QColor &color)
    {
        int r, g, b;
        color.getRgb(&r, &g, &b);

        writer.writeStartElement(TO_STR(r));
        writer.writeCharacters(QString::number(r));
        writer.writeEndElement();

        writer.writeStartElement(TO_STR(g));
        writer.writeCharacters(QString::number(g));
        writer.writeEndElement();

        writer.writeStartElement(TO_STR(b));
        writer.writeCharacters(QString::number(b));
        writer.writeEndElement();
    };

        writer.writeStartDocument();
        writer.writeStartElement("document");
            writer.writeStartElement(TO_STR(m_nextRoundsIntervalMs));
            writer.writeCharacters(QString::number(m_nextRoundsIntervalMs));
            writer.writeEndElement();


            writer.writeStartElement("sizes");
                writer.writeStartElement(TO_STR(m_sizeX));
                writer.writeCharacters(QString::number(m_sizeX));
                writer.writeEndElement();


                writer.writeStartElement(TO_STR(m_sizeY));
                writer.writeCharacters(QString::number(m_sizeY));
                writer.writeEndElement();
            writer.writeEndElement();

            writer.writeStartElement(TO_STR(m_radius));
            writer.writeCharacters(QString::number(m_radius));
            writer.writeEndElement();


            writer.writeStartElement("amountToRevive");
                writer.writeStartElement(TO_STR(m_minAmountToRevive));
                writer.writeCharacters(QString::number(m_minAmountToRevive));
                writer.writeEndElement();


                writer.writeStartElement(TO_STR(m_maxAmountToRevive));
                writer.writeCharacters(QString::number(m_maxAmountToRevive));
                writer.writeEndElement();


                writer.writeStartElement(TO_STR(m_amountToRevive));
                writer.writeCharacters(QString::number(m_amountToRevive));
                writer.writeEndElement();
            writer.writeEndElement();


            writer.writeStartElement("amountToSurvive");
                writer.writeStartElement(TO_STR(m_minAmountToSurvive));
                writer.writeCharacters(QString::number(m_minAmountToSurvive));
                writer.writeEndElement();


                writer.writeStartElement(TO_STR(m_maxAmountToSurvive));
                writer.writeCharacters(QString::number(m_maxAmountToSurvive));
                writer.writeEndElement();


                writer.writeStartElement(TO_STR(m_amountToSurvive));
                writer.writeCharacters(QString::number(m_amountToSurvive));
                writer.writeEndElement();
            writer.writeEndElement();


            writer.writeStartElement("pointsAmount");
                writer.writeStartElement(TO_STR(m_minPointsAmount));
                writer.writeCharacters(QString::number(m_minPointsAmount));
                writer.writeEndElement();


                writer.writeStartElement(TO_STR(m_maxPointsAmount));
                writer.writeCharacters(QString::number(m_maxPointsAmount));
                writer.writeEndElement();


                writer.writeStartElement(TO_STR(m_pointsAmount));
                writer.writeCharacters(QString::number(m_pointsAmount));
                writer.writeEndElement();
            writer.writeEndElement();


            writer.writeStartElement(TO_STR(m_step));
            writer.writeCharacters(QString::number(m_step.get()));
            writer.writeEndElement();

            writer.writeStartElement("colors");
                writer.writeStartElement(TO_STR(m_aliveCellColor));
                    writeColor(m_aliveCellColor);
                writer.writeEndElement();


                writer.writeStartElement(TO_STR(m_deadCellColor));
                    writeColor(m_deadCellColor);
                writer.writeEndElement();


                writer.writeStartElement(TO_STR(m_gridColor));
                    writeColor(m_gridColor);
                writer.writeEndElement();
            writer.writeEndElement();


            writer.writeStartElement(TO_STR(m_gameMap));

            for(size_t x=0; x<m_sizeX; x++)
            {
                for(size_t y=0; y<m_sizeY; y++)
                {

                    writer.writeStartElement("point");
                    writer.writeAttribute("x", QString::number(x));
                    writer.writeAttribute("y", QString::number(y));
                    writer.writeCharacters(m_gameMap(x, y) == m_gameMap.Alive? "Alive" : "Dead");
                    writer.writeEndElement();
                }
            }

            writer.writeEndElement();
        writer.writeEndElement();
        writer.writeEndDocument();

    file.close();
}

void MainWindow::onActionLoadXMLfile()
{
    QTimerLock lk(m_timer);

    QString fileName = QFileDialog::getOpenFileName(this, tr("Load XML file"), QString(), QString("%1 %2").arg(tr("XML file")).arg("(*.xml)"));

    QFile file(fileName);
    using Flags = QFile::OpenModeFlag;

    file.open(Flags::ReadOnly);
    if(!file.isOpen())
    {
        if(!fileName.isEmpty())
        {
            QMessageBox error;
            error.critical(this, tr("Error"), QString("%1: %2").arg(tr("Cannot load XML file")).arg(fileName));
            error.setFixedSize(500, 200);
        }

        return;
    }

    QXmlStreamReader reader(&file);

    using TokenType = QXmlStreamReader::TokenType;
    using Element = QPair<QStringRef, QXmlStreamAttributes>;
    QStack<Element> elements;
    QStringRef characters;
    int r, g, b;
    r = g = b = 0;

    while(!reader.atEnd() && !reader.hasError())
    {
        TokenType token = reader.readNext();
        switch(token)
        {
            case TokenType::StartElement:
                elements.push(Element(reader.name(), reader.attributes()));
            break;

            case TokenType::Characters:
            {
                characters = reader.text();

                Element &e = elements.last();
                QStringRef name = e.first;

                if(name == TO_STR(m_nextRoundsIntervalMs))
                    m_nextRoundsIntervalMs = characters.toInt();
                else if(name == TO_STR(m_radius))
                {
                    m_radius = characters.toInt();
                    m_gameMap.setRadius(m_radius);
                }
                else if(name == TO_STR(m_sizeX))
                    m_sizeX = characters.toUInt();
                else if(name == TO_STR(m_sizeY))
                {
                    m_sizeY = characters.toUInt();
                    m_gameMap.resize(m_sizeX, m_sizeY);
                }
                else if(name == TO_STR(m_minAmountToRevive))
                    m_minAmountToRevive = characters.toUInt();
                else if(name == TO_STR(m_maxAmountToRevive))
                    m_maxAmountToRevive = characters.toUInt();
                else if(name == TO_STR(m_amountToRevive))
                    m_amountToRevive = characters.toUInt();
                else if(name == TO_STR(m_minAmountToSurvive))
                    m_minAmountToSurvive = characters.toUInt();
                else if(name == TO_STR(m_maxAmountToSurvive))
                    m_maxAmountToSurvive = characters.toUInt();
                else if(name == TO_STR(m_amountToSurvive))
                    m_amountToSurvive = characters.toUInt();
                else if(name == TO_STR(m_minPointsAmount))
                    m_minPointsAmount = characters.toUInt();
                else if(name == TO_STR(m_maxPointsAmount))
                    m_maxPointsAmount = characters.toUInt();
                else if(name == TO_STR(m_pointsAmount))
                    m_pointsAmount = characters.toUInt();
                else if(name == TO_STR(m_step))
                    m_step.set(characters.toInt());
                else if(name == TO_STR(r))
                    r = characters.toInt();
                else if(name == TO_STR(g))
                    g = characters.toInt();
                else if(name == TO_STR(b))
                    b = characters.toInt();
                else if(name == "point")
                {
                    size_t x, y;
                    x = y = 0;

                    QXmlStreamAttributes attrs = e.second;
                    foreach(auto attribute, attrs)
                    {
                        if(attribute.name() == TO_STR(x))
                            x = attribute.value().toUInt();
                        else if(attribute.name() == TO_STR(y))
                            y = attribute.value().toUInt();
                    }

                    m_gameMap(x, y) = (characters == "Alive" ? m_gameMap.Alive : m_gameMap.Dead);
                }

            }
            break;

            case TokenType::EndElement:
            {
                Element e = elements.pop();
                QStringRef name = e.first;
                QColor newColor(r, g, b);

                if(name == TO_STR(m_aliveCellColor))
                    m_aliveCellColor = newColor;
                else if(name == TO_STR(m_deadCellColor))
                    m_deadCellColor = newColor;
                else if(name == TO_STR(m_gridColor))
                    m_gridColor = newColor;
            }
            break;

            default:
            continue;
        }
    }

    if(reader.hasError())
    {
        QMessageBox error;
        error.critical(this, tr("Error"), QString("%1: %2").arg(tr("Error occured during loading XML")).arg(reader.errorString()));
        error.setFixedSize(500, 200);
    }
    else {
        lk.disable();
        ui->speedSlider->setValue(m_nextRoundsIntervalMs);
        m_areas.resize(m_sizeX, m_sizeY);
        createGrid();
        colorize();
    }

    file.close();
}

void MainWindow::onActionPrint()
{
    QTimerLock lk(m_timer);

    //get square pixmap
    QPixmap img = ui->graphicsView->grab();
    QPrinter printer;

    QPrintDialog dialog(&printer, this);
    dialog.show();

    QPainter painter;

    qreal xscale = printer.pageRect().width() / static_cast<qreal>(img.width());
    qreal yscale = printer.pageRect().height() / static_cast<qreal>(img.height());
    qreal scale = qMin(xscale, yscale);


    painter.translate(printer.paperRect().x() + printer.pageRect().width()/2,
                       printer.paperRect().y() + printer.pageRect().height()/2);
    painter.scale(scale, scale);
    painter.translate(-width()/2, -height()/2);


    QRect target(0, 0, img.size().width(), img.size().height());


    painter.begin(&printer);
    painter.drawPixmap(target, img, target);
    painter.end();
}

void MainWindow::onActionChangeLanguage()
{
    static QStringList languages{"English", "Polish"};

    bool ok;
    QTimerLock lk(m_timer);
    QString selectedLanguage = QInputDialog::getItem(this, tr("Language"), tr("Change language:"), languages, 0, false, &ok);

    if(ok)
    {
        if(selectedLanguage == tr("English"))
        {
            QApplication::instance()->removeTranslator(&m_polishLanguage);
            languages = QStringList{"English", "Polish"};

            ui->retranslateUi(this);
        }
        else if(selectedLanguage == tr("Polish"))
        {
            m_polishLanguage.load("polish");
            QApplication::instance()->installTranslator(&m_polishLanguage);
            languages = QStringList{tr("English"), tr("Polish")};

            ui->retranslateUi(this);
        }
    }
}

void MainWindow::onActionTutorial()
{
    QTimerLock lk(m_timer);
    if(!QDesktopServices::openUrl(tr("https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life")))
        QMessageBox::warning(this, tr("Error"), tr("Cannot open Url!"));
}

void MainWindow::onActionAuthor()
{
    QTimerLock lk(m_timer);
    if(!QDesktopServices::openUrl(QString("https://github.com/ChairChandler")))
        QMessageBox::warning(this, tr("Error"), tr("Cannot open Url!"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::RoundCounter::RoundCounter(MainWindow *super): m_super(super) {}

void MainWindow::RoundCounter::set(const int &val)
{
    m_var = val;
    m_super->m_activeLabelStep->setNum(m_var);
}
