#ifndef NROBO_H
#define NROBO_H

#include <QStringList>
#include <QDate>
#include "cntype.h"

/**
 * @enum The MECH_TYPE enum
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
    CNR_DDCI_HOLD,                  // hold/run switchhttp://viki.core-robot.com:8000/issues/662

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

/* trajectry data */
struct cn_trajectory
{
    float S;
    cn_i32 enc[32];
    cn_vec3 trans;
};


#define CNR_KEYPAD_LEFT     18
#define CNR_KEYPAD_RIGHT    20
#define CNR_KEYPAD_UP       19
#define CNR_KEYPAD_DOWN     21

class CNController;
class CNRoboPrivate;
class CNRobo
{
    friend class CNController;

    CNRobo();
    static CNRobo*   m_pInstance;

    /* private data class */
    CNRoboPrivate*  m_pPrivate;

public:
    static CNRobo* getInstance();//
    inline CNRoboPrivate* p() { return m_pPrivate; }

protected:
    int getProgramIndex(const QString& prgName);
    int regenProgramList();

public:

    /* server interface */
    int startService();//
    bool stopService();//

    /**
     * @fn getServerAddress
     * @return address
     */
    QString getServerAddress();//

    /* Address */
    /**
     * @fn setServerAddress
     * @param[in] addr
     */
    void setServerAddress(QString& addr);//

    /**
     * @fn getPort
     * @return port number
     */
    int getPort();//

    /* Port */
    /**
     * @fn setPort
     * @param[in] port
     */
    void setPort(int port);//
    bool isConnected();//

    /* server version */
    /**
     * @fn getServerVersion
     * @param [out]ver
     * @return success return 0
     */
    int getServerVersion(unsigned int* ver);//   

    /* client version */
    /**
     * @fn getVersion
     * @return client version
     */
    unsigned int getVersion();//

    /* version type*/

    enum VERSION_TYPE
    {
        VT_CORESERVER,
        VT_MASTER,
        VT_KERNEL,
        VT_CNROBO
    };

    int getVersion2(VERSION_TYPE type, QString &version);//

    /* login not used */
    int login(char* passwd);//

    /**
     * @fn getLoginStatus
     * @param [out]bLogin
     * @return success return 0
     */
    int getLoginStatus(bool* bLogin);//

    /* lock robot */
    /* other connection cannot set values */
    /**
     * @fn lock
     *   lock robot, if succeeded, it cannot set the values through the other connections.
     *   if enable guard is true, the communication between client and server must be accomplished.
     *   when server does not get the status message within timeLimit, the robot motion is stopped.
     *   and, goes to error status
     *
     * @param[in] timeLimit  : timeLimit == 0 : not use ,  msec
     * @return
     *    if succeeded, return 0
     *    others, error
     */
    int lock(int timeLimit);//

    /**
     * @fn unlock
     *    the connection is unlock, and only reading the status is possible.
     *
     * @return
     */
    int unlock();//

    /**
     * @fn getLockStatus
     * @param [out]bLock
     * @return success return 0
     */
    int getLockStatus(bool* bLock);//

    /* robot status */
    unsigned int getStatus();//

    bool isMotorOn();//
    bool isTPEnable();//
    bool isMoving();//
    bool isTPInching();//
    bool isError();//
    bool isWarning();
    bool isTeach();//

    /* getArmStatus not used */
    int getArmStatus();

    CNR_TASK_STATUS getTaskStatus(int taskid);
    bool getHoldDoneStatus();

    /* basic control command */
    bool getServoOn();//
    void setServoOn(bool onoff);//
    bool getServoOnPerAxis(int index);
    int  setServoOnPerAxis(int index, bool onoff);
    int  getServoOnMode(int &mode);
    int  setServoOnMode(int mode);
    int  getAxisServoOnMode(int index, int &mode);
    int  setAxisServoOnMode(int index, int mode);

    bool getEnableOn();
    void setEnableOn(bool onoff);//

    bool getInchingOn();//
    void setInchingOn(bool onoff);//

    int  getTeachSpeed();//
    void setTeachSpeed(int level);//

    int  getJogSpeed(int level, float& ratio);
    int  setJogSpeed(int level, float ratio);
    int  saveJogSpeed();

    int  getCoordinate();//
    void setCoordinate(int co);//
    int  getUseUserCoordFlag(bool* flag);//

    bool getHoldRun();

    bool getTeachMode();//
    void setTeachMode(bool bTeach);//

    /* check mode */
    bool getCheckMode();
    int  setCheckMode(bool bCheckMode);
    int  setCheckProgram(const QString& prgName, int index);
    void setCheckKey(int checkKey);

