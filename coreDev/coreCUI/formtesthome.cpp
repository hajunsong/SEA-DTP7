#include "formtesthome.h"
#include "ui_formtesthome.h"
#include "cnrobo.h"
#include <QTimer>

FormTestHome::FormTestHome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormTestHome)
{
    ui->setupUi(this);
}

FormTestHome::~FormTestHome()
{
    delete ui;
}

void FormTestHome::showEvent(QShowEvent *)
{
    m_timer = new QTimer(this);

    m_timer->setInterval(200);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimer()));

    m_timer->start();
}

void FormTestHome::hideEvent(QHideEvent *)
{
    m_timer->stop();
}

void FormTestHome::on_btnStatr_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    pCon->setHomeStart();
}

void FormTestHome::on_btnStop_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();
     pCon->setHomeStop();
}

void FormTestHome::onTimer()
{
    CNRobo* pCon = CNRobo::getInstance();

    CNR_HOME_STATUS status = pCon->getHomeStatus();

    char* pmsg = "";
    switch(status)
    {
    case -1:
        pmsg = "Error";
        break;
    case 0:
        pmsg = "Ready";
        break;
    case 1:
        pmsg = "Searching";
        break;
    case 2:
        pmsg = "Found";
        break;
    default:
        ;
    };

    ui->txtHStatus->setText(pmsg);
}

void FormTestHome::on_btnHome_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();
    pCon->moveToHome(0);
}
