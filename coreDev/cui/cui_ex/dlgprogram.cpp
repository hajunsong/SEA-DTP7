#include "dlgprogram.h"
#include "ui_dlgprogram.h"

#include "cuiapi.h"


DlgProgram::DlgProgram(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgProgram)
{
    ui->setupUi(this);


    /* load program list */
    CUIApp* pCon = CUIApp::getInstance();

    QStringList programs;

    pCon->getPrograms(programs);

    for(int i = 0; i < programs.size(); i++)
    {
        ui->programList->addItem(programs[i]);
    }
}

DlgProgram::~DlgProgram()
{
    delete ui;
}

void DlgProgram::on_btnOK_clicked()
{

    QListWidgetItem* pItem = ui->programList->currentItem();
    if(pItem)
        m_selectedProgram = pItem->text();

    QDialog::accept();
}

void DlgProgram::on_btnCancel_clicked()
{
    QDialog::reject();
}

void DlgProgram::on_programList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(current)
    {
        m_selectedProgram = current->text();
        ui->txtProgram->setText(m_selectedProgram);
    }
}
