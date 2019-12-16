#include "robotarm.h"

#include "robotarm.h"

Body::Body(){}

Body::~Body(){}

void Body::ang2mat(double ang_z1, double ang_x, double ang_z2, double *mat, bool deg_flag)
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

	double Rz1[9] = {cos(z1), -sin(z1), 0, sin(z1), cos(z1), 0, 0, 0, 1};
	double Rx[9] = {1, 0, 0, 0, cos(x), -sin(x), 0, sin(x), cos(x)};
	double Rz2[9] = {cos(z2), -sin(z2), 0, sin(z2), cos(z2), 0, 0, 0, 1};
	double Rz1Rx[9] = {0,};
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
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

	double temp;
	for(uint i = 0; i < row_1; i++){
		for(uint j = 0; j < col_2; j++){
			temp = 0;
			for(uint k = 0; k < row_2; k++){
				temp += mat_1[i*col_1 + k]*mat_2[k*col_2 + j];
			}
			mat_3[i*col_2 + j] = temp;
		}
	}
}

void RobotArm::mat(double *mat_1, double *vec_2, uint row_1, uint col_1, uint row_2, double *vec_3){
	if (col_1 != row_2){
		printf("please check matrix size\n");
		return;
	}

	double temp;
	for(uint i = 0; i < row_1; i++){
		temp = 0;
		for(uint j = 0; j < row_2; j++){
			temp += mat_1[i*col_1 + j]*vec_2[j];
		}
		vec_3[i] = temp;
	}
}

void RobotArm::rpy2mat(double yaw, double pitch, double roll, double *mat)
{
	double R_yaw[9] = {cos(yaw), -sin(yaw), 0, sin(yaw), cos(yaw), 0, 0, 0, 1};
	double R_pitch[9] = {cos(pitch), 0, sin(pitch), 0, 1, 0, -sin(pitch), 0, cos(pitch)};
	double R_roll[9] = {1, 0, 0, 0, cos(roll), -sin(roll), 0, sin(roll), cos(roll)};
	double R_yaw_R_pitch[9] = {0,};
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			for(int k = 0; k < 3; k++){
				R_yaw_R_pitch[i*3+j] += R_yaw[i*3+k]*R_pitch[k*3+j];
			}
		}
	}

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			mat[i*3+j] = 0;
			for(int k = 0; k < 3; k++){
				mat[i*3+j] += R_yaw_R_pitch[i*3+k]*R_roll[k*3+j];
			}
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

	Body::ang2mat(0, 0, 0, body[0].Cij);
	body[0].sijp[0] = 0; body[0].sijp[1] = 0; body[0].sijp[2] = 0;

	body[0].ri_dot[0] = 0; body[0].ri_dot[1] = 0; body[0].ri_dot[2] = 0;
	body[0].wi[0] = 0; body[0].wi[1] = 0; body[0].wi[2] = 0;

	body[0].u_vec[0] = 0; body[0].u_vec[1] = 0; body[0].u_vec[2] = 1;

	// body 1 variables
	Body::ang2mat(DH[0*4+3], DH[0*4+0], 0, body[1].Cij);
	body[1].sijp[0] = 0; body[1].sijp[1] = 0; body[1].sijp[2] = DH[0*4+2];

	Body::ang2mat(0, 0, 0, body[1].Cii, false);
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

	// body 2 variables
	Body::ang2mat(DH[1*4+3], DH[1*4+0], 0, body[2].Cij);
	body[2].sijp[0] = 0; body[2].sijp[1] = DH[1*4+1]; body[2].sijp[2] = 0;

	Body::ang2mat(M_PI, M_PI_2, M_PI_2, body[2].Cii, false);
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

	// body 3 variables
	Body::ang2mat(DH[2*4+3], DH[2*4+0], 0, body[3].Cij);
	body[3].sijp[0] = DH[2*4+1]; body[3].sijp[1] = 0; body[3].sijp[2] = 0;

	Body::ang2mat(M_PI_2, M_PI_2, -M_PI_2, body[3].Cii, false);
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

	// body 4 variables
	Body::ang2mat(DH[3*4+3], DH[3*4+0], 0, body[4].Cij);
	body[4].sijp[0] = 0; body[4].sijp[1] = 0; body[4].sijp[2] = DH[3*4+2];

	Body::ang2mat(M_PI_2, M_PI_2, M_PI_2, body[4].Cii, false);
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

	// body 5 variables
	Body::ang2mat(DH[4*4+3], DH[4*4+0], 0, body[5].Cij);
	body[5].sijp[0] = 0; body[5].sijp[1] = 0; body[5].sijp[2] = DH[4*4+2];

	Body::ang2mat(-M_PI_2, 0, 0, body[5].Cii, false);
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

	// body 6 variables
	Body::ang2mat(DH[5*4+3], DH[5*4+0], 0, body[6].Cij);
	body[6].sijp[0] = 0; body[6].sijp[1] = 0; body[6].sijp[2] = DH[5*4+2];

	Body::ang2mat(M_PI, M_PI_2, M_PI_2, body[6].Cii, false);
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
}