    void setJogOn(unsigned int plusKey, unsigned int minusKey);//
    void setJogOff(unsigned int plusKey, unsigned int minusKey);//

    /* error Code */
    int getErrorMsg(QString& errorMsg);
    int getLastErrorInfo(int& errorCode, int& axis, int& subCode);

    /* error reset */
    void resetError();//
    void resetEcatError();
    void resetAllError(bool bgmode);
    bool getResetErrorStatus();

    /* warning Code */
    int getWarningCode(int& warningCode);
    int clearWarningCode();


    /* emg */
    void setEMGOn(bool onOff);

    /* robot position */
    float* getCurJoint();//
    float* getCurUC();//
    float* getCurTrans();//
    cn_trans2* getCurTMatrix();

    /* robot Axis */
    int getAxisCount();

    /* track option falg : L axis setting check */
    bool getTrackOptionFlag();

    /* di/o */
    int getDI(cn_ui32* vals, int lenth);//
    int setDI(int vals);
    int getDO(cn_ui32*  vals, int lenth);//
    int setDO(int*  vals, int length);

    /* ai/o */
    int getAI(cn_f32* vals, int length);
    int getAO(cn_f32* vals, int length);
    int setAO(int channel, cn_f32 value);

    /* override din */
    int getOverrideDIN(bool &boverride);
    int setOverrideDIN(bool boverride);

    /* program */
    int getPrograms(QStringList& pgms);//
    QString getCurProgramName(int taskid, bool planProgram = false);//
    int setCurProgram(int taskid, const QString& prgName, int cycle = -1);// 0: success , -1: fail
    int setCurStep(int taskid, int istrp);
    int createProgram(const QString& prgName);//
    int deleteProgram(const QString& prgName);//
    int getProgramStepsCount(const QString& prgName, int* stepCount);//
    int getCurProgramCycle(int taskid);
    int getProgramRunCount(int taskid);
    int setProgramRunCount(int taskid, int count);   //this is cycle
    bool findProgram(const QString &prgName);
    int getProgramsCount();
    int insertStep(const QString& prgName, const QString &stepName, int index = 1);
    int deleteStep(const QString& prgName, int index);
    int getProgramSteps(const QString& prgName, QStringList& steps);//
    int setProgramSteps(const QString& prgName, QStringList& steps);//

    /* program file */
    int importProgram(const QString &filePath);
    int importProgramList(QStringList &PathList);

    /* program save */
    int saveProgram(const QString& prgName);
    int savePrograms(QStringList prgNames);
    int saveProgramAll();
    int getProgramAutoSave(bool& enable);
    int setProgramAutoSave(bool enable);


    /* execute */
    int executeCommand(char* str);

    /* program execute */
    int executeProgram(int taskid, const QString& prgName, int cycle);
    int holdProgram(int taskid);//
    int abortProgram(int taskid);
    int continueProgram(int taskid);//
    int continueProgram2(int taskid, int option);
    int resetCurProgram(int taskid);// 0: success , -1: fail
    int clearCurProgram(int taskid);// 0: success , -1: fail
    int runNxtStep(int taskid);
    int runNxtStepOver(int tsakid);
    int runToNextMotionStep();
    int runBackStep(int taskid);
    int runBackStepOver(int taskid);

    int moveToPosition(const QString& varName, bool isLinear = false);
    int moveToPosition2(const QString& varName, float stableTime = 0.f , bool isLinear = false);
    int setStableTime(float time);

    /* program step index*/
    int getRunningStepIndex(int taskid, int* movestep, int* planstep);//
    int getRunningMainStepIndex(int *planstep);

    /* program OverrideSpeed */
    int setSpeed(float speed);//
    int getOverrideSpeed();//

    /* program stack */
    int getCurProgramStack(int taskid, QStringList& strList);

    /* subProgram Auto Start setting */
    int getAutoRunSubProgram(bool& enable, int taskid = 1);
    int setAutoRunSubProgram(bool enable, int taskid = 1);

    /* smooth option */
    int getSmoothOption(bool &flag, float &stime);
    int setSmoothOption(bool flag, float stime);

    /* variable */
    int getVariableCount(int type, int* count);//
    int getVariableName(int type, int index, QString& varname);//
    int getVariableList(int type, QStringList& varname, QVector<cn_variant>& varDataList);//
    int getVariableData(int type, const QString& varname, cn_variant* value);//
    int setVariableData(int type, const QString& varname, cn_variant& value, bool createNonExist);//
    int deleteVariable(int type, const QString& varname);
    int deleteVariableAll();
    int getVariableType(const QString &varname, int &type, int &dimension);

