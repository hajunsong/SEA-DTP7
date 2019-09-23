#include "formdata.h"
#include "ui_formdata.h"

#include "cuiapi.h"
#include "dlgnumber.h"


#define NAME_WIDTH      60
#define COLUMN_WIDTH    90

FormData::FormData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormData)
{
    ui->setupUi(this);
    int nAxis = 6;

    /* setting joint table */
    m_jointLabels.append(tr("Name"));
    for(int i = 0; i < nAxis; i++)
    {
        QString str = QString("J%1").arg(i+1);

        m_jointLabels.append(str);
    }


    QTableWidget* tbl = ui->tblJoint;
    tbl->setColumnCount(nAxis +1);
    tbl->setHorizontalHeaderLabels(m_jointLabels);
    tbl->setSortingEnabled(false);

    for(int i = 0; i < m_jointLabels.size(); i++)
    {
        tbl->setColumnWidth(i, COLUMN_WIDTH);
    }

    if(m_jointLabels.size() <=7)
    {
        tbl->horizontalHeader()->setStretchLastSection(true);

    }

    /*setting trans table */
    m_transLabels.append("Name");

    if(nAxis >= 1)
        m_transLabels.append("X");
    if(nAxis >= 2)
        m_transLabels.append("Y");
    if(nAxis >= 3)
        m_transLabels.append("Z");
    if(nAxis >= 4)
        m_transLabels.append("A");
    if(nAxis >= 5)
        m_transLabels.append("B");
    if(nAxis >= 6)
        m_transLabels.append("C");
    if(nAxis >= 7)
    {
        for(int i = 7; i <= nAxis; i++)
        {
            m_transLabels.append(QString("Ex%1").arg(i-6));
        }
    }

    tbl = ui->tblTrans;
    tbl->setColumnCount(nAxis +1);
    tbl->setHorizontalHeaderLabels(m_transLabels);
    tbl->setSortingEnabled(false);

    for(int i = 0 ; i < m_transLabels.size(); i++)
    {
        tbl->setColumnWidth(i, COLUMN_WIDTH);
    }
    if(m_transLabels.size() <=7)
    {
        tbl->horizontalHeader()->setStretchLastSection(true);
    }

    /* setting number table */
    m_numberLabels.append("Name");
    m_numberLabels.append("Value");

    tbl = ui->tblNumber;
    tbl->setColumnCount(2);
    tbl->setHorizontalHeaderLabels(m_numberLabels);
    tbl->setColumnWidth(0, 200);
    tbl->horizontalHeader()->setStretchLastSection(true);
    tbl->setSortingEnabled(false);

    /* setting string table */

    tbl = ui->tblString;
    tbl->setColumnCount(2);
    tbl->setColumnWidth(0,200);
    tbl->horizontalHeader()->setStretchLastSection(true);
    tbl->setSortingEnabled(false);


    ui->tblJoint->setAlternatingRowColors(true);
    ui->tblTrans->setAlternatingRowColors(true);
    ui->tblNumber->setAlternatingRowColors(true);
    ui->tblString->setAlternatingRowColors(true);

}

FormData::~FormData()
{
    delete ui;
}


void FormData::showEvent(QShowEvent *evt)
{
    regenJoint();
    regenTrans();
    regenNumber();
    regenString();
}

void FormData::regenJoint()
{
    QStringList varnames;
    QTableWidget* ptbl = ui->tblJoint;
    ptbl->clearContents();

    CUIApp* pCon = CUIApp::getInstance();

    QString str;
    QVector<cn_variant> vardatas;

    pCon->getVariableList(1, varnames, vardatas);

    int nvar = varnames.count();
    ptbl->setRowCount(nvar);

    for(int i = 0 ; i < nvar ; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            QTableWidgetItem *pCell = ptbl->item(i, j);
            if(!pCell){
                pCell = new QTableWidgetItem(" ");
                ptbl->setItem(i, j, pCell);
            }
        }

        ptbl->item(i,0)->setText(varnames[i]);

        str.sprintf("%.3f", vardatas[i].val.joint.joint[0]);
        ptbl->item(i,1)->setText(str);
        str.sprintf("%.3f", vardatas[i].val.joint.joint[1]);
        ptbl->item(i,2)->setText(str);
        str.sprintf("%.3f", vardatas[i].val.joint.joint[2]);
        ptbl->item(i,3)->setText(str);
        str.sprintf("%.3f", vardatas[i].val.joint.joint[3]);
        ptbl->item(i,4)->setText(str);
        str.sprintf("%.3f", vardatas[i].val.joint.joint[4]);
        ptbl->item(i,5)->setText(str);
        str.sprintf("%.3f", vardatas[i].val.joint.joint[5]);
        ptbl->item(i,6)->setText(str);

    }

}

