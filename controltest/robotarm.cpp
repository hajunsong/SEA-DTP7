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

RobotArm::RobotArm(uint numbody, uint DOF) {
    num_body = numbody;
    dof = DOF;

    // read data
    h = 0.002;
    g = -9.80665;

    // body 0 variable
    body[0].Ai[0] = 1; body[0].Ai[1] = 0; body[0].Ai[2] = 0;
    body[0].Ai[3] = 0; body[0].Ai[4] = 1; body[0].Ai[5] = 0;
    body[0].Ai[6] = 0; body[0].Ai[7] = 0; body[0].Ai[8] = 1;

    memset(body[0].ri, 0, sizeof(double)*3);
    memset(body[0].ri_dot, 0, sizeof(double)*3);

    ang2mat(M_PI, M_PI_2, M_PI_2, body[0].Cij, false);
    body[0].sijp[0] = 1.37633e-6; body[0].sijp[1] = 0.0546755; body[0].sijp[2] = 0.0116372;

    memset(body[0].Yih, 0, sizeof(double)*6);
    memset(body[0].wit, 0, sizeof(double)*3);

    // body 1 variable
    body[1].qi = 0;
    body[1].qi_dot = 0;

    body[1].u_vec[0] = 0;   body[1].u_vec[1] = 0;   body[1].u_vec[2] = 1;

    body[1].mi = 1.15828469407282;

    body[1].Jip[0] =  3.33759019862649e-004; body[1].Jip[1] = -2.09252503527173e-021; body[1].Jip[2] = -2.15421743813125e-008;
    body[1].Jip[3] = -2.09252503527173e-021; body[1].Jip[4] =  1.75972275017953e-002; body[1].Jip[5] = -3.70356905869084e-020;
    body[1].Jip[6] = -2.15421743813125e-008; body[1].Jip[7] = -3.70356905869084e-020; body[1].Jip[8] =  1.72798722147092e-002;
    ang2mat(M_PI_2, M_PI_2, 0, body[1].Cii, false);
    body[1].rhoip[0] = 1.13687e-16; body[1].rhoip[1] = 4.70024e-15; body[1].rhoip[2] = 0.0114834;

    ang2mat(M_PI_2, M_PI_2, 0, body[1].Cij, false);
    body[1].sijp[0] = 0; body[1].sijp[1] = -0.2; body[1].sijp[2] = 0.0147;

    // DOB residual
    body[1].r_hat = 0;
    body[1].y = 0;
    body[1].yp = 0;
    body[1].K = 100;
    body[1].p_linear = 0;
    body[1].p_rotate = 0;
    body[1].p = 0;
    body[1].y_old = 0;
    body[1].yp_old = 0;

    // body 2 variable
    body[2].qi = 0;
    body[2].qi_dot = 0;

    body[2].mi = 0.489451904456537;

    body[2].u_vec[0] = 0;   body[2].u_vec[1] = 0;   body[2].u_vec[2] = 0;

    body[2].Jip[0] = 2.34784629597537e-004;  body[2].Jip[1] = 0;                      body[2].Jip[2] = 0;
    body[2].Jip[3] = 0;                      body[2].Jip[4] = 4.60887362792117e-004;  body[2].Jip[5] = 2.38198731578976e-022;
    body[2].Jip[6] = 0;                      body[2].Jip[7] = 2.38198731578976e-022;  body[2].Jip[8] = 2.35989837216437e-004;
    ang2mat(0, 0, 0, body[2].Cii, false);
    body[2].rhoip[0] = -1.98952e-16; body[2].rhoip[1] = 0.00546345; body[2].rhoip[2] = 2.84217e-17;

    ang2mat(0, 0, 0, body[2].Cij, false);
    body[2].sijp[0] = 0; body[2].sijp[1] = 0; body[2].sijp[2] = 0;

    f_cut = 500;
    memset(time_zone, 0, sizeof(double)*3);
    filter_indx = 0;
}

RobotArm::~RobotArm() {
}

void RobotArm::run_DOB_DTP(double *qi, double *qi_dot, double *Ta, double *r_hat, double *r_hat_filter){
    body[1].qi = qi[0];
    body[1].qi_dot = qi_dot[0];
    body[1].Ta = Ta[0];

    kinematics();
    dynamics();
    systemEQM();
    residual();

    r_hat[0] = body[1].r_hat;
    high_pass_filter(r_hat, time_zone, r_hat_filter, h);
}