    /* variable file */
    int importVariable(const QString& varPath);
    int exportVariable(const QString& varPath);

    /* variables */
    int getVariables(QStringList& varnames, QList<cn_variant>& values);
    int setVariables(QStringList& varnames, QList<cn_variant>& values);

    /* localVariable list */
    int getLocalVariableCount(QString progName, int &count);
    int getLocalVariableList(QString progName, QStringList& varNames, QList<cn_variant> &values, QList<cn_ui8> &isParam);

    /* variable save */
    void saveVariable();
    int getVariableAutoSave(bool& enable);
    int setVariableAutoSave(bool enable);

    /* setup */
    int zeroing(unsigned long axis_mask);//
    int zeroingCount(long* penc);
    int setZeroingOffset(float* posArray, int naxis);
    int getZeroingOffset(float* posArray);

    /* log list */
    int getLogList(QStringList &loglist);
    int getSelectedlogList(QStringList &loglist, const QDate &fromDate, const QDate &toDate);

    int setUserLog(int code, const QString& msg);

    /* IO channel size */
    int getChannelSize(CNR_SLAVE_TYPE type, int *size, int nChannel);

    /* AO Table, Spec */
    int getAOValueTable(int channel, float* tAry, float* vAry, int &size);
    int setAOValueTable(int channel, float* tAry, float* vAry, int size);
    int getAOSpec(int channel,  int &min_int,  int &max_int,  float &min_sig,  float &max_sig);
    int setAOSpec(int channel,  int min_int,  int max_int,  float min_sig,  float max_sig);

    /* AI Table, Spec */
    int getAIValueTable(int channel, float* tAry, float* vAry, int &size);
    int getAISpec(int channel,  int &min_int,  int &max_int,  float &min_sig,  float &max_sig);


    /* IO Divice Count */
    int getIOCount(CNR_SLAVE_TYPE type, int& Count);
    int getSlaveCount(int& count);
    int getSlaveType(QVector<CNR_SLAVE_TYPE>& vSlvType);
    int getSlaveModel(QStringList& slvList);
    int setDedicatedSignal(CNR_DDC_SIGNAL signal, int enable);
    int getDedicatedSignal(CNR_DDC_SIGNAL signal, int &index, int &enable);

    int findSigmapMapnoList(int *arrSig, int *arrMapno, int &size);
    int getIOAliasNameList(int *type, int *index, int &size, QStringList &nameList);
    int setIOAliasNameList(int *type, int *index, int size, QStringList nameList);
    int saveIOAliasNameList(int *type, int size);

    /* SDO */
    int* getMotorActualVelocity();
    int* getMotorActualTorque();

    /* PDO */
    long* getPDOT_FollowingError();
    long* getPDOT_Velocity();
    short* getPDOT_Torque();
    int* getPDOT_StatusWord();

    /* SDO */
    int getSDO(int id, int* args, int lenth, unsigned long* dataList);
    int setSDO(int id, int* args, int lenth, unsigned long* dataList);
    int getSDOList(int* args, int argLenth, unsigned long* dataList, int& dataLenth);

    /* TPWrite */
    int getTPWrite(QStringList& strList, QVector<CNR_TP_MSG_STATUS>& msgStatus);


    /* WatchDogLimit */
    int getWatchDogLimit();
    int setWatchDogLimit(int time);

    /* user params */
    int getUserParams(QStringList& params);
    int setUserParams(QStringList params);

    /* app conf */
    int getAppConf(QStringList &dataList);
    int setAppConf(QStringList dataList);

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

    /* commandCycleTime */
    int getCommandCycleTime();
    void setCommandCycleTime(int msec);

    /* RT Task */
    bool getRtTaskFlag();
    void setRtTaskFlag(bool falg);

    /* system reboot */
    int rebootSystem();

    /* DTP */
    int setDTPBuzzerOn(int count, int interval);
    int setDTPBuzzerOn2(int count, int intervalOn, int intervalOff);
    int setDTPBuzzerOff();
    int setDTPLed(CNR_LED ledPos, CNR_LED_COLOR ledColor);

    /* Debug Flag */
    bool getDebugFlag();

    /* DryRun Mode Flag */
    bool getDryRunMode();

    /* coordinate name */
    int getCurBaseName(QString& baseName);
    int getCurToolName(QString& toolName);
    int getCurBaseFrame(cn_trans2& baseFrame);

