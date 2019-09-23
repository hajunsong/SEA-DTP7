#include "formtestworldzone.h"
#include "ui_formtestworldzone.h"
#include "cnrobo.h"
#include "cntype.h"

#include <QTimer>
#include "formtest.h"



FormTestWorldZone::FormTestWorldZone(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormTestWorldZone)
{
    ui->setupUi(this);

    m_timer = new QTimer(this);
    m_timer->setInterval(200);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimer()));

    m_index = 0;
}

FormTestWorldZone::~FormTestWorldZone()
{
    delete ui;
}

void FormTestWorldZone::showEvent(QShowEvent *)
{
    m_timer->start();
}

void FormTestWorldZone::hideEvent(QHideEvent *)
{
    m_timer->stop();
}

void FormTestWorldZone::onTimer()
{
    CNRobo* pCon = CNRobo::getInstance();

    int is_enabled = 0;
    int is_negate = 0;

    pCon->WZGetFlag(m_index, is_enabled, is_negate);

    if(is_enabled == 0)
    {
        ui->cboxDisable->setChecked(true);
        ui->cboxEnable->setChecked(false);
    }
    else
    {
        ui->cboxDisable->setChecked(false);
        ui->cboxEnable->setChecked(true);
    }

    if(is_negate == 0)
        ui->cboxNegate->setChecked(false);
    else
        ui->cboxNegate->setChecked(true);

    bool flag = pCon->getWZCheckFlag();

    ui->cboxCheck->setChecked(flag);

}
void FormTestWorldZone::on_btnAddBox_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    m_index = ui->txtIndex->text().toInt();
    int op = 1;
    cn_vec3 min;
    cn_vec3 max;
    cn_trans2 frame;
    memset(&frame, 0, sizeof(frame));

    //form 10,10,10
    min.x = -29.953827;
    min.y = -1220;
    min.z = 0;

    //to 110,110,110
    max.x = 403.631927;
    max.y = 1220.477539;
    max.z = 1000;

    pCon->getCurBaseFrame(frame);
    pCon->WZAddBox(m_index, op, min, max, frame);

    //form 10,10,10
    min.x = 99.904572;
    min.y = 530.866028;
    min.z = -1000;

    //to 110,110,110
    max.x = 301.625610;
    max.y = 754.643677;
    max.z = 501.914856;

    op = -1;

    pCon->WZAddBox(m_index, op, min, max, frame);



}

void FormTestWorldZone::on_btnAddCyl_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    m_index = ui->txtIndex->text().toInt();
    int op = 0;
    cn_vec3 pc;
    float r = 100; //radius
    float h = 100;
    cn_trans2 frame;
    memset(&frame, 0, sizeof(frame));

    //center 0,0,0
    pc.x = 1;
    pc.y = 1;
    pc.z = 1;

    pCon->getCurBaseFrame(frame);
    pCon->WZAddCyl(m_index,op,pc,r,h,frame);
}



void FormTestWorldZone::on_btnClear_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    m_index = ui->txtIndex->text().toInt();

    pCon->WZClear(m_index);
}

void FormTestWorldZone::on_btnSetEnable_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    m_index = ui->txtIndex->text().toInt();
    int is_enabled;
    int is_negate;

    pCon->WZGetFlag(m_index, is_enabled, is_negate);

    is_negate = ui->txtAddSub->text().toInt();

    if(!is_enabled)
    {
        pCon->WZEnable(m_index, is_negate);
    }
    else
    {
        pCon->WZDisable(m_index);
    }
}


