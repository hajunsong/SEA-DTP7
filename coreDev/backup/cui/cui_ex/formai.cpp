#include "formai.h"
#include "ui_formai.h"
#include <qtimer.h>
#include "cuiapi.h"


FormAI::FormAI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormAI)
{
    ui->setupUi(this);

    for(int i = 0; i < 2; i++)
        ui->tblAin->setColumnWidth(i, 200/2);

    for(int i = 0; i < 8; i++)
        ui->tblAin->setRowHeight(i, 315/8);

    QStringList headerName;
    headerName.append("Index");
    headerName.append("CurVal");
//    headerName.append("MinVal");
//    headerName.append("MaxVal");
//    headerName.append("MinInt");
//    headerName.append("MaxInt");
//    headerName.append("MinSig");
//    headerName.append("MaxSig");

    ui->tblAin->setHorizontalHeaderLabels(headerName);

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    m_idx = 0;
    regen();
}

FormAI::~FormAI()
{
    delete ui;
}


void FormAI::showEvent(QShowEvent *)
{
    m_timer->start(100);
}

void FormAI::hideEvent(QHideEvent *)
{
    m_timer->stop();
}

void FormAI::onTimer()
{
    QTableWidget* tbl = ui->tblAin;
    int iRow = tbl->rowCount();
    QString str;

    float ain[40];
    memset(ain, 0, sizeof(ain));
    CUIApp* pCon = CUIApp::getInstance();
    pCon->getAI(ain, 32);

    for(int i =0; i < iRow; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            QTableWidgetItem* pItem = tbl->item(i, j);
            if(pItem == NULL)
            {
                pItem = new QTableWidgetItem();
                tbl->setItem(i, j, pItem);
            }
            if(j == 0)
            {
                str.sprintf("%d", (m_idx*8)+i+1);
            }
            else
            {
                if(ain[(m_idx*8)+i] == 0)
                    str.sprintf("%3.f", 0.000);
                else
                    str.sprintf("%3.f", ain[(m_idx*8)+i]);

            }
            pItem->setText(str);
        }
    }

}

void FormAI::regen()
{

}

void FormAI::on_btnNext_clicked()
{
    m_idx++;
    if(m_idx > 3)
        m_idx = 3;
}

void FormAI::on_btnPrev_clicked()
{
    m_idx--;
     if(m_idx < 0)
         m_idx = 0;
}
