#include "formao.h"
#include "ui_formao.h"
#include "cnrobo.h"
#include <qtimer.h>
#include "dlgnumber.h"

FormAO::FormAO(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormAO)
{
    ui->setupUi(this);

    for(int i = 0; i < 2; i++)
        ui->tblAout->setColumnWidth(i, 200/2);

    for(int i = 0; i < 8; i++)
        ui->tblAout->setRowHeight(i, 315/8);

    QStringList headerName;
    headerName.append("Index");
    headerName.append("CurVal");
//    headerName.append("MinVal");
//    headerName.append("MaxVal");
//    headerName.append("MinInt");
//    headerName.append("MaxInt");
//    headerName.append("MinSig");
//    headerName.append("MaxSig");

    ui->tblAout->setHorizontalHeaderLabels(headerName);

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    m_idx = 0;
    regen();
}

FormAO::~FormAO()
{
    delete ui;
}

void FormAO::showEvent(QShowEvent *)
{
    m_timer->start(100);
}

void FormAO::hideEvent(QHideEvent *)
{
    m_timer->stop();
}

void FormAO::onTimer()
{
    QTableWidget* tbl = ui->tblAout;
    int iRow = tbl->rowCount();
    QString str;

    float aout[40];
    memset(aout, 0, sizeof(aout));
    CNRobo* pCon = CNRobo::getInstance();
    pCon->getAO(aout, 32);

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
                if(aout[(m_idx*8)+i] == 0)
                    str.sprintf("%3.f", 0.000);
                else
                    str.sprintf("%3.f", aout[(m_idx*8)+i]);

            }
            pItem->setText(str);
        }
    }

}

void FormAO::regen()
{

}

void FormAO::on_btnNext_clicked()
{
    m_idx++;
    if(m_idx > 3)
        m_idx = 3;
}

void FormAO::on_btnPrev_clicked()
{
    m_idx--;
     if(m_idx < 0)
         m_idx = 0;
}

void FormAO::on_btnSetAO_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();

    int idx = ui->tblAout->currentRow();
    DlgNumber dlg;
    if(!dlg.exec()) return;

    if(dlg.fValue < 0 || 10 < dlg.fValue)
    {
        return;
    }

    pCon->setAO((m_idx*8)+idx, dlg.fValue);
}
