#include "formjog.h"
#include "ui_formjog.h"
#include "cnrobo.h"
#include <math.h>
#include <QDebug>


FormJog::FormJog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormJog)
{
    ui->setupUi(this);

    m_timer = new QTimer(this);
    m_timer->setInterval(200);

    /* connect buttons */
    m_jointMinus.append(ui->btnM1);
    m_jointMinus.append(ui->btnM2);
    m_jointMinus.append(ui->btnM3);
    m_jointMinus.append(ui->btnM4);
    m_jointMinus.append(ui->btnM5);
    m_jointMinus.append(ui->btnM6);
    m_jointMinus.append(ui->btnM7);

    m_jointPlus.append(ui->btnP1);
    m_jointPlus.append(ui->btnP2);
    m_jointPlus.append(ui->btnP3);
    m_jointPlus.append(ui->btnP4);
    m_jointPlus.append(ui->btnP5);
    m_jointPlus.append(ui->btnP6);
    m_jointPlus.append(ui->btnP7);

    m_lblJoint.append(ui->lblJoint1);
    m_lblJoint.append(ui->lblJoint2);
    m_lblJoint.append(ui->lblJoint3);
    m_lblJoint.append(ui->lblJoint4);
    m_lblJoint.append(ui->lblJoint5);
    m_lblJoint.append(ui->lblJoint6);
    m_lblJoint.append(ui->lblJoint7);

    m_lcdJoint.append(ui->lcdJ1);
    m_lcdJoint.append(ui->lcdJ2);
    m_lcdJoint.append(ui->lcdJ3);
    m_lcdJoint.append(ui->lcdJ4);
    m_lcdJoint.append(ui->lcdJ5);
    m_lcdJoint.append(ui->lcdJ6);
    m_lcdJoint.append(ui->lcdJ7);

    for(int i = 0 ; i < m_jointMinus.size() ; i++)
    {
        connect(m_jointMinus[i], SIGNAL(pressed()), this, SLOT(onJogPressed()));
        connect(m_jointPlus[i], SIGNAL(pressed()), this, SLOT(onJogPressed()));

        connect(m_jointMinus[i], SIGNAL(released()), this, SLOT(onJogReleased()));
        connect(m_jointPlus[i], SIGNAL(released()), this, SLOT(onJogReleased()));
    }

    /* turn on timer */
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    m_timer->start();

    m_iconOn = QIcon(":/icon/resource/poweron.png");
    m_iconOff = QIcon(":/icon/resource/poweroff.png");


     ui->btnServo->setIcon(m_iconOff);
     ui->btnServo->setFocusPolicy(Qt::NoFocus);
     ui->btnCoordinate->setFocusPolicy(Qt::NoFocus);
     ui->btnEnable->setFocusPolicy(Qt::NoFocus);
     ui->btnInching->setFocusPolicy(Qt::NoFocus);
     ui->btnResetError->setFocusPolicy(Qt::NoFocus);
     ui->btnTeachSpeed->setFocusPolicy(Qt::NoFocus);
     ui->btnTRmode->setFocusPolicy(Qt::NoFocus);

     for(int i = 0 ; i < m_jointMinus.size() ; i++)
     {
         m_jointMinus[i]->setFocusPolicy(Qt::NoFocus);
         m_jointPlus[i]->setFocusPolicy(Qt::NoFocus);
     }

     m_count = true;
}

FormJog::~FormJog()
{
    delete ui;
}

void FormJog::appendOutput(const QString &str)
{
    ui->txtOutput->append(str);
    ui->txtOutput->ensureCursorVisible();
}

unsigned int BITS[] = {
    0x00000001,
    0x00000002,
    0x00000004,
    0x00000008,
    0x00000010,
    0x00000020,
    0x00000040,
    0x00000080,
    0x00000100,
    0x00000200,
    0x00000400,
    0x00000800,
    0x00001000,
    0x00002000,
    0x00004000,
    0x00008000,
    0x00010000,
    0x00020000,
    0x00040000,
    0x00080000,
    0x00100000,
    0x00200000,
    0x00400000,
    0x00800000,
    0x01000000,
    0x02000000,
    0x04000000,
    0x08000000,
    0x10000000,
    0x20000000,
    0x40000000,
    0x80000000
};