    /* inching 1 step mm or degee value set */
    /* level 0: low, 1: mid, 2: high */
    int getInchingStep(int level, float& step_mm);
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
    int getHybridJogMode(bool& hybrid, CNR_HYB_JOG_TYPE xyzrpy[], int ntype);
    int setHybridJogMode(bool hybrid, CNR_HYB_JOG_TYPE xyzrpy[], int ntype);

    /* SoftLimitMonitorFlag */
    // disable repeat mode limit check option
    int setSoftLimitMonitorFlag(bool enable);
    bool getSoftLimitMonitorFlag();


    /* Safety Zone,  World Zone */

    bool getWZCheckFlag();
    int setWZCheckFlag(bool flag);
    bool getWZCheckStatusTeach();
    bool getWZCheckStatusRepeat();

    int WZClear(int index);
    int WZAddBox(int index, int op, cn_vec3& pmin, cn_vec3& pmax, cn_trans2& frame);
    int WZAddCyl(int index, int op, cn_vec3& pc, float r, float h, cn_trans2& frame);

    int WZEnable(int index, int is_negate);
    int WZDisable(int index);

    int WZGetFlag(int index, int& is_enabled, int& is_negate);
    int WZGetEntityCount(int index, int& count);
    int WZGetEntityType(int index, int entity_index, int& type);
    int WZGetEntityBox(int index, int entity_index, cn_vec3& pmin, cn_vec3& pmax);
    int WZGetEntityCyl(int index, int entity_index, cn_vec3& pc, float& radius, float &height);
    int WZGetEntityFrame(int index, int entity_index, cn_trans2& frame);
    int WZGetEntityOperator(int index, int entity_index, int &op);
    int WZSaveAll();


    /* Database */

    int createVariableFile(const QString& varPath, QStringList& varNames, QList<cn_variant>& variables);
    int getVariableFile(const QString& varPath, QStringList& varNames, QList<cn_variant>& variables);

    int createProgramFile(const QString& filePath, QStringList& steps);
    int getProgramFile(const QString& filePath, QStringList& steps);

    int makeDatabaseDir(const QString& dirPath);
    int makeDatabaseText(const QString& textPath);

    int copyDatabaseDir(const QString& dirPath, const QString& destDirPath, bool overWrite = false);
    int copyDatabaseFile(const QString& filePath, const QString& destFilePath);

    int moveDatabaseDir(const QString& dirPath, const QString& destDirPath, bool overWrite = false);
    int moveDatabaseFile(const QString& filePath, const QString& destFilePath);

    int deleteDatabaseDir(const QString& dirPath);
    int deleteDatabaseFile(const QString& filePath);

    int getDatabaseDirCount(const QString& dirPath, int& count);
    int getDatabaseFileCount(const QString& dirPath, int& count);

    int getDatabaseDirList(const QString& dirPath, QStringList& files);
    int getDatabaseFileList(const QString& filePath, QStringList& files);

    int saveDatabaseFile(const QString& filePath, char* buf, int nbuf);
    int loadDatabaseFile(const QString& filePath, char* buf, int& nbuf);

    int checkDirFileExist(const QString& dirFilePath, bool &exist);

    int makeCheckSumFile(const QString& filePath, const QString& checkSumFilePath);
    int checkSumFile(const QString& filePath, const QString& checkSumFilePath, bool &checkSum);

    int makeCheckSumDir(const QString& dirPath, const QString& checkSumFilePath);
    int checkSumDir(const QString& dirPath, const QString& checkSumFilePath, bool &checkSum);


    /* calc */
    int calcInverse(cn_trans &trIn, float* oldang, float* jntOut, cn_conf &confIn);
    int calcForward(float* jntIn, cn_trans& trOut);

    /* cycleSuncMotionFlag */
    bool getRepeatCycleSyncMotionFlag();
    int  setRepeatCycleSyncMotionFlag(bool flag);

    /* trajectory */
    int startTrajectoryLogging();
    int stopTrajectoryLogging();
    int getTrajectoryLogSize(int &size);
    int getTrajectoryS(cn_trajectory *S, int size);
    int getTrajectoryCurEncoder(cn_trajectory *trj, int size);
    int getTrajectoryCmdEncoder(cn_trajectory *trj, int size);
    int getTrajectoryCmdTrans(cn_trajectory *trj, int size);

    int getRunSequenceTimer(float& servo_on, float& brake_on, float& run_ok);
    int setRunSequenceTimer(float servo_on, float brake_on, float run_ok);

    /* user limit */
    int getULimit(float *joint, int size);
    int setULimit(float* joint, int size);
    int getLLimit(float *joint, int size);
    int setLLimit(float* joint, int size);

};

#endif // NROBO_H
