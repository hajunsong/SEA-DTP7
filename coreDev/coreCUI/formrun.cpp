#include "formrun.h"
#include "ui_formrun.h"
#include "cnrobo.h"
#include "cnhelper.h"
#include "dlgprogram.h"
#include "dlgnumber.h"
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include <QModelIndex>
#include <QTime>

/* step list color */
static QColor s_crStepFg(0, 0, 0);
static QColor s_crStepBg(255, 255, 255);
static QColor s_crStepPlanBg(192, 255, 192);
/* step line number color */
static QColor s_crStepLineNumberFg(100, 0, 50);
static QColor s_crStepLineNumberBg(240, 240, 240);
static int s_task = 0;


RunStepModel::RunStepModel(QObject *parent) :QAbstractTableModel(parent)
{
    this->m_iconRobot.load(":/icon/resource/robotgeom32.png");
    this->planStep = 0;
    this->motionStep = 0;
}

void RunStepModel::regen()
{
//    steps.clear();
    this->beginResetModel();

    CNRobo* pCon = CNRobo::getInstance();

    QString str;
    str = pCon->getCurProgramName(s_task, true);

    if(str.toInt() < 0)
        return;

    curPrgName = str;
    pCon->getProgramSteps(curPrgName, prog_steps);

    this->endResetModel();
}

void RunStepModel::updateMarkedIndex()
{
   // this->beginResetModel();
    CNRobo* pCon = CNRobo::getInstance();


    int curStep = -1;
    int curStep_R = -1;

    pCon->getRunningStepIndex(s_task, &curStep_R, &curStep);

    emit dataChanged(index(this->planStep, 0), index(this->motionStep, 1));

    this->motionStep = curStep_R - 1;
    this->planStep = curStep - 1;

    emit dataChanged(index(this->planStep, 0), index(this->motionStep, 1));

 //   this->endResetModel();

}


int RunStepModel::rowCount(const QModelIndex &parent) const
{
    return prog_steps.size();
}

int RunStepModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant RunStepModel::data(const QModelIndex &index, int role) const
{
    int row= index.row();
    int col= index.column();
    if(role == Qt::DisplayRole)
    {
        if(col == 0)
            return QString::number(row +1);
        else if(col == 1)
        {
            return prog_steps[row];
        }
    }
    else if(role == Qt::DecorationRole)
    {
        if(col == 0 && row == motionStep)
        {
            if(s_task == 0)
                return m_iconRobot;
        }
    }
    else if(role == Qt::BackgroundRole)
    {
        if(col == 0)
            return s_crStepLineNumberBg;
        else if(col == 1 && row == planStep)
            return s_crStepPlanBg;
        else
            return s_crStepBg;

    }
    else if(role == Qt::TextColorRole)
    {
        if(col == 0)
            return s_crStepLineNumberFg;
        else
            return s_crStepFg;

    }
    else if(role == Qt::TextAlignmentRole)
    {
        if(col == 0)
            return Qt::AlignRight + Qt::AlignVCenter;
    }

    return QVariant();

}


FormRun::FormRun(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormRun)
{
    ui->setupUi(this);

    RunStepModel* pRunStepModel = new RunStepModel();

#if OS_IS_ANDROID
    int colWidth = 150;
#else
    int colWidth = 80;

#endif

    m_timer = new QTimer(this);
    m_timer->setInterval(200);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimer()));

    m_tblRunStepList.append(ui->tblRunSteps);
    m_tblRunStepList.append(ui->tblRunSteps_Sub1);
    m_tblRunStepList.append(ui->tblRunSteps_Sub2);
    m_tblRunStepList.append(ui->tblRunSteps_Sub3);
    m_tblRunStepList.append(ui->tblRunSteps_Sub4);
    m_tblRunStepList.append(ui->tblRunSteps_Sub5);
    m_tblRunStepList.append(ui->tblRunSteps_Sub6);
    m_tblRunStepList.append(ui->tblRunSteps_Sub7);
    m_tblRunStepList.append(ui->tblRunSteps_Sub8);

    int nTable = m_tblRunStepList.size();

    for(int i = 0; i < nTable; i++)
    {
        m_tblRunStepList[i]->setModel(pRunStepModel);
        m_tblRunStepList[i]->setShowGrid(false);
        m_tblRunStepList[i]->horizontalHeader()->setVisible(false);
        m_tblRunStepList[i]->verticalHeader()->setVisible(false);
        m_tblRunStepList[i]->setColumnWidth(0, colWidth);
        m_tblRunStepList[i]->setSelectionMode(QTableView::SingleSelection);
    }

    m_tblRunStepList[0]->setFocus();

    m_inputCycle = -1;
}

FormRun::~FormRun()
{
    delete ui;
}

void FormRun::regenProgramSteps()
{
    CNRobo* pCon = CNRobo::getInstance();

    QString str;
    str = pCon->getCurProgramName(s_task, true);


    ui->txtPrgName->setText(str);

    RunStepModel* pRunStepModel;

    int taskindex = s_task == 0 ? 0 : s_task - 109;

    pRunStepModel = (RunStepModel*)m_tblRunStepList[taskindex]->model();
    pRunStepModel->regen();
    pRunStepModel->updateMarkedIndex();



#if OS_IS_ANDROID
    int nrows = pRunStepModel->rowCount();
    for(int i = 0; i < nrows; i++)
    {
        ui->tblRunSteps->setRowHeight(i, 80);
    }
#endif

}