void RobotArm::kinematics()
{
    for (uint indx = 1; indx <= num_body; indx++) {
        // Orientation relationship
        body[indx].Aijpp[0] = cos(body[indx].qi);	body[indx].Aijpp[1] = -sin(body[indx].qi);	body[indx].Aijpp[2] = 0;
        body[indx].Aijpp[3] = sin(body[indx].qi);	body[indx].Aijpp[4] = cos(body[indx].qi);	body[indx].Aijpp[5] = 0;
        body[indx].Aijpp[6] = 0;					body[indx].Aijpp[7] = 0;					body[indx].Aijpp[8] = 1;
        memset(body[indx].Hi, 0, sizeof(double) * 3);
        memset(body[indx].Ai, 0, sizeof(double) * 9);
        memset(body[indx].Ai_Cij, 0, sizeof(double) * 9);
        for (uint i = 0; i < 3; i++) {
            for (uint j = 0; j < 3; j++) {
                for (uint k = 0; k < 3; k++) {
                    body[indx].Ai_Cij[i * 3 + j] += body[indx - 1].Ai[i * 3 + k] * body[indx - 1].Cij[k * 3 + j];
                }
            }
        }
        for (uint i = 0; i < 3; i++) {
            for (uint j = 0; j < 3; j++) {
                body[indx].Hi[i] += body[indx].Ai_Cij[i * 3 + j] * body[indx].u_vec[j];
                for (uint k = 0; k < 3; k++) {
                    body[indx].Ai[i * 3 + j] += body[indx].Ai_Cij[i * 3 + k] * body[indx].Aijpp[k * 3 + j];
                }
            }
        }
        // Position relationship
        memset(body[indx - 1].sij, 0, sizeof(double) * 3);
        for (uint i = 0; i < 3; i++) {
            for (uint j = 0; j < 3; j++) {
                body[indx - 1].sij[i] += body[indx - 1].Ai[i * 3 + j] * body[indx - 1].sijp[j];
            }
            body[indx].ri[i] = body[indx - 1].ri[i] + body[indx - 1].sij[i];
        }
    }

    // End point
    for (uint i = 0; i < 3; i++) {
        body[num_body].sij[i] = 0;
        for (uint j = 0; j < 3; j++) {
            body[num_body].sij[i] += body[num_body].Ai[i * 3 + j] * body[num_body].sijp[j];
        }
        body[num_body].re[i] = body[num_body].ri[i] + body[num_body].sij[i];
    }
    for (uint i = 0; i < 3; i++) {
        for (uint j = 0; j < 3; j++) {
            body[num_body].Ae[i * 3 + j] = 0;
            for (uint k = 0; k < 3; k++) {
                body[num_body].Ae[i * 3 + j] += body[num_body].Ai[i * 3 + k] * body[num_body].Cij[k * 3 + j];
            }
        }
    }
    body[num_body].roll = atan2(body[num_body].Ae[2 * 3 + 1], body[num_body].Ae[2 * 3 + 2]);
    body[num_body].pitch = atan2(-body[num_body].Ae[2 * 3 + 0], sqrt(pow(body[num_body].Ae[2 * 3 + 1], 2.0) + pow(body[num_body].Ae[2 * 3 + 2], 2.0)));
    body[num_body].yaw = atan2(body[num_body].Ae[1 * 3 + 0], body[num_body].Ae[0 * 3 + 0]);
}

