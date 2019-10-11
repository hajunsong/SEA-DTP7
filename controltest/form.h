#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QTimer>
#include <QDebug>

#include <stdio.h>
#include <math.h>

#include "functions.h"
#include "cuiapi.h"

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT
    
public:
    explicit Form(QWidget *parent = 0);
    ~Form();
    
private slots:
    void timeout();
    void btnStartClicked();
    void btnStopClicked();
    void btnSetGainClicked();
    void btnGetGainClicked();
    void btnTurnOnClicked();
    void btnTurnOffClicked();

private:
    Ui::Form *ui;
    QTimer *timer;

    long int enc1, enc2, pos, vel, enc_diff;
    long tor;
    double pos_deg, vel_rpm, vel_deg;
    short tor_interval;
    double torque;
    bool up_flag, down_flag, interval_up_flag, interval_down_flag;
    short tick;

    double TP_data[5];
    bool flag;
};

#endif // FORM_H
