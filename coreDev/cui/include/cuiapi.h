#ifndef DEF_CUIAPI_H
#define DEF_CUIAPI_H	1



#include <QObject>
#include <QStringList>
#include <QTimer>
#include "cntype.h"

/**
 * @brief The MECH_TYPE enum
 *   manipulator configuration
 *      parameters for seiral6, parallel6, sparallel6 :
 *          V1, V2, V3, H1, H2, H3(=Tool Offset from Wrist Center)
 *      parameters for scara : V1, V2(Tool Offset), H1, H2
 */
enum CNR_MECH_TYPE
{
    CNR_MECH_SERIAL6    = 0,       // parameter list : dimension[5]
    CNR_MECH_PARALLEL6  = 1,       // ABB IRB-6000 type : parameter list : dimension[6]
    CNR_MECH_SPARALLEL6 = 2,       // KAWASAKI UX120 type : parameter list : dimension[6]
    CNR_MECH_CARTESIAN  = 3,       // Cartesian robot : parameter list :
    CNR_MECH_SCARA      = 4,       // parameter list : dimension[4]
    CNR_MECH_DELTA      = 5,       // delta 4 axis : rotation
    CNR_MECH_DELTA3     = 6,       // delta 3 axis : no rotation
    CNR_MECH_UR6        = 7,       // universal robot
    CNR_MECH_PALLET     = 8,       // palletizing robot
    CNR_MECH_PALLET_L     = 9,     // palletizing robot
    CNR_MECH_CUSTOM     = 0xFF,    // custom robot : cartesian coordinate or user coordinate
};


enum CNR_TEACH_COORDINATE
{
    CNR_TC_JOINT,
    CNR_TC_BASE,
    CNR_TC_TOOL,
    CNR_TC_USER
};

enum CNR_TEACH_SPEED
{
    CNR_TS_LOW,
    CNR_TS_MID,
    CNR_TS_HIGH
};

/* Dedicated Signal Name */
enum CNR_DDC_SIGNAL
{
    /* output : 1 ~ */
    CNR_DDCO_MOTOR_ON = 1,          // Motor is on (Servo is On )
    CNR_DDCO_ERROR,                 // System is on error
    CNR_DDCO_TEACH,                 // Current mode is teach
    CNR_DDCO_REPEAT,                // Current mode is repeat
    CNR_DDCO_CHECK,                 // Current mode is check
    CNR_DDCO_REMOTE,                // Current mode is remote
    CNR_DDCO_HOME,                  // Robot is in home pos
    CNR_DDCO_HOME2,                 // Robot is in home 2pos
    CNR_DDCO_RUN1,                  // Main task is running
    CNR_DDCO_RUN2,                  // Sub task is running
    CNR_DDCO_HIGH_SPEED,            // high speed status : one of axes over specified RPM
    CNR_DDCO_SYSTEM_READY,          // ecat op state
    CNR_DDCO_SERVO_ERROR,           // ecat servo driver is on error

    CNR_DDCO_EPS_MODE,              // External Program Select Mode is Enabled or not
    CNR_DDCO_EPS_STATUS,            // if on : EXT_EPS_ON / OFF is applied

    /* input : 1001 ~ */
    CNR_DDCI_SELECT1 = 1001 ,       //  0 , 0 : repeat      0/1 or 1/0 : remote
    CNR_DDCI_SELECT2,               //  1 , 1 : teach
    CNR_DDCI_MOTOR_POWER_ON,        // motor power on switch
    CNR_DDCI_MOTOR_POWER_STATE,     // motor power state
    CNR_DDCI_SAFETY_ERROR,          // external error signal to need servo off
    CNR_DDCI_ACFAIL,                // ac fail
    CNR_DDCI_EMSTOP,                // emstop switch
    CNR_DDCI_ERESET,                // erreset switch
    CNR_DDCI_TPENABLE,              // tp trigger switch
    CNR_DDCI_HOLD,                  // hold/run switch

    CNR_DDCI_PROGRAM_START,         // external program start :
    CNR_DDCI_PROGRAM_RESET,         // external program reset :

    CNR_DDCI_EPS_ON,                // external program select on
    CNR_DDCI_EPS_OFF,               // external program select off (cancel)
    CNR_DDCI_EPS_START_BIT,         // external program select start io#
    CNR_DDCI_EPS_END_BIT,           // external program select end io#
};

