#ifndef FORMJOG_H
#define FORMJOG_H

#include <QWidget>
#include <QTimer>
#include <QPushButton>

#include <QVector>
#include <QLabel>
#include <QLCDNumber>
#include "cnrobo.h"

namespace Ui {
class FormJog;
}

class FormJog : public QWidget
{
    Q_OBJECT

public:
    explicit FormJog(QWidget *parent = 0);
    ~FormJog();

protected:
    void appendOutput(const QString& str);

private slots:
    void onJogPressed();
    void onJogReleased();

    void onTimer();
    void on_btnServo_clicked();
    void on_btnEnable_clicked();
    void on_btnTRmode_clicked();
    void on_btnTeachSpeed_clicked();
    void on_btnSpeed_clicked();
    void on_btnCoordinate_clicked();
    void on_btnHoldRun_clicked();
    void on_btnInching_clicked();
    void on_btnResetError_clicked();
    void on_btnResetEcatError_clicked();


private:
    Ui::FormJog *ui;

    QTimer* m_timer;
    QIcon m_iconOn;
    QIcon m_iconOff;

    QVector<QPushButton*> m_jointMinus;
    QVector<QPushButton*> m_jointPlus;
    QVector<QLabel*> m_lblJoint;
    QVector<QLCDNumber*> m_lcdJoint;


    bool m_count;

    void setCoordinater(bool coord);


};

#endif // FORMJOG_H
