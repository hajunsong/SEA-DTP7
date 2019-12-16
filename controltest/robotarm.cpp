#include "robotarm.h"

RobotArm::Body::Body(){}

RobotArm::Body::~Body(){}

void RobotArm::ang2mat(double ang_z1, double ang_x, double ang_z2, double *mat, bool deg_flag)
{
    double z1, x, z2;
    if (deg_flag){
        z1 = ang_z1*M_PI/180.0;
        x = ang_x*M_PI/180.0;
        z2 = ang_z2*M_PI/180.0;
    }
    else{
        z1 = ang_z1;
        x = ang_x;
        z2 = ang_z2;
    }

    Rz1[0] = cos(z1);   Rz1[1] = -sin(z1);  Rz1[2] = 0;
    Rz1[0] = sin(z1);   Rz1[1] =  cos(z1);  Rz1[2] = 0;
    Rz1[0] = 0;         Rz1[1] = 0;         Rz1[2] = 1;

    Rx[0] = 1;          Rx[1] = cos(x);     Rx[2] = -sin(x);
    Rx[0] = 0;          Rx[1] = sin(x);     Rx[2] = cos(x);
    Rx[0] = 0;          Rx[1] = 0;          Rx[2] = 1;

    Rz2[0] = cos(z2);   Rz2[1] = -sin(z2);  Rz2[2] = 0;
    Rz2[0] = sin(z2);   Rz2[1] =  cos(z2);  Rz2[2] = 0;
    Rz2[0] = 0;         Rz2[1] = 0;         Rz2[2] = 1;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            Rz1Rx[i*3+j] = 0;
            for(int k = 0; k < 3; k++){
                Rz1Rx[i*3+j] += Rz1[i*3+k]*Rx[k*3+j];
            }
        }
    }

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            mat[i*3+j] = 0;
            for(int k = 0; k < 3; k++){
                mat[i*3+j] += Rz1Rx[i*3+k]*Rz2[k*3+j];
            }
        }
    }
}


void RobotArm::mat(double *mat_1, double *mat_2, uint row_1, uint col_1, uint row_2, uint col_2, double *mat_3){
	if (col_1 != row_2){
		printf("please check matrix size\n");
		return;
	}

	for(uint i = 0; i < row_1; i++){
		for(uint j = 0; j < col_2; j++){
			mat_3[i*col_2 + j] = 0;
			for(uint k = 0; k < row_2; k++){
				mat_3[i*col_2 + j] += mat_1[i*col_1 + k]*mat_2[k*col_2 + j];
			}
		}
	}
}

void RobotArm::mat(double *mat_1, double *vec_2, uint row_1, uint col_1, uint row_2, double *vec_3){
	if (col_1 != row_2){
		printf("please check matrix size\n");
		return;
	}

	for(uint i = 0; i < row_1; i++){
		vec_3[i] = 0;
		for(uint j = 0; j < row_2; j++){
			vec_3[i] += mat_1[i*col_1 + j]*vec_2[j];
		}
	}
}

void RobotArm::mat2rpy(double mat[], double ori[])
{
	ori[0] = atan2(mat[2 * 3 + 1], mat[2 * 3 + 2]);
	ori[1] = atan2(-mat[2 * 3 + 0], sqrt(pow(mat[2 * 3 + 1], 2.0) + pow(mat[2 * 3 + 2], 2.0)));
	ori[2] = atan2(mat[1 * 3 + 0], mat[0 * 3 + 0]);
}