RobotArm::~RobotArm() {
}

void RobotArm::run_DOB_DTP(double *qi, double *qi_dot, double *Ta, double *r_hat, int *collision){
	for(int i = 0; i < 1; i++){
		body[1].qi = qi[0];
		body[1].qi_dot = qi_dot[0];
		body[1].Ta = Ta[0];
	}

	kinematics();
	dynamics();
	residual();

	r_hat[0] = body[1].r_hat;
	high_pass_filter(r_hat, time_zone, r_hat_filter, h);

	for(unsigned int i = 0; i < num_body; i++){
		r_hat[i] = r_hat_filter[i];
	}

	for(unsigned int i = 0; i < num_body; i++){
		collision[i] = 1;
	}
}

void RobotArm::kinematics()
{
	Body *body0, *body1;
	for (uint indx = 1; indx <= num_body; indx++) {
		body0 = &body[indx - 1];
		body1 = &body[indx];
		// orientation
		double *Aijpp_ptr = body1->Aijpp;
		*(Aijpp_ptr++) = cos(body1->qi);	*(Aijpp_ptr++) = -sin(body1->qi);	*(Aijpp_ptr++) = 0;
		*(Aijpp_ptr++) = sin(body1->qi);	*(Aijpp_ptr++) = cos(body1->qi);	*(Aijpp_ptr++) = 0;
		*(Aijpp_ptr++) = 0;					*(Aijpp_ptr++) = 0;					*(Aijpp_ptr++) = 1;

		mat(body0->Ai, body0->Cij, 3, 3, 3, 3, body1->Ai_Cij);
		mat(body1->Ai_Cij, body1->Aijpp, 3, 3, 3, 3, body1->Ai);
		mat(body1->Ai_Cij, body1->u_vec, 3, 3, 3, body1->zi);

		// position
		mat(body0->Ai, body0->sijp, 3, 3, 3, body0->sij);
		for (uint i = 0; i < 3; i++){
			body1->ri[i] = body0->ri[i] + body0->sij[i];
		}
	}

	// End point
	Body *body_end = &body[num_body];
	mat(body_end->Ai, body_end->sijp, 3, 3, 3, body_end->sij);
	for (uint i = 0; i < 3; i++){
		body_end->re[i] = body_end->ri[i] + body_end->sij[i];
	}

	mat(body_end->Ai, body_end->Cij, 3, 3, 3, 3, body_end->Ae);

	mat2rpy(body_end->Ae, body_end->ori);

//    body_end->ori[0] = atan2(body_end->Ae[2 * 3 + 1], body_end->Ae[2 * 3 + 2]);
//    body_end->ori[1] = atan2(-body_end->Ae[2 * 3 + 0], sqrt(pow(body_end->Ae[2 * 3 + 1], 2.0) + pow(body_end->Ae[2 * 3 + 2], 2.0)));
//    body_end->ori[2] = atan2(body_end->Ae[1 * 3 + 0], body_end->Ae[0 * 3 + 0]);
}

