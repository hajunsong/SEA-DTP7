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

public slots:
	void btnStartClicked();
	void btnStopClicked();

	void timeout();
    
private:
    Ui::Form *ui;
	QTimer *timer;
	bool flag;
	float data[100*4*6];
	unsigned indx;
	FILE *fp;
    long enc[6];
    float rhat[6];
    long diff[6];
    float pos_rad[6];
};

#endif // FORM_H