RobotArm::RobotArm(uint numbody, uint DOF) {
	num_body = numbody;
	dof = DOF;

	h = 0.004;
	g = -9.80665;

	// DH paramter
	// | Link | alpha(deg) |  a(mm)  |  d(mm)   | theta(deg) |
	// |=====================================================|
	// |  1   |     90     |    0    |    81    |     90     |
	// |  2   |    180     |  440    |     0    |     90     |
	// |  3   |    180     |  453.3  |     0    |      0     |
	// |  4   |    -90     |    0    |   113.3  |    -90     |
	// |  5   |     90     |    0    |   107    |      0     |
	// |  6   |      0     |    0    |    31.7  |      0     |

	DH[0] = 90;     DH[1] = 0;        DH[2] = 0.081;      DH[3] = 90;
	DH[4] = 180;    DH[5] = 0.440;    DH[6] = 0;          DH[7] = 90;
	DH[8] = 180;    DH[9] = 0.4533;   DH[10] = 0;         DH[11] = 0;
	DH[12] = -90;   DH[13] = 0;		  DH[14] = 0.1133;    DH[15] = -90;
	DH[16] = 90;    DH[17] = 0;       DH[18] = 0.107;	  DH[19] = 0;
	DH[20] = 0;     DH[21] = 0;       DH[22] = 0.0317;    DH[23] = 0;

	// body 0 variable
	body[0].Ai[0] = 1; body[0].Ai[1] = 0; body[0].Ai[2] = 0;
	body[0].Ai[3] = 0; body[0].Ai[4] = 1; body[0].Ai[5] = 0;
	body[0].Ai[6] = 0; body[0].Ai[7] = 0; body[0].Ai[8] = 1;

	body[0].ri[0] = 0; body[0].ri[1] = 0; body[0].ri[2] = 0;

	// preliminary work
	memset(body[0].Yih, 0, sizeof(double)*6);
	memset(body[0].wi, 0, sizeof(double)*3);
	memset(body[0].wit, 0, sizeof(double)*9);

	ang2mat(0, 0, 0, body[0].Cij);
	body[0].sijp[0] = 0; body[0].sijp[1] = 0; body[0].sijp[2] = 0;

	body[0].ri_dot[0] = 0; body[0].ri_dot[1] = 0; body[0].ri_dot[2] = 0;
	body[0].wi[0] = 0; body[0].wi[1] = 0; body[0].wi[2] = 0;

	body[0].u_vec[0] = 0; body[0].u_vec[1] = 0; body[0].u_vec[2] = 1;

	// body 1 variables
	ang2mat(DH[0*4+3], DH[0*4+0], 0, body[1].Cij);
	body[1].sijp[0] = 0; body[1].sijp[1] = 0; body[1].sijp[2] = DH[0*4+2];

	ang2mat(0, 0, 0, body[1].Cii, false);
	body[1].rhoip[0] = -0.0180406; body[1].rhoip[1] = -6.2926e-8; body[1].rhoip[2] = 0.0757967;
	body[1].mi = 11.9167793720014;
	body[1].Ixx = 2.27610950850461e-002;
	body[1].Iyy = 3.5418972763143e-002;
	body[1].Izz = 3.19095883117208e-002;
	body[1].Ixy = 1.35559483902745e-006;
	body[1].Iyz = 3.54913485300752e-007;
	body[1].Izx = 1.13533277840936e-003;
	body[1].Jip[0] = body[1].Ixx; body[1].Jip[1] = body[1].Ixy; body[1].Jip[2] = body[1].Izx;
	body[1].Jip[3] = body[1].Ixy; body[1].Jip[4] = body[1].Iyy; body[1].Jip[5] = body[1].Iyz;
	body[1].Jip[6] = body[1].Izx; body[1].Jip[7] = body[1].Iyz; body[1].Jip[8] = body[1].Izz;
	body[1].u_vec[0] = 0; body[1].u_vec[1] = 0; body[1].u_vec[2] = 1;

	body[1].r_hat = 0;
	body[1].y = 0;
	body[1].yp = 0;
	body[1].K = 100;
	body[1].p_linear = 0;
	body[1].p_rotate = 0;
	body[1].p = 0;
	body[1].y_old = 0;
	body[1].yp_old = 0;

	// body 2 variables
	ang2mat(DH[1*4+3], DH[1*4+0], 0, body[2].Cij);
	body[2].sijp[0] = 0; body[2].sijp[1] = DH[1*4+1]; body[2].sijp[2] = 0;

	ang2mat(M_PI, M_PI_2, M_PI_2, body[2].Cii, false);
	body[2].rhoip[0] = -2.057e-10; body[2].rhoip[1] = 0.207743; body[2].rhoip[2] = 0.0923849;
	body[2].mi = 5.91522581064282;
	body[2].Ixx = 0.150219939704306;
	body[2].Iyy = 0.148668778983352;
	body[2].Izz = 1.15613404663615e-002;
	body[2].Ixy = 6.86059498600652e-011;
	body[2].Iyz = 2.46067046230363e-010;
	body[2].Izx = 6.53465633751484e-005;
	body[2].Jip[0] = body[2].Ixx; body[2].Jip[1] = body[2].Ixy; body[2].Jip[2] = body[2].Izx;
	body[2].Jip[3] = body[2].Ixy; body[2].Jip[4] = body[2].Iyy; body[2].Jip[5] = body[2].Iyz;
	body[2].Jip[6] = body[2].Izx; body[2].Jip[7] = body[2].Iyz; body[2].Jip[8] = body[2].Izz;
	body[2].u_vec[0] = 0; body[2].u_vec[1] = 0; body[2].u_vec[2] = 1;

	body[2].r_hat = 0;
	body[2].y = 0;
	body[2].yp = 0;
	body[2].K = 100;
	body[2].p_linear = 0;
	body[2].p_rotate = 0;
	body[2].p = 0;
	body[2].y_old = 0;
	body[2].yp_old = 0;

	// body 3 variables
	ang2mat(DH[2*4+3], DH[2*4+0], 0, body[3].Cij);
	body[3].sijp[0] = DH[2*4+1]; body[3].sijp[1] = 0; body[3].sijp[2] = 0;

	ang2mat(M_PI_2, M_PI_2, -M_PI_2, body[3].Cii, false);
	body[3].rhoip[0] = 0.215869; body[3].rhoip[1] = -2.23777e-6; body[3].rhoip[2] = 0.0100272;
	body[3].mi = 15.7745199951742;
	body[3].Ixx = 0.695197497551249;
	body[3].Iyy = 0.706849566041388;
	body[3].Izz = 3.02102059259175e-002;
	body[3].Ixy = 2.94021005583699e-006;
	body[3].Iyz = 5.35647222952727e-006;
	body[3].Izx = 5.11048617923188e-003;
	body[3].Jip[0] = body[3].Ixx; body[3].Jip[1] = body[3].Ixy; body[3].Jip[2] = body[3].Izx;
	body[3].Jip[3] = body[3].Ixy; body[3].Jip[4] = body[3].Iyy; body[3].Jip[5] = body[3].Iyz;
	body[3].Jip[6] = body[3].Izx; body[3].Jip[7] = body[3].Iyz; body[3].Jip[8] = body[3].Izz;
	body[3].u_vec[0] = 0; body[3].u_vec[1] = 0; body[3].u_vec[2] = 1;

	body[3].r_hat = 0;
	body[3].y = 0;
	body[3].yp = 0;
	body[3].K = 100;
	body[3].p_linear = 0;
	body[3].p_rotate = 0;
	body[3].p = 0;
	body[3].y_old = 0;
	body[3].yp_old = 0;

	// body 4 variables
	ang2mat(DH[3*4+3], DH[3*4+0], 0, body[4].Cij);
	body[4].sijp[0] = 0; body[4].sijp[1] = 0; body[4].sijp[2] = DH[3*4+2];

	ang2mat(M_PI_2, M_PI_2, M_PI_2, body[4].Cii, false);
	body[4].rhoip[0] = -0.0199333; body[4].rhoip[1] = -5.23401e-6; body[4].rhoip[2] = 0.101482;
	body[4].mi = 6.7196578180871;
	body[4].Ixx = 1.17459661570413e-002;
	body[4].Iyy = 1.43854322196243e-002;
	body[4].Izz = 1.05565233283315e-002;
	body[4].Ixy = 2.00009271584939e-006;
	body[4].Iyz = -2.9988452577468e-006;
	body[4].Izx = 1.58251070450099e-003;
	body[4].Jip[0] = body[4].Ixx; body[4].Jip[1] = body[4].Ixy; body[4].Jip[2] = body[4].Izx;
	body[4].Jip[3] = body[4].Ixy; body[4].Jip[4] = body[4].Iyy; body[4].Jip[5] = body[4].Iyz;
	body[4].Jip[6] = body[4].Izx; body[4].Jip[7] = body[4].Iyz; body[4].Jip[8] = body[4].Izz;
	body[4].u_vec[0] = 0; body[4].u_vec[1] = 0; body[4].u_vec[2] = 1;

	body[4].r_hat = 0;
	body[4].y = 0;
	body[4].yp = 0;
	body[4].K = 100;
	body[4].p_linear = 0;
	body[4].p_rotate = 0;
	body[4].p = 0;
	body[4].y_old = 0;
	body[4].yp_old = 0;

	// body 5 variables
	ang2mat(DH[4*4+3], DH[4*4+0], 0, body[5].Cij);
	body[5].sijp[0] = 0; body[5].sijp[1] = 0; body[5].sijp[2] = DH[4*4+2];

	ang2mat(-M_PI_2, 0, 0, body[5].Cii, false);
	body[5].rhoip[0] = -5.23401e-6; body[5].rhoip[1] = 0.0199333; body[5].rhoip[2] = 0.0951822;
	body[5].mi = 6.71965781808711;
	body[5].Ixx = 1.05565233283315e-002;
	body[5].Iyy = 1.43854322196243e-002;
	body[5].Izz = 1.17459661570412e-002;
	body[5].Ixy = 2.99884525754771e-006;
	body[5].Iyz = -2.00009271580534e-006;
	body[5].Izx = 1.58251070450104e-003;
	body[5].Jip[0] = body[5].Ixx; body[5].Jip[1] = body[5].Ixy; body[5].Jip[2] = body[5].Izx;
	body[5].Jip[3] = body[5].Ixy; body[5].Jip[4] = body[5].Iyy; body[5].Jip[5] = body[5].Iyz;
	body[5].Jip[6] = body[5].Izx; body[5].Jip[7] = body[5].Iyz; body[5].Jip[8] = body[5].Izz;
	body[5].u_vec[0] = 0; body[5].u_vec[1] = 0; body[5].u_vec[2] = 1;

	body[5].r_hat = 0;
	body[5].y = 0;
	body[5].yp = 0;
	body[5].K = 100;
	body[5].p_linear = 0;
	body[5].p_rotate = 0;
	body[5].p = 0;
	body[5].y_old = 0;
	body[5].yp_old = 0;

	// body 6 variables
	ang2mat(DH[5*4+3], DH[5*4+0], 0, body[6].Cij);
	body[6].sijp[0] = 0; body[6].sijp[1] = 0; body[6].sijp[2] = DH[5*4+2];

	ang2mat(M_PI, M_PI_2, M_PI_2, body[6].Cii, false);
	body[6].rhoip[0] = -2e-15; body[6].rhoip[1] = 0.0649685; body[6].rhoip[2] = 0.0983587;
	body[6].mi = 4.37437692243246;
	body[6].Ixx = 9.77371282823288e-003;
	body[6].Iyy = 1.12391000495402e-002;
	body[6].Izz = 3.89214117851027e-003;
	body[6].Ixy = -6.78529393879376e-017;
	body[6].Iyz = -2.20245674018812e-017;
	body[6].Izx = -1.80216958139833e-003;
	body[6].Jip[0] = body[6].Ixx; body[6].Jip[1] = body[6].Ixy; body[6].Jip[2] = body[6].Izx;
	body[6].Jip[3] = body[6].Ixy; body[6].Jip[4] = body[6].Iyy; body[6].Jip[5] = body[6].Iyz;
	body[6].Jip[6] = body[6].Izx; body[6].Jip[7] = body[6].Iyz; body[6].Jip[8] = body[6].Izz;
	body[6].u_vec[0] = 0; body[6].u_vec[1] = 0; body[6].u_vec[2] = 1;

	body[6].r_hat = 0;
	body[6].y = 0;
	body[6].yp = 0;
	body[6].K = 100;
	body[6].p_linear = 0;
	body[6].p_rotate = 0;
	body[6].p = 0;
	body[6].y_old = 0;
	body[6].yp_old = 0;

	f_cut = 500;
	memset(time_zone, 0, sizeof(double)*3);
	filter_indx = 0;
}

