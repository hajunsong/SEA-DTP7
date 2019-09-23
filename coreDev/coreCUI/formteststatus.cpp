#include "formteststatus.h"
#include "ui_formteststatus.h"
#include "cnrobo.h"
#include <QTimer>

FormTestStatus::FormTestStatus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormTestStatus)
{
    ui->setupUi(this);

    m_timer = new QTimer(this);
    m_timer->setInterval(200);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimer()));
}

FormTestStatus::~FormTestStatus()
{
    delete ui;
}

void FormTestStatus::showEvent(QShowEvent *)
{
    m_timer->start(100);
}

void FormTestStatus::hideEvent(QHideEvent *)
{
    m_timer->stop();
}

void FormTestStatus::onTimer()
{
    CNRobo* pCon = CNRobo::getInstance();

    QString TaskMainStatus = QString::number(pCon->getTaskStatus(0));
    QString TaskSubStatus = QString::number(pCon->getTaskStatus(1));

    ui->txtMainTaskStatus->setText(TaskMainStatus);
    ui->txtSubTaskStatus->setText(TaskSubStatus);
}
