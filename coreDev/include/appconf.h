#ifndef APPCONF_H
#define APPCONF_H

#include <QStringList>

class AppConf
{
public:
    AppConf();

    static void init();

    static int getCurAppConf(QStringList &list, bool everyParam = false);
    static void setCurAppConf(QStringList list);

    static int getRobotConfigFile(QString &value);
    static void setRobotConfigFile(QString value);

    static int getDryRunMode(bool &value);
    static void setDryRunMode(bool value);

    static int getOverrideSystemInput(bool &value);
    static void setOverrideSystemInput(bool value);

    static int getServoOnSignalMode(int &value);
    static void setServoOnSignalMode(int value);

    static int getLanguage(QString &value);
    static void setLanguage(QString value);

    static int getMainTaskCount(int &value);
    static void setMainTaskCount(int value);

    static int getSubTaskCount(int &value) ;
    static void setSubTaskCount(int value) ;

    static int getUIStyleFile(QString &value) ;
    static void setUIStyleFile(QString value) ;

    static int getConveyorConfFile(QString &value);
    static void setConveyorConfFile(QString value);

    static int getDryRunCounterStep(int &value);
    static void setDryRunCounterStep(int value);

    static int getOverrideCounter(bool &value);
    static void setOverrideCounter(bool value);

    static int getOverrideCounterSpeed(float &value);
    static void setOverrideCounterSpeed(float value);

    static int getDebugFlag(bool &value);
    static void setDebugFlag(bool value);

    static int getDebugInfo(int &value);
    static void setDebugInfo(int value);

    static int getDebugPrintBit(int &value);
    static void setDebugPrintBit(int value);

    static int getEnableConfigInstruction(bool &value);
    static void setEnableConfigInstruction(bool value);

    static int getPrefetchDO(bool &value);
    static void setPrefetchDO(bool value);

    static int getLogo(QString &value);
    static void setLogo(QString value);

    static int getMainTaskPlannerPriority(int &value);
    static void setMainTaskPlannerPriority(int value);

    static int getSubTaskPriority(int &value);
    static void setSubTaskPriority(int value);

    static int getMainTaskSleepTime(int &value);
    static void setMainTaskSleepTime(int value);

    static int getSubTaskSleepTime(int &value);
    static void setSubTaskSleepTime(int value);

    static int getAutoSaveDataFlag(bool &value);
    static void setAutoSaveDataFlag(bool value);

    static int getPluginFile(QString &value);
    static void setPluginFile(QString value);

    static int getEMStopMode(int &value);
    static void setEMStopMode(int value);

    static int getEMStopAccTime(float &value);
    static void setEMStopAccTime(float value);

    static int getStepBackFlag(bool &value);
    static void setStepBackFlag(bool value);

    static int getStepOverFlag(bool &value);
    static void setStepOverFlag(bool value);

    static int getInstFile(QString &value);
    static void setInstFile(QString value);

    static int getTeachSingularFlag(bool &value);
    static void setTeachSingularFlag(bool value);

    static int getTeachSingularSpeedLimit(float &value);
    static void setTeachSingularSpeedLimit(float value);

    static int getRepeatSingularFlag(bool &value);
    static void setRepeatSingularFlag(bool value);

    static int getRepeatSingularSpeedLimit(float &value);
    static void setRepeatSingularSpeedLimit(float value);

    static int getMaxLogSize(int &value);
    static void setMaxLogSize(int value);

    static int getRemoveLogRatio(int &value);
    static void setRemoveLogRatio(int value);

    static int getRecordingFlag(bool &value);
    static void setRecordingFlag(bool value);

    static int getRecAutoRun(QString &name, int &status);
    static void setRecAutoRun(QString name, int status);

    static int getDomainCount(int &value);
    static void setDomainCount(int value);

    static int getWCErrorDelayCount(int &value);
    static void setWCErrorDelayCount(int value);

    static int getResetALState(int &value);
    static void setResetALState(int value);

    static int getPrintLevel(int &value);
    static void setPrintLevel(int value);

    static int getRemoteScreenFlag(bool &value);
    static void setRemoteScreenFlag(bool value);

    static int getRemoteServerPort(int &value);
    static void setRemoteServerPort(int value);

    static int getConfChecksumErrorSkipFlag(bool &value);
    static void setConfChecksumErrorSkipFlag(bool value);

    static int getTaskProgramAutoLoadingFlag(bool &value);
    static void setTaskProgramAutoLoadingFlag(bool value);

    static int getProgIndentationSize(int &value);
    static void setProgIndentationSize(int value);

    static int getCollaborativeRobot(bool &value);
    static void setCollaborativeRobot(bool value);

    static int getLinkErrorStopFlag(bool &value);
    static void setLinkErrorStopFlag(bool value);

    static int getMasterLinkErrorDelay(float &value);
    static void setMasterLinkErrorDelay(float value);

    static int getRS485master(bool &value);
    static void setRS485master(bool value);

    static int getMemLogFile(QString &value);
    static void setMemLogFile(QString value);

    static int getMemLogFlag(bool &value);
    static void setMemLogFlag(bool value);

};
#endif // APPCONF_H