enum CNR_HOME_STATUS
{
    CNR_HOME_ERROR = -1,
    CNR_HOME_READY = 0,
    CNR_HOME_SERCHING = 1,
    CNR_HOME_FOUNDED = 2
};

enum CNR_TASK_STATUS
{
    CNR_TASK_NOTUSED = 0,
    CNR_TASK_RUNNING = 1,
    CNR_TASK_STOPPED = 2,
};

enum CNR_TP_MSG_STATUS
{
    CNR_TP_MSG_CLEAR = -1,
    CNR_TP_MSG_ERROR = 0,
    CNR_TP_MSG_WARNING,
    CNR_TP_MSG_INFO,
};

enum CNR_LED
{
    // tp led
    CNR_LED_L1,
    CNR_LED_L2,
    CNR_LED_L3,
    CNR_LED_R1,
    CNR_LED_R2,
    CNR_LED_R3,

    // dmc led
    CNR_LED_SYS_RUN,
    CNR_LED_SYS_ERR,

    // io
    CNR_LED_IO_RUN = 1000,  // led id = ETC_LED_IO_RUN + board index (0, 1, 2, 3 ...

    CNR_LED_IO_ERR = 2000   // led id = ETC_LED_IO_ERR + board index (0, 1, 2, 3, ....
};

// led definition
//
enum CNR_LED_COLOR
{
    CNR_LED_COLOR_OFF       = 0x0,
    CNR_LED_COLOR_RED       = 0x1,
    CNR_LED_COLOR_BLUE      = 0x2,
    CNR_LED_COLOR_MAGENTA   = 0x3,    // red + blue
    CNR_LED_COLOR_ON        = 0x3,    // all on
};

typedef enum
{
    CNR_SLAVE_DRIVER    = 1,   // motor driver
    CNR_SLAVE_DIN       = 2,   // digital output
    CNR_SLAVE_DOUT      = 4,   // digital input
    CNR_SLAVE_AIN       = 8,   // analog output
    CNR_SLAVE_AOUT      = 16,  // analog input
    CNR_SLAVE_SYSTEM    = 32,  // coupler ...
    CNR_SLAVE_COUNTER   = 64,  // counter ...
    CNR_SLAVE_DIO       = 7,   // digital input + digital output
    CNR_SLAVE_TYPE_STREAM    = 128,  // stream device ...

} CNR_SLAVE_TYPE;


/* euler angle type and jog type */

enum CNR_EULER_ANGLE_TYPE {
    CNR_EU_DEFAULT,
    CNR_EU_ZYX,
    CNR_EU_XYZ
};

enum CNR_HYB_JOG_TYPE {
    CNR_HYB_JOG_FIXED = -2,  // fixed direction
    CNR_HYB_JOG_BASE = -1,   // default
    CNR_HYB_JOG_J1 = 0,     // joint 1
    CNR_HYB_JOG_J2,         // joint 2
    CNR_HYB_JOG_J3,         // joint 3
    CNR_HYB_JOG_J4,         // joint 4
    CNR_HYB_JOG_J5,         // joint 5
    CNR_HYB_JOG_J6,         // joint 6
    CNR_HYB_JOG_J7,         // joint 7
    CNR_HYB_JOG_J8,         // joint 8
};

/* UI KBD TYPE */
enum CNR_UIKBD_TYPE
{
    CNR_UIKBD_DEFAULT,
    CNR_UIKBD_NINT,
    CNR_UIKBD_INT,
    CNR_UIKBD_HEX,
    CNR_UIKBD_FLOAT,
    CNR_UIKBD_VAR_STR,
    CNR_UIKBD_VAR_TRANS,
    CNR_UIKBD_VAR_NUMBER,
    CNR_UIKBD_VAR_JOINT,
    CNR_UIKBD_PROGRAM,
    CNR_UIKBD_STEP,
    CNR_UIKBD_EXPRESSION
};


/* print level */
#define PRINT_LEVEL_ERROR      0
#define PRINT_LEVEL_WARNING    1
#define PRINT_LEVEL_INFO       2

#include <QObject>

class CUIApp : public QObject
{
    Q_OBJECT
public:
    explicit CUIApp(QObject *parent = 0);

