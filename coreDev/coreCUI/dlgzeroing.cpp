#include "dlgzeroing.h"
#include "ui_dlgzeroing.h"
#include "cnrobo.h"

DlgZeroing::DlgZeroing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgZeroing)
{
    ui->setupUi(this);
}

DlgZeroing::~DlgZeroing()
{
    delete ui;
}

void DlgZeroing::on_btnZeroing_clicked()
{
    CNRobo* probo = CNRobo::getInstance();
    QTextDocument* txtdoc = ui->txtZeroingOffset->document();
    QString strText = txtdoc->toPlainText();
    QStringList strList = strText.split("\n", QString::SkipEmptyParts);
    QString str;

    for(int i = 0; i < strList.count(); i++)
        str = strList[0];

    if(str.isEmpty())
        probo->zeroing(-1);
    else
        probo->zeroing(str.toULong());
}

void DlgZeroing::on_btnSetZeroingOffset_clicked()
{
    int retcode = 0;

    CNRobo* pCon = CNRobo::getInstance();
    QTextDocument* txtdoc = ui->txtZeroingOffset->document();
    QString strText = txtdoc->toPlainText();
    QStringList strList = strText.split("\n", QString::SkipEmptyParts);
    QString str;

    float posArray[32];
    memset(posArray, 0, sizeof(posArray));
    int naxis = strList.count();

    for(int i = 0; i < naxis; i++)
    {
        str = strList[i];
        posArray[i] = str.toFloat();
    }

    retcode = pCon->setZeroingOffset(posArray, naxis);

    ui->txtZeroingOffset->append(QString::number(retcode));
}

void DlgZeroing::on_btnGetZeroingOffset_clicked()
{
    ui->txtZeroingOffset->clear();

    int retcode = 0;

    CNRobo* pCon = CNRobo::getInstance();

    float posArray[32];
    memset(posArray, 0, sizeof(posArray));

    retcode = pCon->getZeroingOffset(posArray);

    if(retcode != 0)
    {
        ui->txtZeroingOffset->append(QString::number(retcode));
        return;
    }

    int naxis = pCon->getAxisCount();

    for(int i = 0; i < naxis; i++)
    {
        ui->txtZeroingOffset->append(QString::number(posArray[i], 'g', 6));
    }
}

void DlgZeroing::on_btnOk_clicked()
{
    QDialog::accept();
}

void DlgZeroing::on_btnClose_clicked()
{
    QDialog::reject();
}

void DlgZeroing::on_sbIndex_valueChanged(int arg1)
{
   if(arg1 >= 32)
       arg1 = 0;

   int motorIndex = 1;
   motorIndex = motorIndex << arg1 - 1;

   if(motorIndex <= 0)
       motorIndex = -1;

   ui->txtZeroingOffset->clear();
   ui->txtZeroingOffset->append(QString::number(motorIndex));
}

void DlgZeroing::on_btnGetZeroingCount_clicked()
{
    ui->txtZeroingOffset->clear();

    int retcode = 0;

    CNRobo* pCon = CNRobo::getInstance();

    long penc[20];
    memset(penc, 0, sizeof(penc));

    retcode = pCon->zeroingCount(penc);

    if(retcode != 0)
    {
        ui->txtZeroingOffset->append(QString::number(retcode));
        return;
    }

    int naxis = pCon->getAxisCount();

    for(int i = 0; i < naxis; i++)
    {
        ui->txtZeroingOffset->append(QString::number(penc[i]));
    }
}