void RobotArm::dynamics()
{
	Body *body0, *body1, *body2;
	for(uint indx = 1; indx <= num_body; indx++){
		body1 = &body[indx];
		body0 = &body[indx - 1];
		// velocity state
		mat(body1->Ai_Cij, body1->u_vec, 3, 3, 3, body1->Hi);
		tilde(body1->ri, body1->rit);
		mat(body1->rit, body1->Hi, 3, 3, 3, body1->Bi);
		memcpy(body1->Bi + 3, body1->Hi, sizeof(double)*3);
		for (uint i = 0; i < 6; i++){
			body1->Yih[i] = body0->Yih[i] + body1->Bi[i]*body1->qi_dot;
		}

		// cartesian velocity
		for (uint i = 0; i < 3; i++){
			for(uint j = 0; j < 3; j++){
				body1->Ti[i*6 + j] = i == j ? 1 : 0;
				body1->Ti[(i + 3)*6 + (j + 3)] = i == j ? 1 : 0;
				body1->Ti[(i + 3)*6 + j] = 0;
				body1->Ti[i*6 + (j + 3)] = -body1->rit[i*3 + j];
			}
		}

		mat(body1->Ti, body1->Yih, 6, 6, 6, body1->Yib);
		memcpy(body1->ri_dot, body1->Yib, sizeof(double)*3);
		memcpy(body1->wi, body1->Yib + 3, sizeof(double)*3);
		tilde(body1->wi, body1->wit);
		mat(body1->Ai, body1->rhoip, 3, 3, 3, body1->rhoi);
		for(uint i = 0; i < 3; i++){
			body1->ric[i] = body1->ri[i] + body1->rhoi[i];
		}
		mat(body1->wit, body1->rhoi, 3, 3, 3, body1->ric_dot);
		for (uint i = 0; i < 3; i++){
			body1->ric_dot[i] += body1->ri_dot[i];
		}

		// mass & force
		mat(body1->Ai, body1->Cii, 3, 3, 3, 3, body1->Ai_Cii);
		double temp[9] = {0,}, temp2 = 0;
		mat(body1->Ai_Cii, body1->Jip, 3, 3, 3, 3, temp);
		for(uint i = 0; i < 3; i++){
			for(uint j = 0; j < 3; j++){
				temp2 = 0;
				for(uint k = 0; k < 3; k++){
					temp2 += temp[i*3 + k]*body1->Ai_Cii[j*3 + k];
				}
				body1->Jic[i*3 + j] = temp2;
			}
		}
		tilde(body1->ri_dot, body1->rit_dot);
		tilde(body1->ric_dot, body1->rict_dot);
		tilde(body1->ric, body1->rict);
		double temp3[9] = {0,};
		mat(body1->rict, body1->rict, 3, 3, 3, 3, temp3);
		for(uint i = 0; i < 3; i++){
			for(uint j = 0; j < 3; j++){
				body1->Mih[i*6 + j] = i == j ? body1->mi : 0;
				body1->Mih[(i + 3)*6 + j] = body1->mi*body1->rict[i*3 + j];
				body1->Mih[i*6 + (j + 3)] = -body1->mi*body1->rict[i*3 + j];
				body1->Mih[(i + 3)*6 + (j + 3)] = body1->Jic[i*3 + j] - body1->mi*temp3[i*3 + j];
			}
		}
		body1->fic[0] = 0;
		body1->fic[1] = 0;
		body1->fic[2] = body1->mi*g;
		body1->tic[0] = 0;
		body1->tic[1] = 0;
		body1->tic[2] = 0;
		double rict_dot_wi[3] = {0,};
		mat(body1->rict_dot, body1->wi, 3, 3, 3, rict_dot_wi);
		for (uint i = 0; i < 3; i++){
			body1->Qih_g[i] = body1->fic[i];
			body1->Qih_c[i] = body1->mi*rict_dot_wi[i];
			body1->Qih[i] = body1->Qih_g[i] + body1->Qih_c[i];
		}
		double rict_fic[3] = {0,}, rict_rict_dot_wi[3] = {0,}, Jic_wi[3] = {0,}, wit_Jic_wi[3] = {0,};
		mat(body1->rict, body1->fic, 3, 3, 3, rict_fic);
		mat(body1->rict, rict_dot_wi, 3, 3, 3, rict_rict_dot_wi);
		mat(body1->Jic, body1->wi, 3, 3, 3, Jic_wi);
		mat(body1->wit, Jic_wi, 3, 3, 3, wit_Jic_wi);
		for (uint i = 0; i < 3; i++){
			body1->Qih_g[i + 3] = rict_fic[i];
			body1->Qih_c[i + 3] = body1->mi*rict_rict_dot_wi[i] - wit_Jic_wi[i];
			body1->Qih[i + 3] = body1->tic[i] + body1->Qih_g[i + 3] + body1->Qih_c[i + 3];
		}

		// velocity coupling
		mat(body0->wit, body1->Hi, 3, 3, 3, body1->Hi_dot);
		double rit_dot_Hi[3] = {0,}, rit_Hi_dot[3] = {0,};
		mat(body1->rit_dot, body1->Hi, 3, 3, 3, rit_dot_Hi);
		mat(body1->rit, body1->Hi_dot, 3, 3, 3, rit_Hi_dot);
		for(uint i = 0; i < 3; i++){
			body1->Di[i] = (rit_dot_Hi[i] + rit_Hi_dot[i])*body1->qi_dot;
			body1->Di[i+3] = body1->Hi_dot[i]*body1->qi_dot;
		}

		memcpy(body1->Di_sum, body1->Di, sizeof(double)*6);
		for(uint indx2 = indx - 1; indx2 >= 1; indx2--){
			for(uint i = 0; i < 6; i++){
				body1->Di_sum[i] += body[indx2].Di[i];
			}
		}
	}

	// system EQM
	for(uint i = num_body; i >= 1;  i--){
		body1 = &body[i];
		if (i == num_body){
			memcpy(body1->Ki, body1->Mih, sizeof(double)*36);
			memcpy(body1->Li, body1->Qih, sizeof(double)*6);
			memcpy(body1->Li_g, body1->Qih_g, sizeof(double)*6);
			memcpy(body1->Li_c, body1->Qih_c, sizeof(double)*6);
		}
		else{
			body2 = &body[i + 1];
			for(uint i = 0; i < 36; i++){
				body1->Ki[i] = body1->Mih[i] + body2->Ki[i];
			}
			mat(body2->Ki, body2->Di, 6, 6, 6, body2->Ki_Di);
			for(uint i = 0; i < 6; i++){
				body1->Li[i] = body1->Qih[i] + body2->Li[i] - body2->Ki_Di[i];
				body1->Li_g[i] = body1->Qih_g[i] + body2->Li_g[i] - body2->Ki_Di[i];
				body1->Li_c[i] = body1->Qih_c[i] + body2->Li_c[i] - body2->Ki_Di[i];
			}
		}
	}

	memset(Q, 0, sizeof(double)*num_body);
	memset(Q_g, 0, sizeof(double)*num_body);
	memset(Q_c, 0, sizeof(double)*num_body);
	for(uint indx = 1; indx <= num_body; indx++){
		body1 = &body[indx];
		mat(body1->Ki, body1->Di_sum, 6, 6, 6, body1->Ki_Di_sum);
		for(uint i = 0; i < 6; i++){
			Q[indx - 1] += body1->Bi[i]*(body1->Li[i] - body1->Ki_Di_sum[i]);
			Q_g[indx - 1] += body1->Bi[i]*(body1->Li_g[i] - body1->Ki_Di_sum[i]);
			Q_c[indx - 1] += body1->Bi[i]*(body1->Li_c[i] - body1->Ki_Di_sum[i]);
		}
	}

	memset(M, 0, sizeof(double)*num_body*num_body);
	for(uint indx = 1; indx <= num_body; indx++){
		body1 = &body[indx];
		for(uint indx2 = 1; indx2 <= num_body; indx2++){
			body2 = &body[indx2];
			double Ki_Bi[6] = {0,}, temp = 0;
			if (indx == indx2){
				mat(body1->Ki, body1->Bi, 6, 6, 6, Ki_Bi);
			}
			else if(indx < indx2){
				mat(body2->Ki, body2->Bi, 6, 6, 6, Ki_Bi);
			}
			else if(indx > indx2){
				mat(body1->Ki, body2->Bi, 6, 6, 6, Ki_Bi);
			}
			temp = 0;
			for(uint i = 0; i < 6; i++){
				temp += body1->Bi[i]*Ki_Bi[i];
			}
			M[(indx - 1)*num_body + (indx2 - 1)] = temp;
		}
	}
}

void RobotArm::residual(){
	body[1].alpha = Q_g - Q_c;
	body[1].yp = body[1].Ta + body[1].alpha - body[1].r_hat;

	body[1].y = body[1].y_old + body[1].yp*h + 0.5*h*h*(body[1].yp - body[1].yp_old);

	for(uint i = 1; i <= num_body; i++){
		body[i].p_linear = 0;
		for (uint j = 0; j < 3; j++) {
			body[i].p_linear += pow(body[i].ric_dot[j], 2);
		}
		body[i].p_linear *= 0.5*body[i].mi;
		double temp[3] = { 0, };
		for (uint j = 0; j < 3; j++) {
			for (uint k = 0; k < 3; k++) {
				temp[k] += body[i].Jic[j * 3 + k] * body[i].wi[k];
			}
		}
		body[i].p_rotate = 0;
		for (uint j = 0; j < 3; j++) {
			body[i].p_rotate += body[i].wi[j] * temp[j];
		}
		body[i].p = body[i].p_linear + 0.5*body[i].p_rotate;
	}
	body[1].r_hat = body[1].K*(body[1].y - (body[1].p + body[2].p));

	body[1].y_old = body[1].y;
	body[1].yp_old = body[1].yp;

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
