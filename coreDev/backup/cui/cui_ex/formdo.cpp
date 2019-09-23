#include "formdo.h"
#include "ui_formdo.h"
#include "cuiapi.h"

FormDO::FormDO(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDO)
{
    ui->setupUi(this);

    m_btnSet.append(ui->btn1);
    m_btnSet.append(ui->btn2);
    m_btnSet.append(ui->btn3);
    m_btnSet.append(ui->btn4);
    m_btnSet.append(ui->btn5);
    m_btnSet.append(ui->btn6);
    m_btnSet.append(ui->btn7);
    m_btnSet.append(ui->btn8);
    m_btnSet.append(ui->btn9);
    m_btnSet.append(ui->btn10);
    m_btnSet.append(ui->btn11);
    m_btnSet.append(ui->btn12);
    m_btnSet.append(ui->btn13);
    m_btnSet.append(ui->btn14);
    m_btnSet.append(ui->btn15);
    m_btnSet.append(ui->btn16);
    m_btnSet.append(ui->btn17);
    m_btnSet.append(ui->btn18);
    m_btnSet.append(ui->btn19);
    m_btnSet.append(ui->btn20);
    m_btnSet.append(ui->btn21);
    m_btnSet.append(ui->btn22);
    m_btnSet.append(ui->btn23);
    m_btnSet.append(ui->btn24);
    m_btnSet.append(ui->btn25);
    m_btnSet.append(ui->btn26);
    m_btnSet.append(ui->btn27);
    m_btnSet.append(ui->btn28);
    m_btnSet.append(ui->btn29);
    m_btnSet.append(ui->btn30);
    m_btnSet.append(ui->btn31);
    m_btnSet.append(ui->btn32);

    m_lblSet.append(ui->label1);
    m_lblSet.append(ui->label2);
    m_lblSet.append(ui->label3);
    m_lblSet.append(ui->label4);
    m_lblSet.append(ui->label5);
    m_lblSet.append(ui->label6);
    m_lblSet.append(ui->label7);
    m_lblSet.append(ui->label8);
    m_lblSet.append(ui->label9);
    m_lblSet.append(ui->label10);
    m_lblSet.append(ui->label11);
    m_lblSet.append(ui->label12);
    m_lblSet.append(ui->label13);
    m_lblSet.append(ui->label14);
    m_lblSet.append(ui->label15);
    m_lblSet.append(ui->label16);
    m_lblSet.append(ui->label17);
    m_lblSet.append(ui->label18);
    m_lblSet.append(ui->label19);
    m_lblSet.append(ui->label20);
    m_lblSet.append(ui->label21);
    m_lblSet.append(ui->label22);
    m_lblSet.append(ui->label23);
    m_lblSet.append(ui->label24);
    m_lblSet.append(ui->label25);
    m_lblSet.append(ui->label26);
    m_lblSet.append(ui->label27);
    m_lblSet.append(ui->label28);
    m_lblSet.append(ui->label29);
    m_lblSet.append(ui->label30);
    m_lblSet.append(ui->label31);
    m_lblSet.append(ui->label32);


    m_idx = 0;

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateStatus()));

    for(int i = 0 ; i < 32 ; i++)
    {
        connect(m_btnSet[i], SIGNAL(clicked()), this, SLOT(setDO()));
    }

    connect(ui->btnReset, SIGNAL(clicked()), this, SLOT(resetAll_DO()));
}

FormDO::~FormDO()
{
    delete ui;
}

void FormDO::showEvent(QShowEvent *)
{
    updateStatus();
    m_timer->start(200);
}

void FormDO::hideEvent(QHideEvent *)
{
    m_timer->stop();
}


void FormDO::updateStatus()
{
    CUIApp* probo = CUIApp::getInstance();
    cn_ui32 dout[4];
    cn_ui32 iResult;
    cn_ui32 mask = 1;

    probo->getDO(dout, 4);

    for(int i = 0; i < 32; i++)
    {
        iResult = dout[m_idx] & mask;

        if(iResult)
            m_btnSet[i]->setIcon(QIcon(":/icon/resource/switch_on.png"));
        else
            m_btnSet[i]->setIcon(QIcon(":/icon/resource/switch_off.png"));

        mask <<= 1;
    }

    for(int i = 0 ; i < 32 ; i++)
    {
        QString temp = m_lblSet[i]->text();
        temp = QString("O%1").arg((i+1)+(m_idx*32));
        m_lblSet[i]->setText(temp);
    }

}

void FormDO::setDO()
{
    CUIApp* probo = CUIApp::getInstance();
    QPushButton* btn = (QPushButton*)sender();

    int index = m_btnSet.indexOf(btn);

    cn_ui32 dout[4] = {0};
    cn_ui32 iResult;
    int sigs;

    probo->getDO(dout, 4);

    iResult = 0x0001 << index;
    iResult = iResult & dout[m_idx];

    if(iResult)
    {
        sigs = -( (index+1) + (m_idx*32));
    }
    else
    {
        sigs = (index+1) + (m_idx*32);
    }


    probo->setDO(&sigs, 1);


}

void FormDO::resetAll_DO()
{

}

void FormDO::on_btnPrev_clicked()
{
    if(m_idx == 0)
        m_idx = 3;
    else
        m_idx -=1;

}

void FormDO::on_btnNext_clicked()
{
    if(m_idx == 3)
        m_idx = 0;
    else
        m_idx += 1;
}

void FormDO::on_btnReset_clicked()
{

}
