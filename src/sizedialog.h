#ifndef SIZEDIALOG_H
#define SIZEDIALOG_H

#include <QObject>
#include <QDialog>
#include <QFormLayout>
#include <QSpinBox>
#include <QPushButton>

//Class for creating dialog to get the new sizes of the game map
class SizeDialog: public QObject
{
    Q_OBJECT

public:
    using Sizes = QPair<size_t, size_t>;

    explicit SizeDialog(QObject *parent, const size_t &minSize, const size_t &maxSize);
    static QPair<Sizes, bool> getSizes(QObject *parent, const size_t &minSize, const size_t &maxSize);
public slots:
    void show();
    void close();
signals:
    void accept(size_t newSizeX, size_t newSizeY);
    void cancel();
private:
    QDialog *m_dialog;
    QFormLayout *m_mainLayout;
    QHBoxLayout *m_buttonLayout;
    QSpinBox *m_buttonSizeX, *m_buttonSizeY;
    QPushButton *m_buttonOk, *m_buttonCancel;
};

#endif // SIZEDIALOG_H