void FormTestWorldZone::on_btnGetBox_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    QString str;
    QStringList txtOut;

    m_index = ui->txtIndex->text().toInt();
    int entity_index = ui->txtEntityIndex->text().toInt();

    int type;
    pCon->WZGetEntityType(m_index, entity_index, type);
    str = QString("type = %1").arg(type);
    txtOut.append(str);

    int count;
    pCon->WZGetEntityCount(m_index, count);
    str = QString("count = %1").arg(count);
    txtOut.append(str);

    int op;
    pCon->WZGetEntityOperator(m_index, entity_index, op);
    str = QString("op = %1").arg(op);
    txtOut.append(str);

    cn_vec3 pmin;
    cn_vec3 pmax;
    pCon->WZGetEntityBox(m_index, entity_index, pmin, pmax);

    str = QString("pmin = ");
    txtOut.append(str);

    str = QString("x(%1), y(%2), z(%3)").arg(pmin.x).arg(pmin.y).arg(pmin.z);
    txtOut.append(str);

    str = QString("pmax = ");
    txtOut.append(str);

    str = QString("x(%1), y(%2), z(%3)").arg(pmax.x).arg(pmax.y).arg(pmax.z);
    txtOut.append(str);

    cn_trans2 frame;

    pCon->WZGetEntityFrame(m_index, entity_index, frame);

    str = QString("frame = ");
    txtOut.append(str);

    str = QString("n.x(%1), n.y(%2), n.z(%3)").arg(frame.n.x).arg(frame.n.y).arg(frame.n.z);
    txtOut.append(str);

    str = QString("o.x(%1), o.y(%2), o.z(%3)").arg(frame.o.x).arg(frame.o.y).arg(frame.o.z);
    txtOut.append(str);

    str = QString("a.x(%1), a.y(%2), a.z(%3)").arg(frame.a.x).arg(frame.a.y).arg(frame.a.z);
    txtOut.append(str);

    str = QString("p.x(%1), p.y(%2), p.z(%3)").arg(frame.p.x).arg(frame.p.y).arg(frame.p.z);
    txtOut.append(str);

    appendTxtOut(txtOut);
}

void FormTestWorldZone::on_btnGetCyl_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    QString str;
    QStringList txtOut;

    m_index = ui->txtIndex->text().toInt();
    int entity_index = ui->txtEntityIndex->text().toInt();

    float r, h;

    int type;
    pCon->WZGetEntityType(m_index, entity_index, type);
    str = QString("type = %1").arg(type);
    txtOut.append(str);

    int count;
    pCon->WZGetEntityCount(m_index, count);
    str = QString("count = %1").arg(count);
    txtOut.append(str);

    int op;
    pCon->WZGetEntityOperator(m_index, entity_index, op);

    str = QString("op = %1").arg(op);
    txtOut.append(str);

    cn_vec3 pc;
    pCon->WZGetEntityCyl(m_index, entity_index, pc, r, h);

    str = QString("pc = ");
    txtOut.append(str);

    str = QString("x(%1), y(%2), z(%3)").arg(pc.x).arg(pc.y).arg(pc.z);
    txtOut.append(str);

    str = QString("r = %1").arg(r);
    txtOut.append(str);

    str = QString("h = %1").arg(h);
    txtOut.append(str);

    cn_trans2 frame;
    memset(&frame, 0, sizeof(struct cn_trans2));

    pCon->WZGetEntityFrame(m_index, entity_index, frame);

    str = QString("frame = ");
    txtOut.append(str);

    str = QString("n.x(%1), n.y(%2), n.z(%3)").arg(frame.n.x).arg(frame.n.y).arg(frame.n.z);
    txtOut.append(str);

    str = QString("o.x(%1), o.y(%2), o.z(%3)").arg(frame.o.x).arg(frame.o.y).arg(frame.o.z);
    txtOut.append(str);

    str = QString("a.x(%1), a.y(%2), a.z(%3)").arg(frame.a.x).arg(frame.a.y).arg(frame.a.z);
    txtOut.append(str);

    str = QString("p.x(%1), p.y(%2), p.z(%3)").arg(frame.p.x).arg(frame.p.y).arg(frame.p.z);
    txtOut.append(str);

    appendTxtOut(txtOut);

}

void FormTestWorldZone::on_btnSetCheck_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();
    unsigned char flag = pCon->getWZCheckFlag();
     pCon->setWZCheckFlag(!flag);
}

void FormTestWorldZone::on_btnSaveAll_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();
    pCon->WZSaveAll();
}

void FormTestWorldZone::appendTxtOut(QStringList list)
{
    FormTest* pTest = FormTest::getInstance();
    pTest->appendTxtOut(list);
}


