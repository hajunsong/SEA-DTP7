#ifndef FORMRUN_H
#define FORMRUN_H

#include <QWidget>
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QTime>

namespace Ui {
class FormRun;
}


class RunStepModel : public QAbstractTableModel
{
    Q_OBJECT

    QPixmap m_iconRobot;

public:
    RunStepModel(QObject *parent = 0);

    QString curPrgName;
    QStringList main_steps;
    QStringList sub_steps;

    int planStep;
    int motionStep;

    QModelIndex planIndex()
    {
        if(planStep < 0) return QModelIndex();

        return index(planStep, 0);
    }

    void regen();
    void updateMarkedIndex();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
};


class FormRun : public QWidget
{
    Q_OBJECT

    QTimer* m_timer;

public:
    explicit FormRun(QWidget *parent = 0);
    ~FormRun();


protected:
    void regenProgramSteps();
    void showEvent(QShowEvent*);
    void hideEvent(QHideEvent*);

private slots:
    void onTimer();
    void on_btnCycle_clicked();
    void on_btnLoad_clicked();
    void on_btnRun_clicked();
    void on_btnSpeed_clicked();
    void on_btnReset_clicked();
    void on_btnSetStep_clicked();
    void on_btnConProgram_clicked();
    void on_btnStepRun_clicked();
    void on_btnStepRunO_clicked();
    void on_btnBstepRun_clicked();
    void on_btnBstepRunO_clicked();
    void on_btnAbortRun_clicked();


    void on_tabWidget_currentChanged(int index);

private:
    Ui::FormRun *ui;

    float m_inputCycleTime;
    int   m_inputCycle;
    int   m_programCurCylcle;

    QString m_str;

};

#endif // FORMRUN_H