RobotArm::~RobotArm() {
}

void RobotArm::run_DOB_DTP(double *qi, double *qi_dot, double *Ta, double *limit_p, double *limit_n, int *collision, double *r_hat){
	for(int i = 0; i < 6; i++){
		body[i + 1].qi = 0;//qi[i];
		body[i + 1].qi_dot = 0;//qi_dot[i];
		body[i + 1].Ta = 0;//Ta[i];
	}

	kinematics();
	dynamics();
	residual();

	for(int i = 0; i < 6; i++){
		r_hat[i] = 0;//body[i + 1].r_hat;
	}

	high_pass_filter(r_hat, time_zone, r_hat_filter, h);

	for(unsigned int i = 0; i < num_body; i++){
		if (r_hat_filter[i] > limit_p[i] || r_hat_filter[i] < limit_n[i]){
			collision[i] = 1;
		}
		else{
			collision[i] = 0;
		}
	}

	for(unsigned int i = 0; i < num_body; i++){
		r_hat[i] = r_hat_filter[i];
		collision[i] = static_cast<int>(r_hat_filter[i]*1000);
	}
}

void RobotArm::kinematics()
{
	for (uint indx = 1; indx <= num_body; indx++) {
		// orientation
		body[indx].Aijpp[0] = cos(body[indx].qi);	body[indx].Aijpp[1] = -sin(body[indx].qi);	body[indx].Aijpp[2] = 0;
		body[indx].Aijpp[3] = sin(body[indx].qi);	body[indx].Aijpp[4] = cos(body[indx].qi);	body[indx].Aijpp[5] = 0;
		body[indx].Aijpp[6] = 0;				body[indx].Aijpp[7] = 0;				body[indx].Aijpp[8] = 1;

		mat(body[indx-1].Ai, body[indx-1].Cij, 3, 3, 3, 3, body[indx].Ai_Cij);
		mat(body[indx].Ai_Cij, body[indx].Aijpp, 3, 3, 3, 3, body[indx].Ai);
//		mat(body[indx].Ai_Cij, body[indx].u_vec, 3, 3, 3, body[indx].zi);

		// position
		mat(body[indx-1].Ai, body[indx-1].sijp, 3, 3, 3, body[indx-1].sij);
		for (uint i = 0; i < 3; i++){
			body[indx].ri[i] = body[indx-1].ri[i] + body[indx-1].sij[i];
		}
	}

	// End point
//	body_end = &body[num_body];
	mat(body[num_body].Ai, body[num_body].sijp, 3, 3, 3, body[num_body].sij);
	for (uint i = 0; i < 3; i++){
		body[num_body].re[i] = body[num_body].ri[i] + body[num_body].sij[i];
	}

	mat(body[num_body].Ai, body[num_body].Cij, 3, 3, 3, 3, body[num_body].Ae);

	mat2rpy(body[num_body].Ae, body[num_body].ori);

//    body[num_body].ori[0] = atan2(body[num_body].Ae[2 * 3 + 1], body[num_body].Ae[2 * 3 + 2]);
//    body[num_body].ori[1] = atan2(-body[num_body].Ae[2 * 3 + 0], sqrt(pow(body[num_body].Ae[2 * 3 + 1], 2.0) + pow(body[num_body].Ae[2 * 3 + 2], 2.0)));
//    body[num_body].ori[2] = atan2(body[num_body].Ae[1 * 3 + 0], body[num_body].Ae[0 * 3 + 0]);
}

