#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>

//#include "FileIO/fileio.h"
//#include "Numerical/numerical.h"

using namespace std;

class RobotArm
{
public:
    RobotArm(uint numbody, uint DOF);
    ~RobotArm();
	void run_DOB_DTP(double *qi, double *qi_dot, double *Ta, double *limit_p, double *limit_n, int *collision, double *r_hat);

private:
    inline void tilde(double *a, double *b) {
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
		double qi, qi_dot, qi_init;
		double mi, Ixx, Iyy, Izz, Ixy, Iyz, Izx;

		double ri[3], ri_dot[3], wi[3], rhoip[3], sijp[3], Jip[9], Cii[9], Cij[9], Ai_Cij[9], Cij_Aijpp[9], Ai_Cii[9];
        // Orientation
        double Aijpp[9], Ai[9], Hi[3], u_vec[3];
        // Position
        double sij[3], rhoi[3], ric[3], rit[9];
        // End point
		double Ce[9], sep[3], se[3], re[3], Ae[9], ori[3];
        // Velocity State
        double Bi[6], Yih[6];
        // Cartesian velocity state
        double Ti[36], wit[9], Yib[6], ric_dot[3];
        // Mass & Force
		double Jic[9], rict[9], rict_dot[9], Mih[36], fic[3], tic[3], Qih[6], Qih_g[6], Qih_c[6];
		double mi_rict[9], mi_rict_drict_wi[3], wit_Jic_wi[3], rict_dot_wi[3], Jic_wi[3], rict_fic[3], rict_rict_dot_wi[3], rict_rict[9], Ai_Cii_Jip[9];
        // Velocity Coupling
		double rit_dot[9], Hi_dot[3], Di[6], rit_dot_Hi[3], rit_Hi_dot[3], Di_sum[6];
        // System EQM
		double Ki[36], Li[6], Li_g[6], Li_c[6], Ki_Di[6], Ki_Bi[6], Ki_Di_sum[6], temp_Bi_Ki_Bi;
        // Acceleration
        double qi_ddot;
        // DOB residual
		double y, yp, Ta, r_hat, K, p_linear, p_rotate, p, y_old, yp_old, alpha;

    };
	double DH[6*4];
    void ang2mat(double ang_z1, double ang_x, double ang_z2, double* mat, bool deg_flag = true);
    double Rz1[9], Rx[9], Rz2[9], Rz1Rx[9];
	double R_yaw[9], R_pitch[9], R_roll[9], R_yaw_R_pitch[9];

	void mat(double *mat_1, double *mat_2, uint row_1, uint col_1, uint row_2, uint col_2, double *mat_3);
	void mat(double *mat_1, double *vec_2, uint row_1, uint col_1, uint row_2, double *vec_3);
	void mat2rpy(double mat[9], double ori[3]);

    uint num_body, dof;

    // system variable
    double h, t_current;
    double g;

    // EQM Mass & Force
	double M[36], Q_g[6], Q_c[6], Q[6];

	Body body[7];

    // High Pass Filter
    double w_cut, tau, tau_ts, a1, b0, b1, a2, b2, sum0;
    double f_cut;
    double time_zone[3];
    unsigned int filter_indx;
	double r_hat_filter[6];

    void kinematics();
    void dynamics();
    void residual();
    void high_pass_filter(double *cur, double *timeZone, double *cur_filter, double ts);
};

