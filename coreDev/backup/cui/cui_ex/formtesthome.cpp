#include "formtesthome.h"
#include "ui_formtesthome.h"
#include "cuiapi.h"
#include "formtest.h"
#include "cerror.h"

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
    CUIApp* pCon = CUIApp::getInstance();

    pCon->setHomeStart();
}

void FormTestHome::on_btnStop_clicked()
{
    CUIApp* pCon = CUIApp::getInstance();
     pCon->setHomeStop();
}

void FormTestHome::onTimer()
{
    CUIApp* pCon = CUIApp::getInstance();

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
    CUIApp* pCon = CUIApp::getInstance();
    pCon->moveToHome(0);
}

void FormTestHome::on_btnSystemLimitOn_clicked()
{
    CUIApp* pCon = CUIApp::getInstance();

    pCon->setSoftLimitMonitorFlag(false);
}

void FormTestHome::on_btnSystemLimitOff_clicked()
{
    CUIApp* pCon = CUIApp::getInstance();

    pCon->setSoftLimitMonitorFlag(true);
}

void FormTestHome::on_btnGetHomePosition_clicked()
{
    CUIApp* pCon = CUIApp::getInstance();

    int index = ui->txtHomePositionIndex->text().toInt();
    int npos = pCon->getAxisCount();
    float pos[32];
    memset(pos, 0, sizeof(pos));
    float bound;

    pCon->getHomePosition(index, pos, npos, bound);

    appendTxtOut(QString::number(index));

    for(int i = 0; i < npos; i++)
        appendTxtOut(QString::number(pos[i]));

    appendTxtOut(QString::number(bound));
}

void FormTestHome::on_btnSetHomePosition_clicked()
{
    CUIApp* pCon = CUIApp::getInstance();

    int index = ui->txtHomePositionIndex->text().toInt();
    int npos = pCon->getAxisCount();
    float pos[32];
    memset(pos, 0, sizeof(pos));
    float bound = 0.01;

    QString str = ui->txtHomePositionPos->text();

    for(int i = 0; i < npos; i++)
    {
        pos[i] = str.section(",",i,i).toFloat();
    }

    pCon->setHomePosition(index, pos, npos, bound);
}

void FormTestHome::appendTxtOut(const QString& str)
{
    FormTest* pTest = FormTest::getInstance();
    QStringList list;

    list.append(str);
    pTest->appendTxtOut(list);
}
