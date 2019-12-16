#ifndef VARIABLES_H
#define VARIABLES_H


#include "robotarm.h"
#include "cuiapi.h"

#include <math.h>

static long int pos[6] = {0,}, vel[6] = {0,}, enc_diff[6] = {0,};
static double diff[6] = {0,};
static double actual_torque[6] = {0,}, k[6] = {696.602,};
static double r_hat_limit_p[6] = {10,};
static double r_hat_limit_n[6] = {-10,};
static int collision[6] = {0,};
static double pos_rad[6] = {0,}, vel_rad[6] = {0,};
static double offset[6] = {38.139,};
static double r_hat[6] = {0,};

static double ENC2DEG = 360.0/262143.0;
static double DEG2RAD = M_PI/180.0;
static double RAD2DEG = 180.0/M_PI;
static double VEL2RPM = 0.01;
static double RPM2DEG = 6;

static RobotArm robot(6,6);

static bool flag = false;
static const int data_cnt = 5;
static const unsigned int max_indx = 100;
static unsigned int indx;
struct TP_data{
	unsigned int indx;
	double pos[6], vel[6], tor[6], r_hat[6];
};
static TP_data tpData[max_indx];

static CUIApp* capp = CUIApp::getInstance();

#endif // VARIABLES_H