void FormJog::onJogPressed()
{
    CNRobo* pCon = CNRobo::getInstance();
    QPushButton* btn = (QPushButton*)sender();

    for(int i = 0 ; i < m_jointMinus.size() ; i++)
    {
        if(m_jointMinus[i] == btn)
        {
            pCon->setJogOn(0, BITS[i]);
            qDebug("BITS[i] = %d", BITS[i]);
            return;
        }
    }

    for(int i = 0 ; i < m_jointPlus.size() ; i++)
    {
        if(m_jointPlus[i] == btn)
        {
            pCon->setJogOn(BITS[i], 0);
            qDebug("BITS[i] = %d", BITS[i]);
            return;
        }
    }
}

void FormJog::onJogReleased()
{
    CNRobo* pCon = CNRobo::getInstance();
    QPushButton* btn = (QPushButton*)sender();

    for(int i = 0; i < m_jointMinus.size(); i++)
    {
        if(m_jointMinus[i] == btn)
        {                
            pCon->setJogOff(0, BITS[i]);
            qDebug("BITS[i] = %d", BITS[i]);
            return;
        }
    }

    for(int i = 0; i < m_jointPlus.size(); i++)
    {
        if(m_jointPlus[i] == btn)
        {
            pCon->setJogOff(BITS[i], 0);
            qDebug("BITS[i] = %d", BITS[i]);
            return;
        }
    }

}

void FormJog::onTimer()
{
    CNRobo* pCon = CNRobo::getInstance();

    unsigned int status = pCon->getStatus();
    int armstatus = pCon->getArmStatus();

    bool error_status = pCon->isError();
    bool warning_status = pCon->isWarning();

    /* check status */
    if(error_status || warning_status)
        ui->chkError->setChecked(true);
    else
        ui->chkError->setChecked(false);

    ui->chkMotorOn->setChecked(  pCon->isMotorOn()  );
    ui->btnServo->setIcon(pCon->isMotorOn() ? m_iconOn : m_iconOff);

    ui->chkTPEnabled->setChecked(  pCon->isTPEnable()  );
    ui->chkMoving->setChecked(  pCon->isMoving()  );
    ui->chkTPInching->setChecked(  pCon->isTPInching()  );

    /* check speed */
    int speed = pCon->getTeachSpeed();
    switch(speed)
    {
    case 0:
        ui->txtJogSpeed->setText("Low");
        break;
    case 1:
        ui->txtJogSpeed->setText("Mid");
        break;
    case 2:
        ui->txtJogSpeed->setText("High");
        break;
    case 3:
        ui->txtJogSpeed->setText("Low");
        break;
    }

    /* check coordinate */
    int coord = pCon->getCoordinate();
    switch(coord)
    {
    case 0:
        ui->txtTPCoordinate->setText("Joint");
        break;
    case 1:
        ui->txtTPCoordinate->setText("Base");
        break;
    case 2:
        ui->txtTPCoordinate->setText("Tool");
        break;
    case 3:
        ui->txtTPCoordinate->setText("User");
        break;
    }

    /* check mode */
    ui->txtTRMode->setText(pCon->isTeach() ? "Teach" : "Repeat");

    /* show current position */
    QString str;

    int nAxis = pCon->getAxisCount();
    if(nAxis > 7) nAxis = 7;

    bool coord_flag = true;
    int coordinate = pCon->getCoordinate();

    if(coordinate > 0)
        coord_flag = false;

    float* joint = pCon->getCurJoint();

    if(coord_flag)
    {
        for(int i = 0; i < nAxis; i++)
        {
            str.sprintf("%8.3f", joint[i]);
            m_lcdJoint[i]->display(str);
        }
    }
    else
    {
        bool useUserCoord = false;
        pCon->getUseUserCoordFlag(&useUserCoord);

        float* transCoord = useUserCoord == true ? pCon->getCurUC() : pCon->getCurTrans();

        for(int i = 0; i < 7; i++)
        {
            str.sprintf("%8.3f", transCoord[i]);
            m_lcdJoint[i]->display(str);
        }
    }

    /* text error code */
    QString errorCode;
    if(error_status && m_count)
    {
        pCon->getErrorMsg(errorCode);
        ui->txtErrorStatus->setText(errorCode);
        m_count = false;
    }
    else if(!error_status)
    {
        ui->txtErrorStatus->clear();
        m_count = true;
    }

    if(!pCon->getDryRunMode())
    {
        int* aVelocity = pCon->getMotorActualVelocity();
        int* aTorque = pCon->getMotorActualTorque();

        ui->txtMotorVelocity->setText(QString::number(aVelocity[0]));
        ui->txtMotorTorque->setText(QString::number((short)aTorque[0]));
    }
    else
    {
        ui->txtMotorVelocity->hide();
        ui->txtMotorTorque->hide();
        ui->label_7->hide();
        ui->label_8->hide();
    }
}

