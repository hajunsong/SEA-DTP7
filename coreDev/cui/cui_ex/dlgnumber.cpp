#include "dlgnumber.h"
#include "ui_dlgnumber.h"

DlgNumber::DlgNumber(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgNumber)
{
    ui->setupUi(this);
    DlgNumber::setWindowTitle("Input Number");
}

DlgNumber::~DlgNumber()
{
    delete ui;
}

void DlgNumber::on_btn0_clicked()
{
    handdleButton((QPushButton*)sender());
}

void DlgNumber::on_btn1_clicked()
{
    handdleButton((QPushButton*)sender());
}

void DlgNumber::on_btn2_clicked()
{
    handdleButton((QPushButton*)sender());
}

void DlgNumber::on_btn3_clicked()
{
    handdleButton((QPushButton*)sender());
}

void DlgNumber::on_btn4_clicked()
{
    handdleButton((QPushButton*)sender());
}

void DlgNumber::on_btn5_clicked()
{
    handdleButton((QPushButton*)sender());
}

void DlgNumber::on_btn6_clicked()
{
    handdleButton((QPushButton*)sender());
}

void DlgNumber::on_btn7_clicked()
{
    handdleButton((QPushButton*)sender());
}

void DlgNumber::on_btn8_clicked()
{
    handdleButton((QPushButton*)sender());
}

void DlgNumber::on_btn9_clicked()
{
    handdleButton((QPushButton*)sender());
}

void DlgNumber::on_btnDot_clicked()
{
    handdleButton((QPushButton*)sender());
}

void DlgNumber::on_btnMinus_clicked()
{
    handdleButton((QPushButton*)sender());
}

void DlgNumber::on_btnClear_clicked()
{
    handdleButton((QPushButton*)sender());
}

void DlgNumber::on_btnDel_clicked()
{
    handdleButton((QPushButton*)sender());
}

void DlgNumber::on_btnOK_clicked()
{
    iValue = sValue.toInt();
    fValue = sValue.toFloat();

    accept();
}

void DlgNumber::on_btnCancel_clicked()
{
    reject();

}

void DlgNumber::handdleButton(QPushButton *btn)
{
    QString strPrev;

    strPrev = sValue;

    if(btn == ui->btn0)
    {
        strPrev.append('0');
    }
    else if(btn == ui->btn1)
    {
        strPrev.append('1');
    }
    else if(btn == ui->btn2)
    {
        strPrev.append('2');
    }
    else if(btn == ui->btn3)
    {
        strPrev.append('3');
    }
    else if(btn == ui->btn4)
    {
        strPrev.append('4');
    }
    else if(btn == ui->btn5)
    {
        strPrev.append('5');
    }
    else if(btn == ui->btn6)
    {
        strPrev.append('6');
    }
    else if(btn == ui->btn7)
    {
        strPrev.append('7');
    }
    else if(btn == ui->btn8)
    {
        strPrev.append('8');
    }
    else if(btn == ui->btn9)
    {
        strPrev.append('9');
    }
    else if(btn == ui->btnDot)
    {
        if(!strPrev.contains('.'))
            strPrev.append('.');
    }
    else if(btn == ui->btnDel)
    {
        if(strPrev.length() > 0)
            strPrev.remove(strPrev.length()-1, 1);
    }
    else if(btn == ui->btnClear)
    {
        strPrev.clear();
    }
    else if(btn == ui->btnMinus)
    {
        if(strPrev.length() > 0)
        {
            if(strPrev[0] != '-')
            {
                strPrev.insert(0, '-');
            }
            else
            {
                strPrev.remove(0, 1);
            }
        }
        else
            strPrev.append('-');
    }

    this->sValue = strPrev;
    setDisplayText();


}

void DlgNumber::setDisplayText()
{
    ui->numberInput->setText(this->sValue);
}
