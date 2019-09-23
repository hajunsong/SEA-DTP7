
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
    naxis = crbapi::get_axis_count();

//    torque_mode[0] = 1;

//    dob.run(dob_pos, dob_vel, dob_tor, collision);

    crbapi::set_user_output2(0, torque_mode, 1);

    torque_value[0] = tor_1;

    crbapi::get_current_first_encoder(0, &enc1, 1);
    crbapi::get_current_second_encoder(0, &enc2, 1);
    crbapi::get_cur_enc(0, &pos);
    crbapi::get_cur_velocity(0, &vel, 1);

    crbapi::set_user_output1(0, torque_value, 1);
    crbapi::get_user_input1(0, get_torque_value, 1);

//    if (vel > 0){
//        K = a[0]*exp(b[0]*enc2) + c[0]*exp(d[0]*enc2);
//    K = a[0]*exp(b[0]*enc2) + c[0]*exp(d[0]*enc2);
//    }
//    else{
//        K = a[1]*exp(b[1]*enc2) + c[1]*exp(d[1]*enc2);
//    }
    K = p1*pow(enc2, 6) + p2*pow(enc2, 5) + p3*pow(enc2, 4) + p4*pow(enc2, 3) + p5*pow(enc2, 2) + p6*enc2 + p7;
    diff = enc1 - enc2;
    torque_cal = K*diff*ENC2DEG*DEG2RAD;

    return 0;
}

void set_torque(short value)
{
    tor_1 = value;
}

void set_torque_mode(long value){
    torque_mode[0] = value;
}

long get_torque()
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