void FormJog::on_btnServo_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    bool curMotorOn = pCon->getServoOn();

    if(!curMotorOn)
        ui->btnServo->setIcon(m_iconOn);
    else
        ui->btnServo->setIcon(m_iconOff);

    bool error_status = pCon->isError();

    if(error_status == false)
    {
        pCon->setServoOn(!curMotorOn);
    }
}

void FormJog::on_btnEnable_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    bool cur = pCon->getEnableOn();

    pCon->setEnableOn(!cur);


}

void FormJog::on_btnInching_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    bool cur = pCon->getInchingOn();

    if(!cur)
        pCon->setInchingOn(true);
    else
        pCon->setInchingOn(false);
}

void FormJog::on_btnTRmode_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    bool cur = pCon->getTeachMode();
    pCon->setTeachMode(!cur);

}

void FormJog::on_btnTeachSpeed_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    int speed = pCon->getTeachSpeed();

    speed++;
    if(speed > 3) speed = 0;

    pCon->setTeachSpeed(speed);
}

void FormJog::on_btnSpeed_clicked()
{

}

void FormJog::on_btnCoordinate_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();


    if(!pCon->getServoOn()) return; // must be motor on

    int coord = pCon->getCoordinate();

    bool useUserCoord = false;
    pCon->getUseUserCoordFlag(&useUserCoord);


    if(useUserCoord)
    {
        if(coord == 0) coord = 3;
        else coord = 0;
    }
    else
    {
        coord++;

        if(coord >= 3) coord = 0;
    }


    pCon->setCoordinate(coord);

    bool coord_flag = true;
    if(coord > 0)
        coord_flag = false;

    setCoordinater(coord_flag);
}

void FormJog::on_btnHoldRun_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    pCon->holdProgram(0);
}

void FormJog::on_btnResetError_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    pCon->resetError();
    pCon->clearWarningCode();
}

void FormJog::on_btnResetEcatError_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    pCon->resetEcatError();
}


void FormJog::setCoordinater(bool coord)
{
    CNRobo* pCon = CNRobo::getInstance();
    QString str = "X,Y,Z,A,B,C,L";

    for(int i = 0 ; i < 7; i++)
    {
        m_lblJoint[i]->hide();
        m_lcdJoint[i]->hide();
        m_jointMinus[i]->hide();
        m_jointPlus[i]->hide();
    }

    if(coord)
    {
        for(int i = 0; i < pCon->getAxisCount(); i++)
        {
            m_lblJoint[i]->show();
            m_lcdJoint[i]->show();
            m_jointMinus[i]->show();
            m_jointPlus[i]->show();

            str.sprintf("J%d",i);
            m_lblJoint[i]->setText(str);
        }
    }
    else
    {
        for(int i = 0; i < 7; i++)
        {
            m_lblJoint[i]->show();
            m_lcdJoint[i]->show();
            m_jointMinus[i]->show();
            m_jointPlus[i]->show();

            m_lblJoint[i]->setText(str.section(',',i,i));
        }
    }
}
