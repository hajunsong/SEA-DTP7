#include "formtestinching.h"
#include "ui_formtestinching.h"
#include "cuiapi.h"
#include "formtest.h"
#include "cerror.h"
#include "dlgnumber.h"

FormTestInching::FormTestInching(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormTestInching)
{
    ui->setupUi(this);
}

FormTestInching::~FormTestInching()
{
    delete ui;
}


void FormTestInching::on_btnSetInchingValue_clicked()
{
    DlgNumber dlg;

    CUIApp* pCon = CUIApp::getInstance();

    int level = 0;
    float step_mm = 0;

    if(dlg.exec())
        level = dlg.sValue.toInt();

    dlg.sValue.clear();

    if(dlg.exec())
        step_mm = dlg.sValue.toFloat();

    QString str = QString("%1 / %2").arg(QString::number(level)).arg(QString::number(step_mm));

    ui->txtInchingValue_2->setText(str);

    /* level : 0 : low, 1: mid, 2: high */
    /* step_mm : data is 'mm' */
    pCon->setInchingStep(level, step_mm);
}

void FormTestInching::on_btnGetInchingValue_clicked()
{
    DlgNumber dlg;

    CUIApp* pCon = CUIApp::getInstance();

    int level;
    float step_mm;

    if(dlg.exec())
        level = dlg.sValue.toInt();

    /* level : 0 : low, 1: mid, 2: high */
    /* step_mm : data is 'mm' */
    pCon->getInchingStep(level, step_mm);

    QString str = QString("%2").arg(QString::number(step_mm));

    ui->txtInchingValue->setText(str);
}

void FormTestInching::on_btnGetInchingAValue_clicked()
{
    DlgNumber dlg;

    CUIApp* pCon = CUIApp::getInstance();

    int level;
    float step_deg;

    if(dlg.exec())
        level = dlg.sValue.toInt();

    /* level : 0 : low, 1: mid, 2: high */
    /* step_mm : data is 'mm' */
    pCon->getInchingStepAngular(level, step_deg);

    QString str = QString("%2").arg(QString::number(step_deg));
    ui->txtInchingAngleValue->setText(str);
}

void FormTestInching::on_btnSetInchingAValue_clicked()
{
    DlgNumber dlg;

    CUIApp* pCon = CUIApp::getInstance();

    int level = 0;
    float step_deg = 0;

    if(dlg.exec())
        level = dlg.sValue.toInt();

    dlg.sValue.clear();

    if(dlg.exec())
        step_deg = dlg.sValue.toFloat();

    QString str = QString("%1 / %2").arg(QString::number(level)).arg(QString::number(step_deg));

    ui->txtInchingAngleValue_2->setText(str);

    /* level : 0 : low, 1: mid, 2: high */
    /* step_mm : data is 'mm' */
    pCon->setInchingStepAngular(level, step_deg);
}


void FormTestInching::on_btnGetInchingAccTime_clicked()
{
    CUIApp* pCon = CUIApp::getInstance();

    float acctime;

    pCon->getInchingAccTime(acctime);

    ui->txtInchingAccTime->setText(QString::number(acctime));
}

void FormTestInching::on_btnSetInchingAccTime_clicked()
{
    DlgNumber dlg;

    CUIApp* pCon = CUIApp::getInstance();

    float acctime;

    if(dlg.exec())
        acctime = dlg.sValue.toFloat();

    pCon->setInchingAccTime(acctime);

    ui->txtInchingAccTime_2->setText(QString::number(acctime));
}
