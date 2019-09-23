#ifndef FORMAO_H
#define FORMAO_H

#include <QWidget>

namespace Ui {
class FormAO;
}

class FormAO : public QWidget
{
    Q_OBJECT

public:
    explicit FormAO(QWidget *parent = 0);
    ~FormAO();
protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

private slots:
    void onTimer();
    void on_btnNext_clicked();
    void on_btnPrev_clicked();

    void on_btnSetAO_clicked();

private:
    Ui::FormAO *ui;

    void regen();

    int m_idx;
    QTimer* m_timer;

};

#endif // FORMAO_H
