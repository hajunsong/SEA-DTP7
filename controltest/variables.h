#ifndef VARIABLES_H
#define VARIABLES_H


#include "dob.h"

static int naxis;
static short tor_1 = 0;
static long int enc1 = 0, enc2 = 0, pos = 0, vel = 0;
static long torque_value[6] ={0,}; // sea torque value
static long torque_mode[6] = {0,}; // 0 = sea position mode, 1 = sea torque mode
static long get_torque_value[6] = {0,};

static double ENC2DEG = 360.0/262143.0;
static double DEG2RAD = M_PI/360.0;
static double VEL2RPM = 0.01;
static double RPM2DEG = 6;

static double dob_pos[6] = {0,}, dob_vel[6] = {0,}, dob_tor[6] = {0,};
static int collision[6] = {0,};
static DOB dob(6);
static double K = 0;

static double p1 = -2.955e-37;
static double p2 =  2.735e-31;
static double p3 = -1.027e-25;
static double p4 =  2.004e-20;
static double p5 = -2.152e-15;
static double p6 =  1.236e-10;
static double p7 = -3.358e-6;

static double diff = 0;
static double torque_cal = 0;

#endif // VARIABLES_H