void RobotArm::dynamics(){
	for(uint indx = 1; indx <= num_body; indx++){
		// velocity state
		mat(body[indx].Ai_Cij, body[indx].u_vec, 3, 3, 3, body[indx].Hi);
		tilde(body[indx].ri, body[indx].rit);
		mat(body[indx].rit, body[indx].Hi, 3, 3, 3, body[indx].Bi);
		memcpy(body[indx].Bi + 3, body[indx].Hi, sizeof(double)*3);
		for (uint i = 0; i < 6; i++){
			body[indx].Yih[i] = body[indx-1].Yih[i] + body[indx].Bi[i]*body[indx].qi_dot;
		}

		// cartesian velocity
		for (uint i = 0; i < 3; i++){
			for(uint j = 0; j < 3; j++){
				body[indx].Ti[i*6 + j] = i == j ? 1 : 0;
				body[indx].Ti[(i + 3)*6 + (j + 3)] = i == j ? 1 : 0;
				body[indx].Ti[(i + 3)*6 + j] = 0;
				body[indx].Ti[i*6 + (j + 3)] = -body[indx].rit[i*3 + j];
			}
		}

		mat(body[indx].Ti, body[indx].Yih, 6, 6, 6, body[indx].Yib);
		memcpy(body[indx].ri_dot, body[indx].Yib, sizeof(double)*3);
		memcpy(body[indx].wi, body[indx].Yib + 3, sizeof(double)*3);
		tilde(body[indx].wi, body[indx].wit);
		mat(body[indx].Ai, body[indx].rhoip, 3, 3, 3, body[indx].rhoi);
		for(uint i = 0; i < 3; i++){
			body[indx].ric[i] = body[indx].ri[i] + body[indx].rhoi[i];
		}
		mat(body[indx].wit, body[indx].rhoi, 3, 3, 3, body[indx].ric_dot);
		for (uint i = 0; i < 3; i++){
			body[indx].ric_dot[i] += body[indx].ri_dot[i];
		}

		// mass & force
		mat(body[indx].Ai, body[indx].Cii, 3, 3, 3, 3, body[indx].Ai_Cii);
		mat(body[indx].Ai_Cii, body[indx].Jip, 3, 3, 3, 3, body[indx].Ai_Cii_Jip);
		for(uint i = 0; i < 3; i++){
			for(uint j = 0; j < 3; j++){
				body[indx].Jic[i*3 + j] = 0;
				for(uint k = 0; k < 3; k++){
					body[indx].Jic[i*3 + j] += body[indx].Ai_Cii_Jip[i*3 + k]*body[indx].Ai_Cii[j*3 + k];
				}
			}
		}
		tilde(body[indx].ri_dot, body[indx].rit_dot);
		tilde(body[indx].ric_dot, body[indx].rict_dot);
		tilde(body[indx].ric, body[indx].rict);
		mat(body[indx].rict, body[indx].rict, 3, 3, 3, 3, body[indx].rict_rict);
		for(uint i = 0; i < 3; i++){
			for(uint j = 0; j < 3; j++){
				body[indx].Mih[i*6 + j] = i == j ? body[indx].mi : 0;
				body[indx].Mih[(i + 3)*6 + j] = body[indx].mi*body[indx].rict[i*3 + j];
				body[indx].Mih[i*6 + (j + 3)] = -body[indx].mi*body[indx].rict[i*3 + j];
				body[indx].Mih[(i + 3)*6 + (j + 3)] = body[indx].Jic[i*3 + j] - body[indx].mi*body[indx].rict_rict[i*3 + j];
			}
		}
		body[indx].fic[0] = 0;
		body[indx].fic[1] = 0;
		body[indx].fic[2] = body[indx].mi*g;
		body[indx].tic[0] = 0;
		body[indx].tic[1] = 0;
		body[indx].tic[2] = 0;
		mat(body[indx].rict_dot, body[indx].wi, 3, 3, 3, body[indx].rict_dot_wi);
		for (uint i = 0; i < 3; i++){
			body[indx].Qih_g[i] = body[indx].fic[i];
			body[indx].Qih_c[i] = body[indx].mi*body[indx].rict_dot_wi[i];
			body[indx].Qih[i] = body[indx].Qih_g[i] + body[indx].Qih_c[i];
		}
		mat(body[indx].rict, body[indx].fic, 3, 3, 3, body[indx].rict_fic);
		mat(body[indx].rict, body[indx].rict_dot_wi, 3, 3, 3, body[indx].rict_rict_dot_wi);
		mat(body[indx].Jic, body[indx].wi, 3, 3, 3, body[indx].Jic_wi);
		mat(body[indx].wit, body[indx].Jic_wi, 3, 3, 3, body[indx].wit_Jic_wi);
		for (uint i = 0; i < 3; i++){
			body[indx].Qih_g[i + 3] = body[indx].rict_fic[i];
			body[indx].Qih_c[i + 3] = body[indx].mi*body[indx].rict_rict_dot_wi[i] - body[indx].wit_Jic_wi[i];
			body[indx].Qih[i + 3] = body[indx].tic[i] + body[indx].Qih_g[i + 3] + body[indx].Qih_c[i + 3];
		}

		// velocity coupling
		mat(body[indx-1].wit, body[indx].Hi, 3, 3, 3, body[indx].Hi_dot);
		mat(body[indx].rit_dot, body[indx].Hi, 3, 3, 3, body[indx].rit_dot_Hi);
		mat(body[indx].rit, body[indx].Hi_dot, 3, 3, 3, body[indx].rit_Hi_dot);
		for(uint i = 0; i < 3; i++){
			body[indx].Di[i] = (body[indx].rit_dot_Hi[i] + body[indx].rit_Hi_dot[i])*body[indx].qi_dot;
			body[indx].Di[i+3] = body[indx].Hi_dot[i]*body[indx].qi_dot;
		}

		memcpy(body[indx].Di_sum, body[indx].Di, sizeof(double)*6);
		for(uint indx2 = indx - 1; indx2 >= 1; indx2--){
			for(uint i = 0; i < 6; i++){
				body[indx].Di_sum[i] += body[indx2].Di[i];
			}
		}
	}

	// system EQM
	for(uint indx = num_body; indx >= 1;  indx--){
		if (indx == num_body){
			memcpy(body[indx].Ki, body[indx].Mih, sizeof(double)*36);
			memcpy(body[indx].Li, body[indx].Qih, sizeof(double)*6);
			memcpy(body[indx].Li_g, body[indx].Qih_g, sizeof(double)*6);
			memcpy(body[indx].Li_c, body[indx].Qih_c, sizeof(double)*6);
		}
		else{
			for(uint i = 0; i < 36; i++){
				body[indx].Ki[i] = body[indx].Mih[i] + body[indx + 1].Ki[i];
			}
			mat(body[indx + 1].Ki, body[indx + 1].Di, 6, 6, 6, body[indx + 1].Ki_Di);
			for(uint i = 0; i < 6; i++){
				body[indx].Li[i] = body[indx].Qih[i] + body[indx + 1].Li[i] - body[indx + 1].Ki_Di[i];
				body[indx].Li_g[i] = body[indx].Qih_g[i] + body[indx + 1].Li_g[i] - body[indx + 1].Ki_Di[i];
				body[indx].Li_c[i] = body[indx].Qih_c[i] + body[indx + 1].Li_c[i] - body[indx + 1].Ki_Di[i];
			}
		}
	}

	memset(Q, 0, sizeof(double)*num_body);
	memset(Q_g, 0, sizeof(double)*num_body);
	memset(Q_c, 0, sizeof(double)*num_body);
	for(uint indx = 1; indx <= num_body; indx++){
		mat(body[indx].Ki, body[indx].Di_sum, 6, 6, 6, body[indx].Ki_Di_sum);
		for(uint i = 0; i < 6; i++){
			Q[indx - 1] += body[indx].Bi[i]*(body[indx].Li[i] - body[indx].Ki_Di_sum[i]);
			Q_g[indx - 1] += body[indx].Bi[i]*(body[indx].Li_g[i] - body[indx].Ki_Di_sum[i]);
			Q_c[indx - 1] += body[indx].Bi[i]*(body[indx].Li_c[i] - body[indx].Ki_Di_sum[i]);
		}
	}

	memset(M, 0, sizeof(double)*num_body*num_body);
	for(uint indx = 1; indx <= num_body; indx++){
		for(uint indx2 = 1; indx2 <= num_body; indx2++){
			if (indx == indx2){
				mat(body[indx].Ki, body[indx].Bi, 6, 6, 6, body[indx].Ki_Bi);
			}
			else if(indx < indx2){
				mat(body[indx2].Ki, body[indx2].Bi, 6, 6, 6, body[indx].Ki_Bi);
			}
			else if(indx > indx2){
				mat(body[indx].Ki, body[indx2].Bi, 6, 6, 6, body[indx].Ki_Bi);
			}
			body[indx].temp_Bi_Ki_Bi = 0;
			for(uint i = 0; i < 6; i++){
				body[indx].temp_Bi_Ki_Bi += body[indx].Bi[i]*body[indx].Ki_Bi[i];
			}
			M[(indx - 1)*num_body + (indx2 - 1)] = body[indx].temp_Bi_Ki_Bi;
		}
	}
}