void FormRun::rergenProgramName()
{
    CNRobo* pCon = CNRobo::getInstance();

    int nTabWid = ui->tbWidget->count();

    int arrIdx[9] = {0, 10, 11, 12, 13, 14, 15, 16, 17};

    for(int i = 0; i < nTabWid; i++)
    {
        ui->tbWidget->setTabText(i, pCon->getCurProgramName(arrIdx[i]));
    }
}

void FormRun::showEvent(QShowEvent *)
{
    m_timer->start();
    regenProgramSteps();
    rergenProgramName();
}

void FormRun::hideEvent(QHideEvent *)
{
    m_timer->stop();
}

void FormRun::onTimer()
{
    CNRobo* pCon = CNRobo::getInstance();
    RunStepModel* model = (RunStepModel*)ui->tblRunSteps->model();

    QString str;
    str = QString("%1 / %2").arg(QString::number(pCon->getProgramRunCount(s_task))).arg(QString::number(pCon->getCurProgramCycle(s_task)));

    int taskindex = s_task == 0 ? 0 : s_task - 109;

    model = (RunStepModel*)m_tblRunStepList[taskindex]->model();
    m_tblRunStepList[taskindex]->scrollTo(model->planIndex());

    if(pCon->isTeach())
    {
        ui->txtStatus->setText("Teach mode");

        if(s_task == 0)
            return;
    }

    int iSpeed = pCon->getOverrideSpeed();

    bool holdDoneStatus = pCon->getHoldDoneStatus();
    CNR_TASK_STATUS taskStatus = pCon->getTaskStatus(s_task);
    QString strStatus;

    if(s_task > 0)
        holdDoneStatus =  true;

    // update status
    if(taskStatus == CNR_TASK_RUNNING)
    {
        strStatus.sprintf("Running, %d%%", iSpeed);
        ui->btnRun->setText("Stop");

        regenProgramSteps();
    }
    else if(taskStatus != CNR_TASK_RUNNING && holdDoneStatus == true)
    {
        ui->btnRun->setText("Run");
        strStatus.sprintf("Stopped, %d%%", iSpeed);
    }



    ui->txtCycle->setText(str);
    ui->txtStatus->setText(strStatus);

}

void FormRun::on_btnCycle_clicked()
{
    DlgNumber dlg;

    CNRobo* pCon = CNRobo::getInstance();

    if(dlg.exec())
    {
        QString cval = dlg.sValue;

        m_inputCycle = cval.toInt();

        pCon->setProgramRunCount(s_task, m_inputCycle);

        ui->txtCycle->setText(cval);

    }

}

void FormRun::on_btnLoad_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();
    int retcode = -1;

    DlgProgram dlg;

    if(dlg.exec())
    {
        QString program = dlg.getSelectedProgram();
        retcode = pCon->setCurProgram(s_task, program);
        if(retcode == 0)
        {
            regenProgramSteps();
            rergenProgramName();
        }
        else
        {
            QMessageBox mBox;
            mBox.setText("Error occured.\nCheck execute condition");
            mBox.exec();
        }
    }
}

void FormRun::on_btnRun_clicked()
{
    CNRobo* pCon = CNRobo::getInstance();


    if(pCon->isTeach() && s_task == 0)
    {
        QMessageBox mBox;
        mBox.setText("Now It's Teach Mode");
        mBox.exec();

        return;
    }
    if((pCon->isMoving() && s_task == 0) || (CNR_TASK_RUNNING == pCon->getTaskStatus(s_task)))
    {
        pCon->holdProgram(s_task);
    }
    else
    {
        if(ui->txtCycle->text().isEmpty())
            m_inputCycle = -1;

        QString Pgname = pCon->getCurProgramName(s_task);
        Pgname = Pgname.trimmed();
        if(Pgname.length() <= 0)  return;

        pCon->executeProgram(s_task, CNHelper::toMultiByteCode(Pgname), m_inputCycle);
    }
}

void FormRun::on_btnSpeed_clicked()
{
    DlgNumber dlg;

    if(dlg.exec())
    {
        QString sval = dlg.sValue;

        int speed = sval.toInt();

        CNRobo* pCon = CNRobo::getInstance();
        pCon->setSpeed(speed);
    }
}

void FormRun::on_btnReset_clicked()
{
    int retcode = 0;
    CNRobo* pCon = CNRobo::getInstance();

    retcode = pCon->resetCurProgram(s_task);

    regenProgramSteps();
}

void FormRun::on_btnSetStep_clicked()
{
    int istep;
    QModelIndex indexmo;

    CNRobo* pCon = CNRobo::getInstance();

    int taskindex = s_task == 0 ? 0 : s_task - 109;

    istep = m_tblRunStepList[taskindex]->currentIndex().row();

    pCon->setCurStep(s_task, istep+1);

    regenProgramSteps();
}

void FormRun::on_btnConProgram_clicked()
{
    int retcode = 0;

    CNRobo* pCon = CNRobo::getInstance();

    retcode = pCon->continueProgram(s_task);
    regenProgramSteps();
}

void FormRun::on_btnStepRun_clicked()
{
    int retcode = 0;

    CNRobo* pCon = CNRobo::getInstance();

    retcode = pCon->runNxtStep(s_task);

    regenProgramSteps();
}

void FormRun::on_btnBstepRun_clicked()
{
    int retcode = 0;

    CNRobo* pCon = CNRobo::getInstance();

    retcode = pCon->runBackStep(s_task);
    regenProgramSteps();
}

void FormRun::on_btnAbortRun_clicked()
{
    int retcode = 0;

    CNRobo* pCon = CNRobo::getInstance();

    retcode = pCon->abortProgram(s_task);
    regenProgramSteps();
}

void FormRun::on_tbWidget_tabBarClicked(int index)
{
    s_task = index == 0 ? 0 : 109 + index;

    regenProgramSteps();
}
