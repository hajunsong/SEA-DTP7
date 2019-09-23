#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QTimer>
#include <QDebug>

#include <stdio.h>
#include <math.h>

#include "functions.h"

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
    void btnUpClicked();
    void btnDownClicked();
    void btnClearClicked();
    void btnOnClicked();
    void btnOffClicked();
    void btnIntervalUpClicked();
    void btnIntervalDownClicked();
private:
    Ui::Form *ui;
    QTimer *timer;

    long int enc1, enc2, pos, vel;
    long tor;
    double pos_deg, vel_rpm, vel_deg;
    short tor_interval;
    double torque;
};
const short tick = 50;

#endif // FORM_H