void FormData::regenTrans()
{
    QStringList varnames;
    QTableWidget* ptbl = ui->tblTrans;
    ptbl->clearContents();

    CUIApp* pCon = CUIApp::getInstance();

    QString str;
    QVector<cn_variant> vardatas;

    pCon->getVariableList(2, varnames, vardatas);

    int nvar = varnames.count();
    ptbl->setRowCount(nvar);

    for(int i = 0 ; i < nvar ; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            QTableWidgetItem *pCell = ptbl->item(i, j);
            if(!pCell)
            {
                pCell = new QTableWidgetItem(" ");
                ptbl->setItem(i, j, pCell);
            }
        }

        ptbl->item(i,0)->setText(varnames[i]);

        str.sprintf("%.3f", vardatas[i].val.trans.p[0]);
        ptbl->item(i,1)->setText(str);
        str.sprintf("%.3f", vardatas[i].val.trans.p[1]);
        ptbl->item(i,2)->setText(str);
        str.sprintf("%.3f", vardatas[i].val.trans.p[2]);
        ptbl->item(i,3)->setText(str);
        str.sprintf("%.3f", vardatas[i].val.trans.eu[0]);
        ptbl->item(i,4)->setText(str);
        str.sprintf("%.3f", vardatas[i].val.trans.eu[1]);
        ptbl->item(i,5)->setText(str);
        str.sprintf("%.3f", vardatas[i].val.trans.eu[2]);
        ptbl->item(i,6)->setText(str);
    }
}

void FormData::regenNumber()
{
    QStringList varnames;
    QTableWidget* ptbl = ui->tblNumber;
    ptbl->clearContents();

    CUIApp* pCon = CUIApp::getInstance();

    //cn_variant var;
    QString str;
    QVector<cn_variant> vardatas;

    pCon->getVariableList(3, varnames, vardatas);

    int nvar = varnames.count();
    ptbl->setRowCount(nvar);

    for(int i = 0 ; i < nvar ; i ++)
    {
        //pCon->getVariableData(3, varnames[i], &var);

        for(int j = 0 ; j < 2 ; j++)
        {
            QTableWidgetItem *pCell = ptbl->item(i,j);
            if(!pCell)
            {
                pCell = new QTableWidgetItem("");
                ptbl->setItem(i, j ,pCell);
            }
        }

        ptbl->item(i,0)->setText(varnames[i]);

        str.sprintf("%.3f", vardatas[i].val.f32);
        ptbl->item(i,1)->setText(str);
    }
}

void FormData::regenString()
{
    QStringList varnames;
    QTableWidget* ptbl = ui->tblString;
    ptbl->clearContents();

    CUIApp* pCon = CUIApp::getInstance();

    //cn_variant var;
    QString str;
    QVector<cn_variant> vardatas;

    pCon->getVariableList(4, varnames, vardatas);

    int nvar = varnames.count();

    ptbl->setRowCount(nvar);

    for(int i = 0 ; i < nvar ; i++)
    {
        //pCon->getVariableData(4, varnames[i], &var);

        for(int j = 0 ; j < 2 ; j++)
        {
            QTableWidgetItem* pCell = ptbl->item(i,j);
            if(!pCell)
            {
                pCell = new QTableWidgetItem("");
                ptbl->setItem(i, j, pCell);
            }
        }

        ptbl->item(i,0)->setText(varnames[i]);

        str.sprintf("%s", vardatas[i].val.str);
        ptbl->item(i,1)->setText(str);
    }


}

