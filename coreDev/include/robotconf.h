#ifndef ROBOTCONF_H
#define ROBOTCONF_H

#include <QStringList>

class RobotConf
{
public:
    RobotConf();

    static void init();

    static int getCurRobotConf(QStringList &list, bool everyParam = false);
    static void setCurRobotConf(QStringList list);

    static int getRobotName(QString &val);
    static void setRobotName(QString val);

    static int getControllerModel(QString &val);
    static void setControllerModel(QString val);

    static int getCycleTime(int &val);
    static void setCycleTime(int val);

    static int getShiftPercent(int &val);
    static void setShiftPercent(int val);

    static int getSpeedRateType(int &val);
    static void setSpeedRateType(int val);

    static int getHoldTimer(float *vals, int &size);
    static void setHoldTimer(float *vals, int size);

    static int getRunTimer(float *vals, int &size);
    static void setRunTimer(float *vals, int size);

    static int getReportILA(bool &val);
    static void setReportILA(bool val);

    static int getMonitorCmdJump(bool &val);
    static void setMonitorCmdJump(bool val);

    static int getMonitorCmdJumpRate(float &val);
    static void setMonitorCmdJumpRate(float val);

    static int getVariableHoldDcc(bool &val);
    static void setVariableHoldDcc(bool val);

    static int getMaxHoldDccTime(float &val);
    static void setMaxHoldDccTime(float val);

    static int getWarningAsError(bool &val);
    static void setWarningAsError(bool val);

    static int getAxisCount(int  &val);
    static void setAxisCount(int  val);

    static int getRobotType(QString &val);
    static void setRobotType(QString val);

    static int getMaxParallelAngle(float &val);
    static void setMaxParallelAngle(float val);

    static int getMinParallelAngle(float &val);
    static void setMinParallelAngle(float val);

    static int getWAccTime(float &val);
    static void setWAccTime(float val);

    static int getWMAccTime(float &val);
    static void setWMAccTime(float val);

    static int getWMinAccuracy(float &val);
    static void setWMinAccuracy(float val);

    static int getTrackOption(bool  &val);
    static void setTrackOption(bool  val);

    static int getECATDevice(QStringList &vals);
    static void setECATDevice(QStringList vals);

    static int getAxisType(int* vals, int &size);
    static void setAxisType(int* vals, int size);

    static int getAxisPPR(int *vals, int &size);
    static void setAxisPPR(int *vals, int size);

    static int getAxisEncBit(int *vals, int &size);
    static void setAxisEncBit(int *vals, int size);

    static int getAxisGear(float *vals, int &size);
    static void setAxisGear(float *vals, int size);

    static int getAxisRPM(int *vals, int &size);
    static void setAxisRPM(int *vals, int size);

    static int getAxisMaxRPM(int *vals, int &size);
    static void setAxisMaxRPM(int *vals, int size);

    static int getAxisLimitP(float *vals, int &size);
    static void setAxisLimitP(float *vals, int size);

    static int getAxisLimitM(float *vals, int &size);
    static void setAxisLimitM(float *vals, int size);

    static int getAxisAccTime(float *vals, int &size);
    static void setAxisAccTime(float *vals, int size);

    static int getAxisMMPU(float *vals, int &size);
    static void setAxisMMPU(float *vals, int size);

    static int getAxisMSpeed(float *vals, int &size);
    static void setAxisMSpeed(float *vals, int size);

    static int getAxisServoOnMode(int *vals, int &size);
    static void setAxisServoOnMode(int *vals, int size);

    static int getAxisMAccTime(float *vals, int &size);
    static void setAxisMAccTime(float *vals, int size);

    static int getWSpeed(float *vals, int &size);
    static void setWSpeed(float *vals, int size);

    static int getWMSpeed(float *vals, int &size);
    static void setWMSpeed(float *vals, int size);

    static int getInchingAccTime(float &val);
    static void setInchingAccTime(float val);

    static int getZeroPosition(int *vals, int &size);
    static void setZeroPosition(int *vals, int size);