    static CUIApp* getInstance();

    // report hide custom ui
    void setStandardMode(bool bstandard);

public:

    // error
    bool isMotorOn();//
    bool isMotorOnSwitch();//
    bool isTPEnable();//
    bool isMoving();//
    bool isTPInching();//
    bool isError();//
    bool isWarning();
    bool isTeach();//

    CNR_TASK_STATUS getTaskStatus(int taskid);
    bool getHoldDoneStatus();

    /* basic control command */
    bool getServoOn();//
    int getServoOn2();
    void setServoOn(bool onoff);//

    bool getEnabled();
    void setEnabled(bool onoff);//

    bool getInchingOn();//
    void setInchingOn(bool onoff);//

    int  getTeachSpeed();//
    void setTeachSpeed(int speed);//

    int  getJogSpeed(int level, float& ratio);
    int  setJogSpeed(int level, float ratio);

    int  getCoordinate();//
    void setCoordinate(int co);//
    int  getUseUserCoordFlag(bool* flag);//

    bool getHoldRun();

    bool getTeachMode();//
    void setTeachMode(bool bTeach);//

    bool getCheckMode();
    int  setCheckMode(bool bCheckMode);
    int  setCheckProgram(const QString& prgName, int index);
    void setCheckKey(int checkKey);

    void setJogOn(unsigned int plusKey, unsigned int minusKey);//
    void setJogOff(unsigned int plusKey, unsigned int minusKey);//

    /* error Code */
    int getErrorMsg(QString &errorMsg);
    int getLastErrorInfo(int &errorCode, int &axis, int &subCode);
    int getSaveErrorListSize();
    void getSaveErrorList(int errlist[], int* nlist);

    /* error reset */
    void resetError();//
    void resetEcatError();//
    void resetAllError(bool bgmode = true);
    bool getResetErrorStatus();

    /* warning Code */
    int getWarningCode(int &warningCode);
    int clearWarningCode();

    /* ethercat info */
    int getECATMasterStatus(int* status, int* nresponding, int* linkstatus);
    int getECATDomainStatus(int* wc, int* wc_state);

    /* emg */
    void setEMGOn(bool onOff);
    bool getEMGOn();

    /* filterSystemKey */
    void filterSystemKey(bool setEnabled = false);
    bool getSystemKeyFlag();


    /* robot position */
    float* getCurJoint();//
    float* getCurUC();//
    float* getCurTrans();//
    float* getCurVAPosition();//
    float* getPhysicalJoint();//

    /* robot Axis */
    int getAxisCount();

    /* di/o */
    int getDI(cn_ui32* vals, int lenth);//
    int setDI(int vals);
    int getDO(cn_ui32*  vals, int lenth);//
    int setDO(int*  vals, int length);//

    /* ai/o */
    int getAI(cn_f32* vals, int length);
    int getAO(cn_f32* vals, int length);
    int setAO(int channel, cn_f32 value);//

    int getOverrideDIN(bool &boverride);
    int setOverrideDIN(bool boverride);

    /* program database */
    int getPrograms(QStringList& pgms);//
    QString getCurProgramName(int taskid, bool planProgram = false);//
    int setCurProgram(int taskid, const QString& prgName, int cycle = -1, bool autoLoadingFlag = true);// 0: success , -1: fail
    int loadCurProgram(int taskid, const QString& prgName, int cycle, bool autoLoadingFlag = true);
    int setCurStep(int taskid, int istrp);
    int createProgram(const QString& prgName);//
    int deleteProgram(const QString& prgName);//
    int getProgramStepsCount(const QString& prgName, int* stepCount);//
    int getCurProgramCycle(int taskid);
    int getProgramRunCount(int taskid);
    int setProgramRunCount(int taskid, int count);
    bool findProgram(const QString &prgName);
    int getProgramsCount();
    int insertStep(const QString& prgName, const QString &stepName, int index = 1);
    int deleteStep(const QString& prgName, int index);
    int getProgramSteps(const QString& prgName, QStringList& steps);//
    int setProgramSteps(const QString& prgName, QStringList& steps);//

    /* program save */
    int saveProgram(const QString& prgName);
    int saveProgramAll();

    /* execute */
    int executeCommand(char* str);

