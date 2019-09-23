#include "formrun.h"
#include "ui_formrun.h"
#include "cuiapi.h"
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

    CUIApp* pCon = CUIApp::getInstance();

    QStringList prgStacks;
    pCon->getCurProgramStack(s_task, prgStacks);

    QString str;

    if(prgStacks.isEmpty())
        str = pCon->getCurProgramName(s_task);
    else if(prgStacks.count() > 0)
        str = prgStacks[prgStacks.count()-1];

    if(str.toInt() < 0)
        return;

    curPrgName = str;

    if(s_task == 0)
        pCon->getProgramSteps(curPrgName, main_steps);
    else
        pCon->getProgramSteps(curPrgName, sub_steps);

    this->endResetModel();
}

void RunStepModel::updateMarkedIndex()
{
   // this->beginResetModel();
    CUIApp* pCon = CUIApp::getInstance();


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
    return s_task == 0 ? main_steps.size() : sub_steps.size();
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
            return s_task == 0 ? main_steps[row] : sub_steps[row];
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

    ui->tblRunSteps->setModel(pRunStepModel);
    ui->tblRunSteps->setShowGrid(false);
    ui->tblRunSteps->horizontalHeader()->setVisible(false);
    ui->tblRunSteps->verticalHeader()->setVisible(false);
    ui->tblRunSteps->setColumnWidth(0, colWidth);
    ui->tblRunSteps->setSelectionMode(QTableView::SingleSelection);


    ui->tblRunSteps_Sub->setModel(pRunStepModel);
    ui->tblRunSteps_Sub->setShowGrid(false);
    ui->tblRunSteps_Sub->horizontalHeader()->setVisible(false);
    ui->tblRunSteps_Sub->verticalHeader()->setVisible(false);
    ui->tblRunSteps_Sub->setColumnWidth(0, colWidth);
    ui->tblRunSteps_Sub->setSelectionMode(QTableView::SingleSelection);

}

FormRun::~FormRun()
{
    delete ui;
}
void FormRun::regenProgramSteps()
{
    CUIApp* pCon = CUIApp::getInstance();

    QStringList prgStacks;
    pCon->getCurProgramStack(s_task, prgStacks);

    QString str;

    if(prgStacks.isEmpty())
        str = pCon->getCurProgramName(s_task);
    else if(prgStacks.count() > 0)
        str = prgStacks[prgStacks.count()-1];

    ui->txtPrgName->setText(str);

    RunStepModel* pRunStepModel = s_task == 0 ? (RunStepModel*)ui->tblRunSteps->model() : (RunStepModel*)ui->tblRunSteps_Sub->model();
    pRunStepModel->regen();
    pRunStepModel->updateMarkedIndex();
}

void FormRun::showEvent(QShowEvent *)
{
    m_timer->start();
    regenProgramSteps();
}

void FormRun::hideEvent(QHideEvent *)
{
    m_timer->stop();
}

void FormRun::onTimer()
{
    CUIApp* pCon = CUIApp::getInstance();
    RunStepModel* model = (RunStepModel*)ui->tblRunSteps->model();
    RunStepModel* model_sub = (RunStepModel*)ui->tblRunSteps_Sub->model();
    QString str;
    str = QString("%1 / %2").arg(QString::number(pCon->getProgramRunCount(s_task))).arg(QString::number(pCon->getCurProgramCycle(s_task)));

    if(s_task == 0)
        ui->tblRunSteps->scrollTo(model->planIndex());
    else if(s_task == 1)
        ui->tblRunSteps_Sub->scrollTo(model_sub->planIndex());

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

    if(s_task == 1)
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
    else
    {
        regenProgramSteps();
    }
    ui->txtCycle->setText(str);
    ui->txtStatus->setText(strStatus);

}


void FormRun::on_btnCycle_clicked()
{
    DlgNumber dlg;

    CUIApp* pCon = CUIApp::getInstance();

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
    CUIApp* pCon = CUIApp::getInstance();
    int retcode = -1;

    DlgProgram dlg;

    if(dlg.exec())
    {
        QString program = dlg.getSelectedProgram();
        retcode = pCon->setCurProgram(s_task, program);
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

void FormRun::on_btnRun_clicked()
{
    CUIApp* pCon = CUIApp::getInstance();


    if(pCon->isTeach() && s_task == 0) return;

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

        pCon->executeProgram(s_task, Pgname, m_inputCycle);
    }
}

void FormRun::on_btnSpeed_clicked()
{
    DlgNumber dlg;

    if(dlg.exec())
    {
        QString sval = dlg.sValue;

        int speed = sval.toInt();

        CUIApp* pCon = CUIApp::getInstance();
        pCon->setSpeed(speed);
    }
}

void FormRun::on_btnReset_clicked()
{
    int retcode = 0;
    CUIApp* pCon = CUIApp::getInstance();

    retcode = pCon->resetCurProgram(s_task);

    regenProgramSteps();
}

void FormRun::on_btnSetStep_clicked()
{
    int retcode = 0;
    int istep;
    QModelIndex indexmo;

    CUIApp* pCon = CUIApp::getInstance();
    istep = s_task == 0 ? ui->tblRunSteps->currentIndex().row() : ui->tblRunSteps_Sub->currentIndex().row();

    pCon->setCurStep(s_task, istep+1);

    regenProgramSteps();
}

void FormRun::on_btnConProgram_clicked()
{
    int retcode = 0;

    CUIApp* pCon = CUIApp::getInstance();

    retcode = pCon->continueProgram(s_task);
    regenProgramSteps();
}

void FormRun::on_btnStepRun_clicked()
{
    int retcode = 0;

    CUIApp* pCon = CUIApp::getInstance();

    retcode = pCon->runNxtStep(s_task);

    regenProgramSteps();
}

void FormRun::on_btnStepRunO_clicked()
{
    int retcode = 0;

    CUIApp* pCon = CUIApp::getInstance();

    retcode = pCon->runNxtStepOver(s_task);

    regenProgramSteps();
}

void FormRun::on_btnBstepRun_clicked()
{
    int retcode = 0;

    CUIApp* pCon = CUIApp::getInstance();

    retcode = pCon->runBackStep(s_task);
    regenProgramSteps();
}

void FormRun::on_btnBstepRunO_clicked()
{
    int retcode = 0;

    CUIApp* pCon = CUIApp::getInstance();

    retcode = pCon->runBackStepOver(s_task);
    regenProgramSteps();
}

void FormRun::on_btnAbortRun_clicked()
{
    int retcode = 0;

    CUIApp* pCon = CUIApp::getInstance();

    retcode = pCon->abortProgram(s_task);
    regenProgramSteps();
}


void FormRun::on_tabWidget_currentChanged(int index)
{
    s_task = index;

    regenProgramSteps();
}
