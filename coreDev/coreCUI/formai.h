#ifndef FORMAI_H
#define FORMAI_H

#include <QWidget>

namespace Ui {
class FormAI;
}

class FormAI : public QWidget
{
    Q_OBJECT

public:
    explicit FormAI(QWidget *parent = 0);
    ~FormAI();

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);


private slots:
    void onTimer();


    void on_btnNext_clicked();

    void on_btnPrev_clicked();

private:
    Ui::FormAI *ui;

    void regen();

    int m_idx;
    QTimer* m_timer;

};

#endif // FORMAI_H