void RobotArm::dynamics(){
    for(uint indx = 1; indx <= num_body; indx++){
        memset(body[indx].rhoi, 0, sizeof(double) * 3);
        for (uint i = 0; i < 3; i++) {
            for (uint j = 0; j < 3; j++) {
                body[indx].rhoi[i] += body[indx].Ai[i * 3 + j] * body[indx].rhoip[j];
            }
            body[indx].ric[i] = body[indx].ri[i] + body[indx].rhoi[i];
        }

        // Inertial matrix
        for (uint i = 0; i < 3; i++) {
            for (uint j = 0; j < 3; j++) {
                body[indx].Ai_Cii[i*3+j] = 0;
                for (uint k = 0; k < 3; k++) {
                    body[indx].Ai_Cii[i * 3 + j] += body[indx].Ai[i * 3 + k] * body[indx].Cii[k * 3 + j];
                }
            }
        }
        memset(body[indx].Jic, 0, sizeof(double) * 9);
        for (uint i = 0; i < 3; i++) {
            for (uint j = 0; j < 3; j++) {
                body[indx].Ai_Cii_Jip[i*3+j] = 0;
                for (uint k = 0; k < 3; k++) {
                    body[indx].Ai_Cii_Jip[i * 3 + j] += body[indx].Ai_Cii[i * 3 + k] * body[indx].Jip[k * 3 + j];
                }
            }
        }
        for (uint i = 0; i < 3; i++) {
            for (uint j = 0; j < 3; j++) {
                body[indx].Jic[i * 3 + j] = 0;
                for (uint k = 0; k < 3; k++) {
                    body[indx].Jic[i * 3 + j] += body[indx].Ai_Cii_Jip[i * 3 + k] * body[indx].Ai_Cii[j * 3 + k];
                }
            }
        }

        // Velocity State
        tilde(body[indx].ri, body[indx].rit);
        memset(body[indx].Bi, 0, sizeof(double) * 3);
        for (uint i = 0; i < 3; i++) {
            for (uint j = 0; j < 3; j++) {
                body[indx].Bi[i] += body[indx].rit[i * 3 + j] * body[indx].Hi[j];
            }
        }
        memcpy(body[indx].Bi + 3, body[indx].Hi, sizeof(double) * 3);

        for (uint i = 0; i < 6; i++) {
            body[indx].Yih[i] = body[indx - 1].Yih[i] + body[indx].Bi[i] * body[indx].qi_dot;
        }

        // Cartesian Velocity
        for (uint i = 0; i < 6; i++) {
            for (uint j = 0; j < 6; j++) {
                if (i < 3 && j >= 3) {
                    body[indx].Ti[i * 6 + j] = -body[indx].rit[i * 3 + (j - 3)];
                }
                else {
                    body[indx].Ti[i * 6 + j] = i == j ? 1 : 0;
                }
            }
        }
        memset(body[indx].Yib, 0, sizeof(double) * 6);
        for (uint i = 0; i < 6; i++) {
            for (uint j = 0; j < 6; j++) {
                body[indx].Yib[i] += body[indx].Ti[i * 6 + j] * body[indx].Yih[j];
            }
        }
        memcpy(body[indx].ri_dot, body[indx].Yib, sizeof(double) * 3);
        memcpy(body[indx].wi, body[indx].Yib + 3, sizeof(double) * 3);
        tilde(body[indx].wi, body[indx].wit);
        memset(body[indx].ric_dot, 0, sizeof(double) * 3);
        for (uint i = 0; i < 3; i++) {
            for (uint j = 0; j < 3; j++) {
                body[indx].ric_dot[i] += body[indx].wit[i * 3 + j] * body[indx].rhoi[j];
            }
            body[indx].ric_dot[i] += body[indx].ri_dot[i];
        }

        // Mass & Force
        tilde(body[indx].ric, body[indx].rict);
        tilde(body[indx].ric_dot, body[indx].rict_dot);
        for (uint i = 0; i < 9; i++) {
            body[indx].mi_rict[i] = body[indx].mi*body[indx].rict[i];
        }
        memset(body[indx].Mih, 0, sizeof(double) * 36);
        for (uint i = 0; i < 3; i++) {
            for (uint j = 0; j < 3; j++) {
                body[indx].Mih[i * 6 + j] = i == j ? body[indx].mi : 0;
                body[indx].Mih[i * 6 + (j + 3)] = -body[indx].mi_rict[i * 3 + j];
                body[indx].Mih[(i + 3) * 6 + j] = body[indx].mi_rict[i * 3 + j];
                for (uint k = 0; k < 3; k++) {
                    body[indx].Mih[(i + 3) * 6 + (j + 3)] += -body[indx].mi_rict[i * 3 + k] * body[indx].rict[k * 3 + j];
                }
                body[indx].Mih[(i + 3) * 6 + (j + 3)] += body[indx].Jic[i * 3 + j];
            }
        }
        memset(body[indx].Fic, 0, sizeof(double) * 3);
        body[indx].Fic[2] = body[indx].mi*g;

        for (uint i = 0; i < 3; i++) {
            for (uint j = 0; j < 3; j++) {
                body[indx].rict_dot_wi[i*3+j] = 0;
                body[indx].Jic_wi[i+3+j] = 0;
                for (uint k = 0; k < 3; k++) {
                    for (uint m = 0; m < 3; m++) {
                        body[indx].rict_dot_wi[k] += body[indx].rict_dot[k * 3 + m] * body[indx].wi[m];
                        body[indx].Jic_wi[k] += body[indx].Jic[k * 3 + m] * body[indx].wi[m];
                    }
                }
                body[indx].mi_rict_drict_wi[i] += body[indx].mi_rict[i * 3 + j] * body[indx].rict_dot_wi[j];
                body[indx].wit_Jic_wi[i] += body[indx].wit[i * 3 + j] * body[indx].Jic_wi[j];
            }
        }
        memset(body[indx].Qih_g, 0, sizeof(double) * 6);
        memset(body[indx].Qih_c, 0, sizeof(double) * 6);
        for (uint i = 0; i < 3; i++) {
            for (uint j = 0; j < 3; j++) {
                body[indx].Qih_g[i + 3] += body[indx].rict[i * 3 + j] * body[indx].Fic[j];
                body[indx].Qih_c[i] += body[indx].rict_dot[i * 3 + j] * body[indx].wi[j];
            }
            body[indx].Qih_g[i] = body[indx].Fic[i];
            body[indx].Qih_c[i] *= body[indx].mi;
            body[indx].Qih_c[i + 3] += (body[indx].mi_rict_drict_wi[i] - body[indx].wit_Jic_wi[i]);
        }
        // Velocity Coupling
        tilde(body[indx].ri_dot, body[indx].rit_dot);
        memset(body[indx].dHi, 0, sizeof(double) * 3);
        if (indx != 0) {
            for (uint i = 0; i < 3; i++) {
                for (uint j = 0; j < 3; j++) {
                    body[indx].dHi[i] += body[indx - 1].wit[i * 3 + j] * body[indx].Hi[j];
                }
            }
        }
        memset(body[indx].Di, 0, sizeof(double) * 3);
        for (uint i = 0; i < 3; i++) {
            body[indx].rit_dot_Hi[i] = 0;
            body[indx].rit_dHi[i] = 0;
            for (uint j = 0; j < 3; j++) {
                body[indx].rit_dot_Hi[i*3+j] += body[indx].rit_dot[i * 3 + j] * body[indx].Hi[j];
                body[indx].rit_dHi[i*3+j] += body[indx].rit[i * 3 + j] * body[indx].dHi[j];
            }
            body[indx].Di[i] = (body[indx].rit_dot_Hi[i] + body[indx].rit_dHi[i])*body[indx].qi_dot;
            body[indx].Di[i + 3] = body[indx].dHi[i] * body[indx].qi_dot;
        }
    }
}

