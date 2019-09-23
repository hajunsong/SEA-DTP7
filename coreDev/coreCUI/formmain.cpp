#include "formmain.h"
#include "ui_formmain.h"
#include <QString>
#include "cnrobo.h"
#include <QTimer>
#include <QDebug>
#include "dlgzeroing.h"
#include "mainwindow.h"

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
    CNRobo* probo = CNRobo::getInstance();

    m_timer->start(100);

    unsigned int cversion = 0;
    unsigned int sversion = 0;

    probo->getServerVersion(&sversion);
    cversion = probo->getVersion();

    QString str;

    str.sprintf("Server : %x, Client : %x", sversion, cversion);
    ui->txtVersion->setText(str);

}

void FormMain::hideEvent(QHideEvent *)
{
    m_timer->stop();
}


void FormMain::onTimer()
{
    CNRobo* probo = CNRobo::getInstance();

    ui->chkConnected->setChecked(probo->isConnected());

    int retcode = 0;
    bool    bLogin = false;
    bool    bLock = false;

    retcode = probo->getLoginStatus(&bLogin);
    ui->chkLogin->setChecked(bLogin);

    probo->getLockStatus(&bLock);
    ui->chkLock->setChecked(bLock);
}

void FormMain::on_btnTest_clicked()
{
    CNRobo* probo = CNRobo::getInstance();

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
    CNRobo* probo = CNRobo::getInstance();

    int retcode = 0;

    retcode = probo->login("corerobot");

    if(retcode != 0)
    {
        qDebug() << "login failed";
    }

}

void FormMain::on_btnLock_clicked()
{
    CNRobo* probo = CNRobo::getInstance();

    int retcode = 0;
    bool bLock = false;
    probo->getLockStatus(&bLock);

    if(!bLock)
    {
        retcode = probo->lock(10000);
    }
    else
    {
        retcode = probo->unlock();
    }

    if(retcode != 0)
    {
        qDebug() << "lock failed";
    }

}

void FormMain::on_btnDI_clicked()
{
    CNRobo* probo = CNRobo::getInstance();
    cn_ui32 di[4];

    probo->getDI(di, 4);

    QString str;
    str.sprintf("DI = 0x%x, 0x%x, 0x%x, 0x%x", di[0], di[1], di[2], di[3]);

    ui->txtOut->append(str);

}

void FormMain::on_btnDO_clicked()
{
    CNRobo* probo = CNRobo::getInstance();
    cn_ui32 dout[4];
    probo->getDO(dout, 4);

    QString str;
    str.sprintf("DO = 0x%x, 0x%x, 0x%x, 0x%x", dout[0], dout[1], dout[2], dout[3]);

    ui->txtOut->append(str);
}

void FormMain::on_btnDOSet_clicked()
{
    CNRobo* probo = CNRobo::getInstance();

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
    CNRobo* probo = CNRobo::getInstance();
    cn_f32 val[8];

    probo->getAI(val, 8);

    QString str;
    str.sprintf("AI = %.2f, %.2f, %.2f, %.2f", val[0], val[1], val[2], val[3]);

    ui->txtOut->append(str);

}

void FormMain::on_btnAO_clicked()
{
    CNRobo* probo = CNRobo::getInstance();
    cn_f32 val[8];

    probo->getAO(val, 8);

    QString str;
    str.sprintf("AO = %.2f, %.2f, %.2f, %.2f", val[0], val[1], val[2], val[3]);

    ui->txtOut->append(str);


}

void FormMain::on_btnAOSet_clicked()
{
    CNRobo* probo = CNRobo::getInstance();

    QString str = ui->txtAOSet->text();
    QStringList strList = str.split(",", QString::SkipEmptyParts);

    if(strList.size() < 2) return;

    int channel = strList[0].toInt();
    float value = strList[1].toFloat();

    if(channel <= 0 || channel > 128) return;

    probo->setAO(channel-1, value);
}


void FormMain::on_btnZeroing_clicked()
{

    DlgZeroing dlg;

    dlg.exec();
}


void FormMain::on_btnService_clicked()
{
    CNRobo* probo = CNRobo::getInstance();

   if(!probo->isConnected())
   {
       probo->startService();
   }
   else
   {
       probo->stopService();
   }
}

void FormMain::on_btnClean_clicked()
{
    ui->txtOut->clear();
}