    /* program execute */
    int executeProgram(int taskid, const QString& prgName, int cycle);
    int holdProgram(int taskid);//
    int abortProgram(int taskid);
    int continueProgram(int taskid);//
    int resetCurProgram(int taskid);// 0: success , -1: fail
    int clearCurProgram(int taskid);// 0: success , -1: fail
    int runNxtStep(int taskid);
    int runNxtStepOver(int taskid);
    int runToNextMotionStep();
    int runBackStep(int taskid);
    int runBackStepOver(int taskid);

    int moveToPosition(const QString& varName, bool isLinear = false);
    int moveToPosition2(const QString& varName, float stableTime = 0.f , bool isLinear = false);
    int setStableTime(float time);

    /* program step index*/
    int getRunningStepIndex(int taskid, int* movestep, int* planstep);//
    int getRunningMainStepIndex(int *planstep, int taskid = 0);
    int getCurStep(int taskid, int& stepId, bool bplan);

    /* program OverrideSpeed */
    int setSpeed(float speed);//
    int getOverrideSpeed();//

    /* program stack */
    int getCurProgramStack(int taskid, QStringList& strList);

    /* subProgram Auto Start setting */
    int getAutoRunSubProgram(bool& setEnabled, int taskid = 1);
    int setAutoRunSubProgram(bool setEnabled, int taskid = 1);
    int saveRunProgram(int taskid, const QString &prgName, int cycle = -1);

    /* smooth option */
    int getSmoothOption(bool &flag, float &stime);
    int setSmoothOption(bool flag, float stime);

    /* variable */
    int getVariableCount(int type, int* count);//
    int getVariableName(int type, int index, QString& varname);//
    int getVariableListAll(int type, QStringList& varname, QVector<cn_variant> &vardataList);// all variable list
    int getVariableList(int type, QStringList& varname, QVector<cn_variant> &vardataList);// variable + data variable list
    int getVariableData(int type, const QString& varname, cn_variant* value);//
    int setVariableData(int type, const QString& varname, cn_variant& value, bool createNonExist);//
    int deleteVariable(int type, const QString& varname);
    int deleteVariableAll();

    int getVariableType(const QString &varname, int &type, int &dimension, int &exist);
    int getVariables(QStringList& varnames, QList<cn_variant>& values);
    int setVariables(QStringList& varnames, QList<cn_variant>& values);

    /* variable save */
    void saveVariable();
    int getVariableAutoSave(bool& setEnabled);
    int setVariableAutoSave(bool setEnabled);
    int getLocalVariable(QString pgname, int type, QStringList& varName, QList<cn_variant>& values);

    /* setup */
    int zeroing(unsigned long axis_mask);//
    int zeroingCount(long* penc);
    int setZeroingOffset(float* posArray, int naxis);
    int getZeroingOffset(float* posArray);

    /* log list */
    int getLogList(QStringList &loglist);
    int setUserLog(int code, const QString& msg);
    void clearLogMask();
    int addLogMask(int from, int to);
    int getLogMaskSize(int &size);
    int getLogMask(int index, int &from, int &to);

    int enquePrintListItem(int level, const QString& msg);

    /* IO Divice Count (type 1~6  : di, do, ai, ao, dio, aio), */
    int getIOCount(CNR_SLAVE_TYPE type, int& Count);
    int getSlaveCount(int& count);
    int getSlaveType(QVector<CNR_SLAVE_TYPE>& vSlvType);
    int getSlaveModel(QStringList& slvList);

    int getDeicatedSignal(CNR_DDC_SIGNAL signal, bool *enable);
    int setDedicatedSignal(CNR_DDC_SIGNAL signal, bool setEnabled);

    /* steam dev data in/out pointer */
    int getStreamOutDataPtr(int index, char** streamOut, int* streamOutSize);
    int getStreamInDataPtr(int index, char** streamIn, int* streamInSize);

    /* SDO */
    int* getMotorActualVelocity();
    int* getMotorActualTorque();

    /* PDO */
    long* getPDOT_FollowingError();
    long* getPDOT_Velocity();
    short* getPDOT_Torque();
    int* getPDOT_StatusWord();
    long* getPDOR_TargetPosition();
    long* getPDOT_ActualPosition();