void RobotArm::systemEQM(){
    memcpy(body[2].Ki, body[2].Mih, sizeof(double)*36);
    for(uint i = 0; i < 36; i++){
        body[1].Ki[i] = body[2].Ki[i] + body[1].Mih[i];
    }

    for(uint indx = 1; indx <= num_body; indx++){
        for(uint i = 0; i <6; i++){
            body[indx].Ki_Di[i] = 0;
            for(uint j = 0; j < 6; j++){
                body[indx].Ki_Di[i] += body[2].Ki[i*6+j]*body[2].Di[j];
            }
        }
    }
    memcpy(body[2].Li_g, body[2].Qih_g, sizeof(double)*6);
    memcpy(body[2].Li_c, body[2].Qih_c, sizeof(double)*6);
    for(uint i = 0; i < 6; i++){
        body[1].Li_g[i] = body[1].Qih_g[i] + body[2].Li_g[i] - body[2].Ki_Di[i];
        body[1].Li_c[i] = body[1].Qih_c[i] + body[2].Li_c[i] - body[2].Ki_Di[i];
    }

    M = 0;
    for(uint i = 0; i < 6; i++){
        body[1].Ki_Bi[i] = 0;
        for(uint j = 0; j < 6; j++){
            body[1].Ki_Bi[i] += body[1].Ki[i*6+j]*body[1].Bi[j];
        }
    }
    for(uint i = 0; i < 6; i++){
        M += body[1].Bi[i]*body[1].Ki_Bi[i];
    }

    Q_g = 0;
    Q_c = 0;
    for(uint i = 0; i < 6; i++){
        Q_g += body[1].Bi[i]*(body[1].Li_g[i] - body[1].Ki_Di[i]);
        Q_c += body[1].Bi[i]*(body[1].Li_c[i] - body[1].Ki_Di[i]);
    }

    Q = 0;
    Q = Q_g + Q_c;
//    body[1].qi_ddot = Q/M;
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