    static int getOutProgramCode(bool &val);
    static void setOutProgramCode(bool val);

    static int getSlowRepeatSpeed(int &val);
    static void setSlowRepeatSpeed(int val);

    static int getHSExtEnable(bool &val);
    static void setHSExtEnable(bool val);

    static int getHSEnable(bool &val);
    static void setHSEnable(bool val);

    static int getHSAxis(int *vals, int &size);
    static void setHSAxis(int *vals, int size);

    static int getHSStartOrder(int *vals, int &size);
    static void setHSStartOrder(int *vals, int size);

    static int getHSMethod(int  *vals, int &size);
    static void setHSMethod(int  *vals, int size);

    static int getHSSpeed(float *vals, int &size);
    static void setHSSpeed(float *vals, int size);

    static int getHSSpeedFine(float *vals, int &size);
    static void setHSSpeedFine(float *vals, int size);

    static int getHSAccel(float *vals, int &size);
    static void setHSAccel(float *vals, int size);

    static int getJogJointLabel(QStringList &vals);
    static void setJogJointLabel(QStringList vals);

    static int getJogTransLabel(QStringList &vals);
    static void setJogTransLabel(QStringList vals);

    static int getJogTransAngleType(QString &val);
    static void setJogTransAngleType(QString val);

    static int getJogTransData(QStringList &vals);
    static void setJogTransData(QStringList vals);

    static int getJogTransKey(QStringList &vals);
    static void setJogTransKey(QStringList vals);

    static int getEditingMotionCommand(QString &val);
    static void setEditingMotionCommand(QString val);

    static int getVAEnable(bool &val);
    static void setVAEnable(bool val);

    static int getVACount(int &val);
    static void setVACount(int val);

    static int getVAType(int *vals, int &size);
    static void setVAType(int *vals, int size);

    static int getVASolver(QString &val);
    static void setVASolver(QString val);

    static int getVASpeed(float *vals, int &size);
    static void setVASpeed(float *vals, int size);

    static int getVAAccTime(float *vals, int &size);
    static void setVAAccTime(float *vals, int size);

    static int getVAMSpeed(float *vals, int &size);
    static void setVAMSpeed(float *vals, int size);

    static int getVALimitP(float *vals, int &size);
    static void setVALimitP(float *vals, int size);

    static int getVALimitM(float *vals, int &size);
    static void setVALimitM(float *vals, int size);

    static int getCustomCmd(QString &val);
    static void setCustomCmd(QString val);

    static int getLTControl(bool &val);
    static void setLTControl(bool val);

    static int getUCSize(int &val);
    static void setUCSize(int val);

    static int getUCAngular(int *vals, int &size);
    static void setUCAngular(int *vals, int size);

    static int getUCSpeed(float *vals, int &size);
    static void setUCSpeed(float *vals, int size);

    static int getUCAccTime(float *vals, int &size);
    static void setUCAccTime(float *vals, int size);

    static int getUCMSpeed(float *vals, int &size);
    static void setUCMSpeed(float *vals, int size);

    static int getRobotSolver(QString &val);
    static void setRobotSolver(QString val);

    static int getAxisCofactor(QStringList &vals, bool listFlag = true);
    static void setAxisCofactor(QStringList vals, bool listFlag = true);

    static int getVAParams(QStringList &vals, bool listFlag = true);
    static void setVAParams(QStringList vals, bool listFlag = true);

    static int getCParams(QStringList &vals, bool listFlag = true);
    static void setCParams(QStringList &vals, bool listFlag = true);

    static int getDDCIOList(QStringList &vals, bool listFlag = true);
    static void setDDCIOList(QStringList vals, bool listFlag = true);

    static int getDDCKeyList(QStringList &vals, bool listFlag = true);
    static void setDDCKeyList(QStringList vals, bool listFlag = true);

    static int getLinkParams(QStringList &vals, bool listFlag = true);
    static void setLinkParams(QStringList vals, bool listFlag = true);
};

#endif // ROBOTCONF_H