    int getSDO(int id, int* args, int lenth, unsigned long* dataList);
    int setSDO(int id, int* args, int lenth, unsigned long* dataList);
    int getSDOList(int* args, int argLenth, unsigned long* dataList, int& dataLenth);

    /* TPWrite */
    int getTPWrite(QStringList &strList, QVector<CNR_TP_MSG_STATUS> &msgStatus, bool skipEmptyMessage = true);

    /* user params */
    int getUserParams(QStringList& params);
    int setUserParams(QStringList params);

    /* robot conf */
    int getRobotConf(QStringList& dataList);
    int setRobotConf(QStringList dataList);

    /* robot information */
    int getRobotName(QString& robotName);

    /* robot type */
    CNR_MECH_TYPE getRobotType();

    /* date time */
    int getDateTime(QString& strTime);
    int setDateTime(QString strTime);

    /* system reboot */
    int rebootSystem();

    /* DTP */
    int setDTPBuzzerOn(int count, int interval);
    int setDTPBuzzerOn2(int count, int intervalOn, int intervalOff);
    int setDTPBuzzerOff();
    int setDTPLed(CNR_LED ledPos, CNR_LED_COLOR ledColor);

    /* Debug Flag */
    bool getDebugFlag();

    /* DryRun Mode */
    bool getDryRunMode();

    /* coordinate name */
    int getCurBaseName(QString& baseName);
    int getCurToolName(QString& toolName);
    int setCurTool(QString& toolName);
    int clearTool();

    /* inching 1 step mm or degee value set */
    /* level 0: low, 1: mid, 2: high */
    int getInchingStep(int level, float &step_mm);
    int setInchingStep(int level, float step_mm);  //step_mm is 'mm'
    int getInchingStepAngular(int level, float& step_deg);
    int setInchingStepAngular(int level, float step_deg); //step_deg is 'degee'
    int getInchingAccTime(float& acctime);
    int setInchingAccTime(float acctime);

    /* Home */
    int setHomeStart();
    int setHomeStop();
    CNR_HOME_STATUS getHomeStatus();
    int getHomePosition(int index, float* pos, int npos, float& bound);
    int setHomePosition(int index, float* pos, int npos, float bound);
    int moveToHome(int index = 0);

    /* euler angle type */
    int getEulerAngleType(CNR_EULER_ANGLE_TYPE& type);
    int setEulerAngleType(CNR_EULER_ANGLE_TYPE type);

    /* jog type */
    int getHybridJogMode(bool &hybrid, CNR_HYB_JOG_TYPE xyzrpy[], int ntype);
    int setHybridJogMode(bool hybrid, CNR_HYB_JOG_TYPE xyzrpy[], int ntype);

    /* SoftLimitMonitorFlag */
    // disable repeat mode limit check option
    int setSoftLimitMonitorFlag(bool setEnabled);
    bool getSoftLimitMonitorFlag();


    /* Safety Zone,  World Zone */
    bool getWZCheckFlag();
    int setWZCheckFlag(bool flag);

    int WZClear(int index);
    int WZAddBox(int index, int op, cn_vec3& pmin, cn_vec3 &pmax, cn_trans2& frame);
    int WZAddCyl(int index, int op, cn_vec3& pc, float r, float h, cn_trans2& frame);

    int WZEnable(int index, int is_negate);
    int WZDisable(int index);

    int WZGetFlag(int index, int &is_enabled, int &is_negate);
    int WZGetEntityCount(int index, int& count);
    int WZGetEntityType(int index, int entity_index, int& type);
    int WZGetEntityBox(int index, int entity_index, cn_vec3& pmin, cn_vec3& pmax);
    int WZGetEntityCyl(int index, int entity_index, cn_vec3& pc, float &radius, float& height);
    int WZGetEntityFrame(int index, int entity_index, cn_trans2& frame);
    int WZGetEntityOperator(int index, int entity_index, int &op);
    int WZSaveAll();

    // Z Compensation

    int getZCompTableSize(int tblidx, int &size);
    int clearZCompTable(int tblidx);
    int addZCompTableItem(int tblidx, float r, float z);
    int getZCompTableItem(int tblidx, int index, float &r, float &z);
    int setZCompTableItem(int tblidx, int index, float r, float z);

