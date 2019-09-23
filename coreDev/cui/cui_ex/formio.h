#ifndef FORMIO_H
#define FORMIO_H

#include <QWidget>
#include <QPushButton>


namespace Ui {
class FormIO;
}

class FormIO : public QWidget
{
    Q_OBJECT

    QVector<QPushButton*> m_btns;

public:
    explicit FormIO(QWidget *parent = 0);
    ~FormIO();

private:
    Ui::FormIO *ui;

private slots:

    void changePage();
};

#endif // FORMIO_H