void RobotArm::residual(){
	for(uint indx = 1; indx <= num_body; indx++){
		body[indx].alpha = Q_g[indx] - Q_c[indx];
		body[indx].yp = body[indx].Ta + body[indx].alpha - body[indx].r_hat;

		body[indx].y = body[indx].y_old + body[indx].yp*h + 0.5*h*h*(body[indx].yp - body[indx].yp_old);
	}

	for(uint indx = 1; indx <= num_body; indx++){
		body[indx].p_linear = 0;
		for (uint j = 0; j < 3; j++) {
			body[indx].p_linear += pow(body[indx].ric_dot[j], 2);
		}
		body[indx].p_linear *= 0.5*body[indx].mi;
		body[indx].p_rotate = 0;
		for (uint j = 0; j < 3; j++) {
			body[indx].p_rotate += body[indx].wi[j] * body[indx].Jic_wi[j];
		}
		body[indx].p_rotate *= 0.5;
		body[indx].p = body[indx].p_linear + body[indx].p_rotate;
	}

	for(uint indx = 1; indx <= num_body; indx++){
		body[indx].r_hat = body[indx].K*(body[indx].y - body[indx].p);

		body[indx].y_old = body[indx].y;
		body[indx].yp_old = body[indx].yp;
	}

	t_current += h;
}

void RobotArm::high_pass_filter(double *cur, double *timeZone, double *cur_filter, double ts){
    w_cut = 2*M_PI*f_cut;
    tau = 1 / w_cut;
    tau_ts = 1/(tau + ts);
    a1 = -tau*tau_ts;
    b0 = tau*tau_ts;
    b1 = -tau*tau_ts;
    a2 = 0;
    b2 = 0;
    sum0 = 0;

    sum0 = -a1*timeZone[1] - a2*timeZone[0];
    timeZone[2] = cur[0] + sum0;
    cur_filter[0] = b0*timeZone[2] + b1*timeZone[1] + b2*timeZone[0];

    timeZone[0] = timeZone[1];
    timeZone[1] = timeZone[2];
}

