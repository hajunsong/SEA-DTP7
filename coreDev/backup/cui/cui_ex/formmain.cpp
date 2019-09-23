#include "formmain.h"
#include "ui_formmain.h"
#include <QString>
#include "cuiapi.h"
#include <QTimer>
#include <QDebug>
#include "dlgzeroing.h"
#include "formmainwindow.h"

extern unsigned int BITS[];

FormMain::FormMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormMain)
{
    ui->setupUi(this);

    m_timer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimer()));
}

FormMain::~FormMain()
{
    delete ui;
}


void FormMain::showEvent(QShowEvent *)
{
    m_timer->start(200);
}

void FormMain::hideEvent(QHideEvent *)
{
    m_timer->stop();
}


void FormMain::onTimer()
{

}

void FormMain::on_btnTest_clicked()
{
    CUIApp* probo = CUIApp::getInstance();

    QStringList pgms;

    probo->getPrograms(pgms);
    for(int i = 0; i < pgms.size(); i++)
    {
        ui->txtOut->append(pgms[i]);
    }

    QStringList steps;
    probo->getProgramSteps("test", steps);

    for(int i = 0; i < steps.size(); i++)
    {
        ui->txtOut->append(steps[i]);
    }

}

void FormMain::on_btnLogin_clicked()
{


}

void FormMain::on_btnLock_clicked()
{


}

void FormMain::on_btnDI_clicked()
{
    CUIApp* probo = CUIApp::getInstance();
    cn_ui32 di[4];

    probo->getDI(di, 4);

    QString str;
    str.sprintf("DI = 0x%x, 0x%x, 0x%x, 0x%x", di[0], di[1], di[2], di[3]);

    ui->txtOut->append(str);

}

void FormMain::on_btnDO_clicked()
{
    CUIApp* probo = CUIApp::getInstance();
    cn_ui32 dout[4];
    probo->getDO(dout, 4);

    QString str;
    str.sprintf("DO = 0x%x, 0x%x, 0x%x, 0x%x", dout[0], dout[1], dout[2], dout[3]);

    ui->txtOut->append(str);
}

void FormMain::on_btnDOSet_clicked()
{
    CUIApp* probo = CUIApp::getInstance();

    QVector<int> do_list;

    QString str = ui->txtDOSet->text();
    QStringList strList = str.split(",", QString::SkipEmptyParts);

    for(int i = 0; i < strList.size(); i++)
    {
        int index = strList[i].toInt();

        do_list.append(index);
    }

    probo->setDO(do_list.data(), do_list.size());

    /* get current do */
    cn_ui32 dout[4];

    probo->getDO(dout, 4);
    str.sprintf("DO = 0x%x, 0x%x, 0x%x, 0x%x", dout[0], dout[1], dout[2], dout[3]);

    ui->txtOut->append(str);

}

void FormMain::on_btnAI_clicked()
{
    CUIApp* probo = CUIApp::getInstance();
    cn_f32 val[8];

    probo->getAI(val, 8);

    QString str;
    str.sprintf("AI = %.2f, %.2f, %.2f, %.2f", val[0], val[1], val[2], val[3]);

    ui->txtOut->append(str);

}

void FormMain::on_btnAO_clicked()
{
    CUIApp* probo = CUIApp::getInstance();
    cn_f32 val[8];

    probo->getAO(val, 8);

    QString str;
    str.sprintf("AO = %.2f, %.2f, %.2f, %.2f", val[0], val[1], val[2], val[3]);

    ui->txtOut->append(str);


}

void FormMain::on_btnAOSet_clicked()
{
    CUIApp* probo = CUIApp::getInstance();

    QString str = ui->txtAOSet->text();
    QStringList strList = str.split(",", QString::SkipEmptyParts);

    if(strList.size() < 2) return;

    int channel = strList[0].toInt();
    float value = strList[1].toFloat();

    if(channel <= 0 || channel > 128) return;

    probo->setAO(channel-1, value);

    cn_f32 val[8];

    probo->getAO(val, 8);

    str.sprintf("AO = %.2f, %.2f, %.2f, %.2f", val[0], val[1], val[2], val[3]);

    ui->txtOut->append(str);
}


void FormMain::on_btnZeroing_clicked()
{

    DlgZeroing dlg;

    dlg.exec();
}


void FormMain::on_btnService_clicked()
{
//    CUIApp* probo = CUIApp::getInstance();

//   if(!probo->isConnected())
//   {
//       probo->startService();
//   }
//   else
//   {
//       probo->stopService();
//   }
}

void FormMain::on_btnClean_clicked()
{
    ui->txtOut->clear();
}

void FormMain::on_btnClose_clicked()
{
    CUIApp* probo = CUIApp::getInstance();

    probo->setStandardMode(true);
}
