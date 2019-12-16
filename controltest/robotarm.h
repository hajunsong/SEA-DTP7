//#ifndef ROBOTARM_H
//#define ROBOTARM_H

////#include <QtCore/qglobal.h>

////#if defined(ROBOTARMLIB_LIBRARY)
////#  define ROBOTARMLIB_EXPORT Q_DECL_EXPORT
////#else
////#  define ROBOTARMLIB_EXPORT Q_DECL_IMPORT
////#endif

//#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <memory.h>
//#include <math.h>

////#include "numerical.h"

//using namespace std;

//class Body
//{
//public:
//	Body();
//	Body(double psi, double theta, double phi, double sijp_x, double sijp_y, double sijp_z);
//	~Body();

//	double qi, qi_dot, qi_ddot;
//	double mi, Ixx, Iyy, Izz, Ixy, Iyz, Izx;

//	// orientation
//	double Ai[9], Aijpp[9], Ai_Cij[9], Cij[9], u_vec[3];
//	// position
//	double sij[3], sijp[3], ri[3], re[3], Ae[9], re_dot[3], we[3], ori[3];
//	// jacobian
//	double Jvi[3], Jwi[3], re_qi[3], Ae_qi[9], r6_qi[3], A6_qi[9], Ae_qi_Cij[9], Ae_qi_Cij_Aijpp[9], Aijpp_qi[9], Cij_Aijpp[9], Ai_Cij_Aijpp_qi[9], Ae_qi_sijp[3], Ae_qi_end[3];
//	double Ae_qi_31, Ae_qi_32, Ae_qi_33, Ae_qi_21, Ae_qi_11, roll_qi_1, roll_qi_2, roll_qi, pitch_qi_1, pitch_qi_2, pitch_qi, yaw_qi_1, yaw_qi_2, yaw_qi;
//	double oi[3], zi[3], zit[9];
//	// velocity state
//	double Hi[3], rit[9], Bi[6], Yih[6];
//	// cartesian velocity
//	double Ti[36], Yib[6], ri_dot[3], wi[3], wit[9], rhoip[3], rhoi[3], ric[3], ric_dot[3];
//	// mass & force
//	double Cii[9], Ai_Cii[9], Jic[9], Jip[9], rit_dot[9], rict_dot[9], rict[9], Mih[36], fic[3], tic[3], Qih[6], Qih_g[6], Qih_c[6];
//	// velocity coupling
//	double Hi_dot[3], Di[6], Di_sum[6];
//	// system EQM
//	double Ki[36], Li[6], Li_g[6], Li_c[6], Ki_Di[6], Ki_Di_sum[6];
//	// DOB residual
//	double y, yp, Ta, r_hat, K, p_linear, p_rotate, p, y_old, yp_old, alpha;

//	static void ang2mat(double ang_z1, double ang_x, double ang_z2, double* mat, bool deg_flag = true);
//};

//class RobotArm
//{
//public:
//	RobotArm(uint numbody, uint DOF);
//	~RobotArm();
//	void run_DOB_DTP(double *qi, double *qi_dot, double *Ta, double *r_hat, int *collision);

//	static void mat(double *mat_1, double *mat_2, uint row_1, uint col_1, uint row_2, uint col_2, double *mat_3);
//	static void mat(double *mat_1, double *vec_2, uint row_1, uint col_1, uint row_2, double *vec_3);

//	static void rpy2mat(double yaw, double pitch, double roll, double *mat);
//	static void mat2rpy(double mat[9], double ori[3]);

//private:
//	inline void tilde(double *a, double *b) {
//		*(b++) = 0;	*(b++) = -a[2];	*(b++) = a[1];
//		*(b++) = a[2];	*(b++) = 0;	*(b++) = -a[0];
//		*(b++) = -a[1];	*(b++) = a[0];	*(b++) = 0;
//	}

//	double DH[6*4];

//	uint num_body, dof;

//	// system variable
//	double h, t_current;
//	double g;

//	// EQM Mass & Force
//	double M[36], Q_g[6], Q_c[6], Q[6];

//	Body body[7];

//	// High Pass Filter
//	double w_cut, tau, tau_ts, a1, b0, b1, a2, b2, sum0;
//	double f_cut;
//	double time_zone[3];
//	unsigned int filter_indx;
//	double r_hat_filter[6];

//	void kinematics();
//	void dynamics();
//	void residual();
//	void high_pass_filter(double *cur, double *timeZone, double *cur_filter, double ts);
//};

//#endif // ROBOTARM_H
