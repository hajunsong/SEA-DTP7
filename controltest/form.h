#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QTimer>
#include <QDebug>

#include <stdio.h>
#include <math.h>

#include "cuiapi.h"
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
    void btnStartClicked();
    void btnStopClicked();
    void btnSetGainClicked();
    void btnGetGainClicked();
    void btnTurnOnClicked();
    void btnTurnOffClicked();
    void btnUpClicked();
	void btnDownClicked();

private:
    Ui::Form *ui;
    QTimer *timer;

    bool flag;
	double data[600*6];
    unsigned int indx;
	long value;

    FILE *fp;
};

#endif // FORM_H
