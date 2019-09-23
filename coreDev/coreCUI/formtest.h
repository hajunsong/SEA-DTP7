#ifndef FORMTEST_H
#define FORMTEST_H

#include <QWidget>

struct CUIFCTxt
{
    QString name_getbtn;
    QString name_setbtn;
    QString exam_a;
    QString exam_b;
    int findex;
    int hiddenCmd;
};

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

    void appendTxtOut(QStringList lsit);

    static QStringList s_list;


private slots:
    void onTimer();
    void on_btnClean_clicked();
    void on_btnGetLog_clicked();
    void on_btnListPrograms_clicked();
    void on_btnSetSteps_clicked();
    void on_btnLoadProgram_clicked();
    void on_btnDeleteProgram_clicked();
    void on_rbtn_VariableData_clicked();
    void on_rbtn_VariableList_clicked();
    void on_rbtn_VariableCount_clicked();
    void on_rbtn_VariableDelete_clicked();
    void on_rbtn_VarDeleteAll_clicked();
    void on_rbtn_Variables_clicked();
    void on_btn_SetData_pressed();
    void on_btn_GetData_pressed();
    void on_btnGetSDO_clicked();
    void on_btnSetSDO_clicked();
    void on_btnGetSDOList_clicked();
    void on_btnWatchDog_clicked();
    void on_btnMoveToPos_clicked();
    void on_btnGetDateTime_clicked();
    void on_btnSetDateTime_clicked();
    void on_btnSetInchingValue_clicked();
    void on_btnGetInchingValue_clicked();
    void on_btnSetLog_clicked();
    void on_btnSaveVariable_clicked();
    void on_btnGetInchingAValue_clicked();
    void on_btnSetInchingAValue_clicked();
    void on_btn_GetCurProgramStack_clicked();
    void on_btnGetHomePosition_clicked();
    void on_btnSetHomePosition_clicked();
    void on_btnGetSlaveCount_clicked();
    void on_btnGetSlaveType_clicked();
    void on_btnSetEMS_clicked();
    void on_btnGetSlaveModel_clicked();
    void on_btnGetAutoRunSubPrg_clicked();
    void on_btnSetAutoRunSubPrg_clicked();
    void on_btnSaveProgram_clicked();
    void on_btnSaveProgramAll_clicked();
    void on_btnGetProgramAutoSave_clicked();
    void on_btnSetProgramAutoSave_clicked();
    void on_btnGetVariableAutoSave_clicked();
    void on_btnSetVariableAutoSave_clicked();
    void on_btnSetCmdCycleTime_clicked();
    void on_btnGetCmdCycleTime_clicked();
    void on_rbtn_ApplyVarFile_clicked();
    void on_rbtn_ExtractVarFile_clicked();
    void on_btnRebootSystem_clicked();
    void on_btnGetInchingAcc_clicked();
    void on_btnSetInchingAcc_clicked();
    void on_btnCheckMode_clicked();
    void on_btnChechKeyFWD_pressed();
    void on_btnChechKeyFWD_released();
    void on_btnCalcInverse_clicked();
    void on_btnBaseFrame_clicked();
    void on_btnGetVersion2_clicked();
    void on_btnGetTrajectory_clicked();
    void on_btnStartTrajectory_clicked();
    void on_btnStopTrajectory_clicked();

    void on_btnServoOnMode_clicked();

    void on_btn_SetBuzzerOn_clicked();

    void on_btn_setBuzzerOff_clicked();

private:
    Ui::FormTest *ui;

    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

    void setVariableData();
    void getVariableData();
    void getVariableList();
    void getVariableCount();
    void deleteVariable();
    void deleteVariableAll();
    void setVariables();
    void getVariables();
    void applyVariableFile();
    void extractVariableFile();

    void getSDO();

    void SetWidgetHidden(int hdnCmd);
    void setFunctionStruct(CUIFCTxt& cft);
    void setBase();

    int m_functionIndex;
    int m_axisCount;
    bool m_error;
    bool m_warning;
};

#endif // FORMTEST_H
