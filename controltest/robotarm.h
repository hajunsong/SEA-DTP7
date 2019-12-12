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
    void run_DOB_DTP(double *qi, double *qi_dot, double *Ta, double *r_hat, double *r_hat_filter);

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
        double qi, qi_dot, mi, qi_init;
        double ri[3], ri_dot[3], wi[3], rhoip[3], sijp[3], Jip[9], Cii[9], Cij[9], Ai_Cij[9], Cij_Aijpp[9], Ai_Cii[9], Ai_Cii_Jip[9];
        // Orientation
        double Aijpp[9], Ai[9], Hi[3], u_vec[3];
        // Position
        double sij[3], rhoi[3], ric[3], rit[9];
        // End point
        double Ce[9], sep[3], se[3], re[3], Ae[9], roll, pitch, yaw;
        // Jacobian
        double Jvi[3], Jwi[3], re_qi[3], Ae_qi[9], r6_qi[3], A6_qi[9], Aijpp_qi[9];
        double Ae_qi_31, Ae_qi_32, Ae_qi_33, Ae_qi_21, Ae_qi_11, roll_qi, pitch_qi, yaw_qi;
        // Velocity State
        double Bi[6], Yih[6];
        // Cartesian velocity state
        double Ti[36], wit[9], Yib[6], ric_dot[3];
        // Mass & Force
        double Jic[9], rict[9], rict_dot[9], Mih[36], Fic[3], Tic[3], Qih[6], Qih_g[6], Qih_c[6], mi_rict[9], mi_rict_drict_wi[3], wit_Jic_wi[3], rict_dot_wi[3], Jic_wi[3];
        // Velocity Coupling
        double rit_dot[9], dHi[3], Di[6], rit_dot_Hi[3], rit_dHi[3];
        // System EQM
        double Ki[36], Li[6], Li_g[6], Li_c[6], Ki_Di[6], Ki_Bi[6];
        // Acceleration
        double qi_ddot;
        // DOB residual
        double y, yp, Ta, r_hat, K, p_linear, p_rotate, p, y_old, yp_old, alpha;

    };
    void ang2mat(double ang_z1, double ang_x, double ang_z2, double* mat, bool deg_flag = true);
    double Rz1[9], Rx[9], Rz2[9], Rz1Rx[9];

    uint num_body, dof;

    // system variable
    double h, t_current;
    double g;

    // EQM Mass & Force
    double M, Q_g, Q_c, Q;

    Body body[3];

    // High Pass Filter
    double w_cut, tau, tau_ts, a1, b0, b1, a2, b2, sum0;
    double f_cut;
    double time_zone[3];
    unsigned int filter_indx;

    void kinematics();
    void dynamics();
    void systemEQM();
    void residual();
    void high_pass_filter(double *cur, double *timeZone, double *cur_filter, double ts);
};

