#ifndef FORMTEST_H
#define FORMTEST_H

#include <QWidget>


namespace Ui {
class FormTest;
}

class FormTest : public QWidget
{
    Q_OBJECT

public:
    explicit FormTest(QWidget *parent = 0);
    ~FormTest();

    QTimer* m_timer;

    static FormTest* m_pInstance;
    static FormTest* getInstance();

    void appendTxtOut(QStringList list);

    static QStringList s_list;

private slots:
    void onTimer();
    void on_btnClean_clicked();

    void on_btnGetLog_clicked();
    void on_btnMoveToPos_clicked();
    void on_btnGetDateTime_clicked();
    void on_btnSetDateTime_clicked();
    void on_btnSetLog_clicked();
    void on_btn_GetCurProgramStack_clicked();
    void on_btnGetSlaveCount_clicked();
    void on_btnGetSlaveType_clicked();
    void on_btnSetEMS_clicked();
    void on_btnGetSlaveModel_clicked();
    void on_btnGetAutoRunSubPrg_clicked();
    void on_btnSetAutoRunSubPrg_clicked();
    void on_btnRebootSystem_clicked();
    void on_btnCalcInverse_clicked();
    void on_btnSetAutoRunSubPrg_2_clicked();
    void on_btnEcatStats_clicked();
    void on_btnVersion_clicked();
    void on_btnMultiData_clicked();

private:
    Ui::FormTest *ui;

    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    void regenMessage();

    void setBase();

    int m_axisCount;
    bool m_error;
};

#endif // FORMTEST_H