    // DPS: dynamic path shift
    int getDPSShift(float &delx, float &dely, float &delz);
    int setDPSShift(float delx, float dely, float delz);

    int getDPSSpeed(float &speed);
    int setDPSSpeed(float speed);

    int setDPSEnableFlag(bool flag);
    bool getDPSEnableFlag();


    /* calc */
    int calcInverse(cn_trans &trIn, float* oldang, float* jntOut, cn_conf &confIn);
    int calcForword(float* jntIn, cn_trans &trOut);

    int calcInverseMulti(cn_trans &trIn, float* oldang, float* jntOut, cn_mconf &confIn);   /* multihand */
    int calcRobotConfig(float* jntin, cn_mconf &confOut);                                   /* multihand */

    int getCustomHint(cn_mconf &confOut);                                                   /* multihand */
    int setCustomHint(cn_mconf confIn);                                                     /* multihand */


    /* cycleSyncMotionFlag */
    bool getRepeatCycleSyncMotionFlag();
    int  setRepeatCycleSyncMotionFlag(bool flag);

    /* run Sequence Timer */
    int setRunSequenceTimer(float servo_on, float brake_on, float run_ok); //sec
    int getRunSequenceTimer(float& servo_on, float& brake_on, float& run_ok); //sec
    int setHoldSequenceTimer(float holdwait, float brakeon, float servooff);
    int getHoldSequenceTimer(float &holdwait, float &brakeon, float &servooff);

    /* be no use */
    void raiseReceivePrintItemSignal(const QString &str, int level);

    /* ui tools */
    int showNumberDialog(const QString& strIn, QString& strOut);
    int showPasswordDialog(const QString& strIn, QString& strOut);
    int showHexDialog(const QString& strIn, QString& strOut);
    int showKeyboardDialog(QString& str);

    int showHomeSearchDialog();
    int showSetInchingDialog();
    int showProgramListDialog(const QString &strIn, QString &strOut);
    int showToolListDialog(QStringList& listIn, QString& strOut);
    int showMessageBox(QString text, QString title, QString inform, int flag);

    /* Torque Limit */
    int getMinTorqueLogData(int axis, short &logData);
    int getMaxTorqueLogData(int axis, short &logData);
    int getAverageTorqueLogData(int axis, short &logData);

    int startTorqueDataLogging(bool flag);
    int setTorqueLimitMonitorFlag(bool flag);
    int setTorqueLimitValue(int axis, short positive, short negative);
    int setKalmanFilterVolumn(int volumn);
    int resetMinMaxTorqueData();

    int getCurTorque(short* curtor, int naxis);
    int getCmdTorque(short* curtor, int naxis);

    /* version type*/

    enum VERSION_TYPE
    {
        VT_CORECON,
        VT_MASTER,
        VT_KERNEL,
    };

    int getVersion(VERSION_TYPE type, QString &version);

    int captureTPScreen();

    /* remote */
    int getSimRemoteLockingState(bool &locking);
    int unlockSimRemoteControl();

    /* max command encoder */
    int getMaxCommandEnc(long* teach, long* repeat);

    /* Axis Limit */
    int getAxisLimitN(int axis, float &value);
    int getAxisLimitP(int axis, float &value);

    int showKeyboardDialog2(QString title, QString& str, CNR_UIKBD_TYPE type);

    /* Multi-Arm Robot */
    int MA_getArmSize(int &size);
    /* index is 0 ~ TCP -1 */
    int MA_getMasterArm(int &armIndex);
    int MA_setMasterArm(int armIndex);
    int MA_getArmOrder(int *orders);
    int MA_setArmOrder(int *orders);
    int MA_setHint(int index, float value);
    int MA_getHint(int index, float &value);

signals:

    /**
     * @fn CUIApp::receivePrintItem
     * getTPWrite와 동일한 기능이며 함께 사용하지 않아야한다.
     * @warning getTPWrite와 함께 사용하지 않아야한다.
     * @warning filterSystemKey true 시 동작되지 않는다.
     * @param [out] str
     *              print message
     * @param [in] level
     *              -1 : clear, 0 : error, 1 : warning, 2 : info
     *
     */
    void receivePrintItem(const QString &str, int level);
    //void requestClearOutput();

private slots:


};

#endif // DEF_CUIAPI_H
