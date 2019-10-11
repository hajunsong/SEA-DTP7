#ifndef VARIABLES_H
#define VARIABLES_H


#include "dob.h"
#include "cuiapi.h"

static int naxis;
static short tor_1 = 0;
static long int enc1 = 0, enc2 = 0, pos = 0, vel = 0, enc_diff = 0;
static short torque_value[6] ={0,}; // sea torque value
static long torque_mode[6] = {0,}; // 0 = sea position mode, 1 = sea torque mode
static short get_torque_value[6] = {0,};

static double ENC2DEG = 360.0/262143.0;
static double DEG2RAD = M_PI/180.0;
static double RAD2DEG = 180.0/M_PI;
static double VEL2RPM = 0.01;
static double RPM2DEG = 6;

//static double dob_pos[1] = {0,}, dob_vel[1] = {0,}, dob_tor[1] = {0,};
static int collision[1] = {0,};
static DOB dob(1);
//static double K = 0;

static double diff = 0, diff_ang = 0, diff_rad = 0;
static double torque_cal = 0;
static double pos_deg = 0, pos_rad = 0;
static double vel_deg = 0, vel_rad = 0, vel_rpm = 0;
static double actual_torque = 0, k = 696.602;
const int data_cnt = 5;
static double TP_data[data_cnt] = {0,};
static double des_vel = 5*RPM2DEG*DEG2RAD, err_vel = 0, err_vel_accum = 0, err_vel_prev = 0, h = 0.002;
static double Kp_vel = 9000, Kd_vel = 0, Ki_vel = 100;
static double T_control = 0;
static bool flag = false;

static int sdoIndex = 0;
static unsigned long sdoSetData = 0;
static unsigned long sdoGetData = 0;
static unsigned long goal_vel = 2700; // [0.01 RPM]

static CUIApp* capp = CUIApp::getInstance();

static int sdoIndexGoalVel = 0x02280020;
static int sdoIndexTorqueEnable = 0x02000008;
static int sdoIndexOperatingMode = 0x000b0008;
static long sdoSetDataGoalVel = 2700;

static bool turn_on = false, turn_off = false;

static int delay = 0;

#endif // VARIABLES_H
