#include "formprogram.h"
#include "ui_formprogram.h"
#include "cnrobo.h"
#include "dlgprogram.h"
#include "dlgtextinput.h"
#include <QMessageBox>
#include <QDebug>



ProgramStepModel::ProgramStepModel(QObject *parent /* = 0*/) : QAbstractTableModel(parent)
{

}

void ProgramStepModel::regen()
{
    steps.clear();

    this->beginResetModel();

    CNRobo* pCon = CNRobo::getInstance();

    /* get program name and index*/
    //pCon->regenProgramList();
    QString str = pCon->getCurProgramName();

    pCon->getProgramSteps(str, steps);

    this->endResetModel();
}
\
void ProgramStepModel::appendStep(QString str)
{
    this->beginInsertRows(QModelIndex(), rowCount(), rowCount());
    this->steps.append(str);
    this->endInsertRows();
}

void ProgramStepModel::editStep(QString str, int index)
{
    steps[index] = str;
}

int ProgramStepModel::rowCount(const QModelIndex &parent) const
{
    return steps.size();
}
int ProgramStepModel::columnCount(const QModelIndex &parent ) const
{
    /* line # , step data */
    return 1;

}

QVariant ProgramStepModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    if(role == Qt::DisplayRole)
    {
        if(col ==0)
        {           
            return steps[row];

        }

    }

    return QVariant();
}


FormProgram::FormProgram(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormProgram)
{
    ui->setupUi(this);

    ProgramStepModel* pPrgStepModel = new ProgramStepModel();
    ui->tblSteps->setModel(pPrgStepModel);  

}

FormProgram::~FormProgram()
{
    delete ui;
}

void FormProgram::regenProgramSteps()
{

    CNRobo* pCon = CNRobo::getInstance();

    QString str = pCon->getCurProgramName();
    ui->txtCurProgram->setText(str);    

    ProgramStepModel* pPrgStep = (ProgramStepModel*)ui->tblSteps->model();
    pPrgStep->regen();

#if OS_IS_ANDROID
    int nrows = pPrgStep->rowCount();
    for(int i = 0; i < nrows; i++)
    {
        ui->tblSteps->setRowHeight(i, 80);
    }
#endif

}

void FormProgram::showEvent(QShowEvent *)
{
    ui->lstCmdSet->clear();
    QStringList names;
    names <<"MoveJ"<<"MoveL"<< "MoveC"<< "WaitTime"<< "Speed" <<"Accel"<<"Decel" << "Accuracy" << "Delay";

    ui->lstCmdSet->addItems(names);    

}

void FormProgram::on_btnOpenProgram_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();
    int retcode = -1;

    /* regen program list */
    //pCon->regenProgramList();

    DlgProgram dlg;

    if(dlg.exec())
    {
        QString program = dlg.getSelectedProgram();
        retcode         = pCon->setCurProgram(program);
        if(retcode == 0)
        {
            regenProgramSteps();
        }
        else
        {
            QMessageBox mBox;
            mBox.setText("Error occured.\nCheck execute condition");
            mBox.exec();
        }


    }
}

void FormProgram::on_btnInsertProgram_clicked()
{
    DlgTextInput dlg;

    QStringList names;
    names <<"MoveJ"<<"MoveL"<< "MoveC"<< "WaitTime"<< "Speed" <<"Accel"<<"Decel" << "Accuracy" << "Delay";

    int index = -1;
    index = ui->lstCmdSet->currentRow();

    if(index != -1)
    {
        QString str = names[index];
        dlg.str = str;
        dlg.setText();
    }


    if(dlg.exec())
    {
        QString strStep = dlg.str;

        ProgramStepModel* pPrgStepModel = (ProgramStepModel*) ui->tblSteps->model();

        pPrgStepModel->appendStep(strStep);

    }


}

void FormProgram::on_btnSaveProgram_clicked()
{

}

void FormProgram::on_btnEditProgram_clicked()
{

    DlgTextInput dlg;
    ProgramStepModel* pPrgStepModel = (ProgramStepModel*) ui->tblSteps->model();

    QModelIndex midx;
    midx = ui->tblSteps->currentIndex();
    int index = -1;
    index = midx.row();

    if(index != -1)
    {
        dlg.str = pPrgStepModel->steps[index];
        dlg.setText();


        if(dlg.exec())
        {
            QString strStep = dlg.str;

            pPrgStepModel->editStep(strStep, index);
        }
    }
    else
    {
        return;
    }

}
