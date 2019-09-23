#ifndef CUIECAT
#define CUIECAT


#include <QStringList>


class CUIEcat
{

public:
    CUIEcat();

    static CUIEcat *getInstance();

    // read write sdo
    int readSDO(int id, int index, int subindex, int bitsize, unsigned long* data);
    int writeSDO(int id, int index, int subindex, int bitsize, unsigned long data);

    // read write slave registry
    int readSlaveReg(int id, int index, int size, unsigned long *data);
    int writeSlaveReg(int id, int index, int size, unsigned long *data);

    // dec stats
    int getDecErrorState(unsigned int &value);               //Dec Error State
    int getRtCycletimeAvg(unsigned int &value);              //Dec RT Cycletime Avg
    int getRtCycletimeMin(unsigned int &value);              //Dec RT Cycletime Min
    int getRtCycletimeMax(unsigned int &value);              //Dec RT Cycletime Max
    int getRtTaskRuntimeAvg(unsigned int &value);            //Dec RT Task Runtime Avg
    int getRtRaskRuntimeMin(unsigned int &value);            //Dec RT Task Runtime Min
    int getRtTaskRuntimeMax(unsigned int &value);            //Dec RT Task Runtime Max
    int getCurWorkingCount(unsigned short &value);           //Current working cnt
    int getOnlineSlaveNum(unsigned short  &value);           //Online slave num
    int getRtTaskState(unsigned short &value);               //RT task state
    int getRtTaskCount(unsigned int &value);                 //RT task cnt
    int getWCChangeCount(unsigned short &value);             //Working cnt change cnt
    int getOnlineSlaveNumErrorCount(unsigned short & value); //Online slave err
    int getRdyEventErrorCount(unsigned short &value);        //Ready ev err
    int getAppEventErrorCount(unsigned short &value);        //APP ev err
    int getEndEventErrorCount(unsigned short &value);        //END ev err
    int getWaitPeriodErrorCount(unsigned short & value);     //Wait period err
    int getDeepSleepErrorCount(unsigned short &value);       //Deep sleep err
    int getWakeupLargeErrorCount(unsigned short &value);     //Wakeup large err
    int getNetdevRxLengthErrors(unsigned int &value);        //Netdev Rx length err
    int getNetdevRxCrcErrors(unsigned int &value);           //Netdev Rx crc err
    int getNetdevRxFifoErrors(unsigned int &value);          //Netdev Rx fifo err
    int getEcdevTxCount(__uint64_t &value);                  //Ecdev Tx cnt
    int getEcdevRxCount(__uint64_t &value);                  //Ecdev Rx cnt
    int getEcdevLostPacket(unsigned int &value);             //Lost Frames
    int getEcdevTxBytes(__uint64_t &value);                  //Ecdev Tx Byte
    int getEcdevRxBytes(__uint64_t &value);                  //Ecdev Rx Byte
    int getCurDCDiffTime(int &value);                        //Cur DC Diff Time
    int getDCTimeDiagTable(unsigned int* values, int size);  //DC Time Diag Table
    int resetAllDecStats();                                  //clear decStats
    int resetDCTimeDiagTable();                              //clear DC TIM Diag Table
    bool getDryRunMode();                                    //Dry run mode
    int getMasterStatus(int* nresponding, int* link_status); //Mater State
    int getPDOT_StatusWord(int lidx);                        //Current Statusword


    // slave
    int getSlaveCount(int& count);
    int getSlaveType(int index, int& type);
    int getSlaveModel(QStringList& slvList);
    int getSlaveStatus(int index, int& status);
    int getSlaveConfigStatus(int index, int& alstate, int& linkstate);
    int getSlaveID(int index, unsigned int& vendor, unsigned int& product);






};

#endif // CUIECAT

