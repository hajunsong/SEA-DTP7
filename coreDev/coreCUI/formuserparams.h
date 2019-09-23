#ifndef FORMUSERPARAMS_H
#define FORMUSERPARAMS_H

#include <QWidget>

namespace Ui {
class FormUserParams;
}

class FormUserParams : public QWidget
{
    Q_OBJECT

public:
    explicit FormUserParams(QWidget *parent = 0);
    ~FormUserParams();

private slots:
    void on_btnGetUserParams_clicked();
    void on_btnSetUserParams_clicked();

private:
    Ui::FormUserParams *ui;
};

#endif // FORMUSERPARAMS_H
