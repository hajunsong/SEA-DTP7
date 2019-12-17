#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>

//#include "FileIO/fileio.h"
//#include "Numerical/numerical.h"

const float PI = 3.14159265358979323846f;	/* pi */
const float PI_2 = 1.57079632679489661923f;	/* pi/2 */

using namespace std;

class RobotArm
{
public:
    RobotArm(uint numbody, uint DOF);
    ~RobotArm();
	void run_DOB_DTP(float *qi, float *qi_dot, float *Ta, float *limit_p, float *limit_n, int *collision, float *r_hat);
	void run_dynamics(float *qi, float *qi_dot);
	void get_M(float *M_req);
	void get_Q(float *Q_req);

private:
	inline void tilde(float *a, float *b) {
        *(b++) = 0;	*(b++) = -a[2];	*(b++) = a[1];
        *(b++) = a[2];	*(b++) = 0;	*(b++) = -a[0];
        *(b++) = -a[1];	*(b++) = a[0];	*(b++) = 0;
    }

    class Body
    {
    public:
        Body();
        ~Body();
        // body initial data
		float qi, qi_dot, qi_init;
		float mi, Ixx, Iyy, Izz, Ixy, Iyz, Izx;

		float ri[3], ri_dot[3], wi[3], rhoip[3], sijp[3], Jip[9], Cii[9], Cij[9], Ai_Cij[9], Cij_Aijpp[9], Ai_Cii[9];
        // Orientation
		float Aijpp[9], Ai[9], Hi[3], u_vec[3];
        // Position
		float sij[3], rhoi[3], ric[3], rit[9];
        // End point
		float Ce[9], sep[3], se[3], re[3], Ae[9], ori[3];
        // Velocity State
		float Bi[6], Yih[6];
        // Cartesian velocity state
		float Ti[36], wit[9], Yib[6], ric_dot[3];
        // Mass & Force
		float Jic[9], rict[9], rict_dot[9], Mih[36], fic[3], tic[3], Qih[6], Qih_g[6], Qih_c[6];
		float mi_rict[9], mi_rict_drict_wi[3], wit_Jic_wi[3], rict_dot_wi[3], Jic_wi[3], rict_fic[3], rict_rict_dot_wi[3], rict_rict[9], Ai_Cii_Jip[9];
        // Velocity Coupling
		float rit_dot[9], Hi_dot[3], Di[6], rit_dot_Hi[3], rit_Hi_dot[3], Di_sum[6];
        // System EQM
		float Ki[36], Li[6], Li_g[6], Li_c[6], Ki_Di[6], Ki_Bi[6], Ki_Di_sum[6], temp_Bi_Ki_Bi;
        // Acceleration
		float qi_ddot;
        // DOB residual
		float y, yp, Ta, r_hat, K, p_linear, p_rotate, p, y_old, yp_old, alpha, f_cut, time_zone[3], r_hat_filter;
		int filter_indx;

    };
	float DH[6*4];
//	void ang2mat(float ang_z1, float ang_x, float ang_z2, float* mat, bool deg_flag = true);
//    float Rz1[9], Rx[9], Rz2[9], Rz1Rx[9];
	float R_yaw[9], R_pitch[9], R_roll[9], R_yaw_R_pitch[9];

	void mat(float *mat_1, float *mat_2, uint row_1, uint col_1, uint row_2, uint col_2, float *mat_3);
	void mat(float *mat_1, float *vec_2, uint row_1, uint col_1, uint row_2, float *vec_3);
	void mat2rpy(float mat[9], float ori[3]);

    uint num_body, dof;

    // system variable
	float h, t_current;
	float g;

    // EQM Mass & Force
	float M[36], Q_g[6], Q_c[6], Q[6];

	Body body[7];

    // High Pass Filter
	float w_cut, tau, tau_ts, a1, b0, b1, a2, b2, sum0;
    unsigned int filter_indx;

    void kinematics();
    void dynamics();
    void residual();
	void high_pass_filter(float cur, float *timeZone, float cur_filter, float ts, float f_cut);
};