void FormData::updateJointItem(int index)
{
    CUIApp* pCon = CUIApp::getInstance();
    cn_variant var;

    QTableWidget* ptbl = ui->tblJoint;
    QTableWidgetItem* pItem = ptbl->item(index, 0);
    if(pItem == NULL) return;

    QString strName = pItem->text();
    pCon->getVariableData(1, strName, &var);  //?? check

    for(int j = 0 ; j < 7 ; j++)
    {
        QTableWidgetItem *pCell = ptbl->item(index, j);
        if(!pCell)
        {
            pCell = new QTableWidgetItem("");
            ptbl->setItem(index, j, pCell);
        }
    }

    QString str;
    ptbl->item(index, 0)->setText(strName);
    str.sprintf("%.3f", var.val.joint.joint[0]);
    ptbl->item(index, 1)->setText(str);
    str.sprintf("%.3f", var.val.joint.joint[1]);
    ptbl->item(index, 2)->setText(str);
    str.sprintf("%.3f", var.val.joint.joint[2]);
    ptbl->item(index, 3)->setText(str);
    str.sprintf("%.3f", var.val.joint.joint[3]);
    ptbl->item(index, 4)->setText(str);
    str.sprintf("%.3f", var.val.joint.joint[4]);
    ptbl->item(index, 5)->setText(str);
    str.sprintf("%.3f", var.val.joint.joint[5]);
    ptbl->item(index, 6)->setText(str);

}

void FormData::updateTransItem(int index)
{
    CUIApp* pCon = CUIApp::getInstance();
    cn_variant var;

    QTableWidget* ptbl = ui->tblTrans;
    QTableWidgetItem* pItem = ptbl->item(index, 0);
    if(pItem == NULL) return;

    QString strName = pItem->text();
    pCon->getVariableData(2, strName, &var);

    for(int j = 0 ; j < 7 ; j++)
    {
        QTableWidgetItem *pCell = ptbl->item(index, j);
        if(!pCell)
        {
            pCell = new QTableWidgetItem("");
            ptbl->setItem(index, j, pCell);
        }
    }

    QString str;
    ptbl->item(index, 0)->setText(strName);
    str.sprintf("%.3f", var.val.trans.p[0]);
    ptbl->item(index, 1)->setText(str);
    str.sprintf("%.3f", var.val.trans.p[1]);
    ptbl->item(index, 2)->setText(str);
    str.sprintf("%.3f", var.val.trans.p[2]);
    ptbl->item(index, 3)->setText(str);
    str.sprintf("%.3f", var.val.trans.eu[0]);
    ptbl->item(index, 4)->setText(str);
    str.sprintf("%.3f", var.val.trans.eu[1]);
    ptbl->item(index, 5)->setText(str);
    str.sprintf("%.3f", var.val.trans.eu[2]);
    ptbl->item(index, 6)->setText(str);

}

void FormData::teachVarJoint()
{
    CUIApp* pCon = CUIApp::getInstance();
    if( !pCon->isTeach()) return;

    QTableWidget* ptbl = ui->tblJoint;

    int index = ptbl->currentRow();

    if(index < 0)
    {
        // show message " no selected item"
        return;
    }

    QTableWidgetItem* pItem = ptbl->item(index, 0);
    QString strPoint = pItem->text();

    // set cur position

    updateJointItem(index);
}

void FormData::on_btnEdit_clicked()
{
    CUIApp* pCon = CUIApp::getInstance();

    int rowidx = ui->tblNumber->currentRow();
    cn_variant newvalue;
    DlgNumber dlg;

    if(dlg.exec())
    {
        QString valuename = ui->tblNumber->item(rowidx, 0)->text();
        newvalue.val.f32 = dlg.fValue;

        pCon->setVariableData(3, valuename, newvalue, true);

    }
    else
    {
        return;
    }

    regenNumber();

}
