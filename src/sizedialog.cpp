#include "sizedialog.h"
#include <QEventLoop>

SizeDialog::SizeDialog(QObject *parent, const size_t &minSize, const size_t &maxSize) : QObject(parent)
{
    m_dialog = new QDialog;
    m_mainLayout = new QFormLayout;
    m_buttonLayout = new QHBoxLayout;

    m_buttonSizeX = new QSpinBox;
    m_buttonSizeY = new QSpinBox;

    int iMinSize, iMaxSize;

    iMinSize = static_cast<int>(minSize);
    iMaxSize = static_cast<int>(maxSize);

    m_buttonSizeX->setRange(iMinSize, iMaxSize);
    m_buttonSizeY->setRange(iMinSize, iMaxSize);

    m_mainLayout->addRow(tr("Width"), m_buttonSizeX);
    m_mainLayout->addRow(tr("Height"), m_buttonSizeY);

    m_buttonOk = new QPushButton(tr("OK"));
    m_buttonCancel = new QPushButton(tr("Cancel"));

    m_buttonLayout->addWidget(m_buttonOk);
    m_buttonLayout->addWidget(m_buttonCancel);

    m_mainLayout->addRow(m_buttonLayout);

    m_dialog->setSizePolicy(QSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum));
    m_dialog->setModal(true);
    m_dialog->setWindowFlags(Qt::Dialog|Qt::MSWindowsFixedSizeDialogHint);
    m_dialog->setLayout(m_mainLayout);

    QObject::connect(m_buttonOk,
                     &QPushButton::clicked,
                     this,
                     [this]()
    {
        size_t sizeX, sizeY;
        sizeX = static_cast<size_t>(m_buttonSizeX->value());
        sizeY = static_cast<size_t>(m_buttonSizeY->value());

        m_dialog->close();
        emit accept(sizeX, sizeY);
    });

    QObject::connect(m_buttonCancel,
                     &QPushButton::clicked,
                     this,
                     [this]()
    {
        m_dialog->close();
        emit cancel();
    });
}

QPair<SizeDialog::Sizes, bool> SizeDialog::getSizes(QObject *parent, const size_t &minSize, const size_t &maxSize)
{
    SizeDialog dialog(parent, minSize, maxSize);
    QObject obj;
    QEventLoop loop;

    bool success;
    size_t x, y;
    QObject::connect(&dialog,
                     &SizeDialog::accept,
                     &obj,
                     [&success, &x, &y, &loop](size_t sizeX, size_t sizeY)
    {
        success = true;
        x = sizeX;
        y = sizeY;

        loop.exit();
    });

    QObject::connect(&dialog,
                     &SizeDialog::cancel,
                     &obj,
                     [&success, &loop]()
    {
        success = false;
        loop.exit();
    });

    dialog.show();
    loop.exec();

    QPair<Sizes, bool> val(Sizes(x, y), success);
    return val;
}

void SizeDialog::show()
{
    m_dialog->show();
}

void SizeDialog::close()
{
    m_dialog->close();
}
