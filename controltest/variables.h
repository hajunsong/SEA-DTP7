#ifndef VARIABLES_H
#define VARIABLES_H


#include "robotarm.h"
#include "cuiapi.h"

//#include <math.h>

static long int pos[6] = {0,}, vel[6] = {0,}, enc_diff[6] = {0,};
static float diff[6] = {0,};
static float actual_torque[6] = {0,};
static float k[6] = {3307.0f,3786.0f,3307.0f,1122.0f,1122.0f,1122.0f}; // 20 : 1122, 60 : 3307, 100 : 3786
static float r_hat_limit_p[6] = {0.102, 0.479, 0.149, 0.652, 0.421, 3.147};
static float r_hat_limit_n[6] = {-0.135, -0.467, -0.126, -0.639, -0.403, -3.037};
static int collision[12] = {0,};
static float pos_rad[6] = {0,}, vel_rad[6] = {0,};
static float offset[6] = {48279, 170, -22246, -65879, -4994, -115157};
static float r_hat[6] = {0,};
static bool coll_flag = false;

static float ENC2DEG = 360.0f/262143.0f;
static float DEG2RAD = PI/180.0f;
static float RAD2DEG = 180.0f/PI;
static float VEL2RPM = 0.01f;
static float RPM2DEG = 6;

static RobotArm robot(6,6);

static bool flag = false;
static const int data_cnt = 5;
static const unsigned int max_indx = 100;
static unsigned int indx;
struct TP_data{
	unsigned int indx;
	float pos[6], vel[6], tor[6], r_hat[6];
};
static TP_data tpData[max_indx];

static CUIApp* capp = CUIApp::getInstance();

#endif // VARIABLES_H
