
/*
 *  CUSTOMUI
 *
 */
#include <stdio.h>

#include "crbtype.h"
#include "crbapi.h"

#ifdef __cplusplus
extern "C" {
#endif

/* get widget pointer */
extern int cx_cmdtor();
extern void* cui_get_subwidget();
extern void* createTestSubWidget();

#ifdef __cplusplus
}
#endif

static void* s_subwidget_ptr;

void* cui_get_subwidget()
{
    if(s_subwidget_ptr == NULL)
        s_subwidget_ptr = (void*)createTestSubWidget();

    return s_subwidget_ptr;
}

#include "functions.h"
#include "variables.h"

int cx_cmdtor()
{

    if (flag){
        if (turn_on){
            if (delay == 0){
                crbapi::set_rs485_pdo_communication(0);

                sdoSetData += 500;
                sdoSetData = sdoSetData > goal_vel ? goal_vel : sdoSetData;

                capp->setSDO(0, &sdoIndexGoalVel, 1, &sdoSetData);

                crbapi::set_rs485_pdo_communication(1);
            }
        }

        if (turn_off){
            capp->setServoOn(false);
            sdoSetData = 0;

            turn_off = false;
            flag = false;
        }

        delay++;
        if (delay >= 1000){
            delay = 0;
        }

        crbapi::get_current_first_encoder(0, &enc1, 1);
        crbapi::get_current_second_encoder(0, &enc2, 1);
        crbapi::get_user_input1(0, &enc_diff, 1);
        crbapi::get_cur_enc(0, &pos);
        crbapi::get_cur_velocity(0, &vel, 1);

        diff = enc_diff*ENC2DEG*DEG2RAD;
        actual_torque = k*diff*ENC2DEG*DEG2RAD;
        pos_rad = pos*ENC2DEG*DEG2RAD;
        vel_rad = vel*ENC2DEG*DEG2RAD;
    }
}

void set_torque(short value)
{
    tor_1 = value;
}

void set_torque_mode(long value){
    torque_mode[0] = value;
}

short get_torque()
{
    return get_torque_value[0];
}

double get_torque_cal(){
    return torque_cal;
}

long int get_enc1(){
    return enc1;
}

long int get_enc2(){
    return enc2;
}

long int get_enc_diff(){
    return enc_diff;//enc1/75 - enc2;
}

long int get_pos(){
    return pos;
}

double get_pos_deg(){
    return pos*ENC2DEG;
}

long int get_vel(){
    return vel;
}

double get_vel_rpm(){
    return vel*VEL2RPM;
}

double get_vel_deg(){
    return vel*VEL2RPM*RPM2DEG;
}

void get_data(double *req_data)
{
    memcpy(req_data, TP_data, sizeof(double)*data_cnt);
}

void set_flag(bool in_flag){
    if (!in_flag){
        err_vel_accum = 0;
        err_vel_prev = 0;
    }
    else{
        crbapi::set_rs485_pdo_communication(0);

        int index[2] = {sdoIndexOperatingMode, sdoIndexGoalVel};
        unsigned long data[2] = {1, 0};
        capp->setSDO(0, index, 1, data);

        crbapi::set_rs485_pdo_communication(1);
    }
    capp->setServoOn(in_flag);
    flag = in_flag;
}

void set_gain(){
    crbapi::set_rs485_pdo_communication(0);

    int sdoIndex[15] = {0x03160020, 0x031A0020, 0x031E0020, 0x03220020, 0x03260020,
                        0x032A0020, 0x032E0020, 0x03320020, 0x03360020, 0x033A0020,
                        0x033E0020, 0x03420020, 0x03460020, 0x034A0020, 0x034E0020};
    unsigned long sdoSetData[15] = {0,};

    capp->setSDO(0, sdoIndex, 15, sdoSetData);

    crbapi::set_rs485_pdo_communication(1);
}

void get_gain(unsigned long *rdata){
    crbapi::set_rs485_pdo_communication(0);

    int sdoIndex[15] = {0x03160020, 0x031A0020, 0x031E0020, 0x03220020, 0x03260020,
                        0x032A0020, 0x032E0020, 0x03320020, 0x03360020, 0x033A0020,
                        0x033E0020, 0x03420020, 0x03460020, 0x034A0020, 0x034E0020};
    unsigned long sdoGetData[15] = {0,};

    capp->getSDO(0, sdoIndex, 15, sdoGetData);

    for (int i = 0; i < 15; i++){
        rdata[i] = sdoGetData[i];
    }

    crbapi::set_rs485_pdo_communication(1);
}

void set_turn_on(){
    turn_on = true;
    turn_off = false;
    sdoSetData = 0;
}

void set_turn_off(){
    turn_on = false;
    turn_off = true;
    sdoSetData = 0;
}
