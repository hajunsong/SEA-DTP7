#include "dob.h"

DOB::DOB(uint numbody)
{
    num_body = numbody;
    body = new Body[num_body];

    // read data
    start_time = 0;
    //    end_time = 5;
    h = 0.002;
    g = -9.80665;

    body[0].A0[0] = 1;	body[0].A0[1] = 0;	body[0].A0[2] = 0;
    body[0].A0[3] = 0;	body[0].A0[4] = 1;	body[0].A0[5] = 0;
    body[0].A0[6] = 0;	body[0].A0[7] = 0;	body[0].A0[8] = 1;

    body[0].r0[0] = 0;	body[0].r0[1] = 0;	body[0].r0[2] = 0;

    ang2mat(M_PI, M_PI_2, M_PI_2, body[0].C01, false);
    body[0].s01p[0] = 1.37633e-6;   body[0].s01p[1] = 0.0546755;    body[0].s01p[2] = 0.0116372;

    switch (num_body) {
        case 6:
            // body 6 variable
            goto CASE5;
CASE5: case 5:
            // body 5 variable
            goto CASE4;
CASE4: case 4:
            // body 4 variable
            goto CASE3;
CASE3: case 3:
            // body 3 variable
            goto CASE2;
CASE2: case 2:
            // body 2 variable
            body[1].qi = 0;
            body[1].qi_dot = 0;
            body[1].mi = 0.489451904456537;

            body[1].Jip[0] = 2.34784629597537e-004;  body[1].Jip[1] = 0;                      body[1].Jip[2] = 0;
            body[1].Jip[3] = 0;                      body[1].Jip[4] = 4.60887362792117e-004;  body[1].Jip[5] = 2.38198731578976e-022;
            body[1].Jip[6] = 0;                      body[1].Jip[7] = 2.38198731578976e-022;  body[1].Jip[8] = 2.35989837216437e-004;

            body[1].rhoip[0] = -1.98952e-16; body[1].rhoip[1] = 0.00546345; body[1].rhoip[2] = 2.84217e-17;
            ang2mat(M_PI_2, M_PI_2, 0, body[1].Cii, false);

            body[1].sijp[0] = 0;    body[1].sijp[1] = 0; body[1].sijp[2] = 0;
            ang2mat(0, 0, 0, body[1].Cij, false);
            goto CASE1;
CASE1: case 1:
            // body 1 variable
            body[0].qi = 0;
            body[0].qi_dot = 0;
            body[0].mi = 1.15828469407282;

            body[0].Jip[0] = 3.33759019862649e-004;  body[0].Jip[1] = -2.09252503527173e-021; body[0].Jip[2] = -2.15421743813125e-008;
            body[0].Jip[3] = -2.09252503527173e-021; body[0].Jip[4] = 1.75972275017953e-002;  body[0].Jip[5] = -3.70356905869084e-020;
            body[0].Jip[6] = -2.15421743813125e-008; body[0].Jip[7] = -3.70356905869084e-020; body[0].Jip[8] = 1.72798722147092e-002;

            body[0].rhoip[0] = 1.13687e-16; body[0].rhoip[1] = 4.70024e-15; body[0].rhoip[2] = 0.0114834;
            ang2mat(M_PI_2, M_PI_2, 0, body[0].Cii, false);

            body[0].sijp[0] = 0;    body[0].sijp[1] = -0.2; body[0].sijp[2] = 0.0147;
            ang2mat(M_PI_2, M_PI_2, 0, body[0].Cij, false);
            break;
    }

    // define Y vector
    Y = new double[num_body - 1];
    Yp = new double[num_body - 1];
    Y_old = new double[num_body - 1];
    Yp_old = new double[num_body - 1];

    memset(Y, 0, sizeof(double) * (num_body - 1));
    memset(Yp, 0, sizeof(double) * (num_body - 1));
    memset(Y_old, 0, sizeof(double) * (num_body - 1));
    memset(Yp_old, 0, sizeof(double) * (num_body - 1));
}

DOB::~DOB() {
    delete[] body;
    delete[] Y;
    delete[] Yp;
    delete[] Y_old;
    delete[] Yp_old;
}

void DOB::run(double *q, double *q_dot, double *tor, int *collision_flag)
{
    t_current = start_time;
    if (num_body == 1) {
        Y[0] = 0;
    }
    else {
        for (uint i = 0; i < num_body; i++) {
            Y[i] = 0;
        }
    }

    for (uint i = 0; i < num_body - 1; i++) {
        body[i].qi = q[i];
    }
    for (uint i = 0; i < num_body - 1; i++) {
        body[i].qi_dot = q_dot[i];
    }
    for (uint i = 0; i < num_body - 1; i++) {
        body[i].tor = tor[i];
    }

    analysis();

    for (uint i = 0; i < num_body - 1; i++) {
        Yp[i] = body[i].yp;
    }

    for (uint i = 0; i < num_body - 1; i++) {
        Y[i] = Y_old[i] + Yp_old[i] * h + 0.5*h*h*(Yp[i] - Yp_old[i]);
    }

    for (uint i = 0; i < num_body; i++) {
        double p_linear = 0, p_rotate = 0;
        for (uint j = 0; j < 3; j++) {
            p_linear += pow(body[i].ric_dot[j], 2);
        }
        p_linear *= 0.5*body[i].mi;

        double temp[3] = { 0, };
        for (uint j = 0; j < 3; j++) {
            for (uint k = 0; k < 3; k++) {
                temp[k] += body[i].Jic[j * 3 + k] * body[i].wi[k];
            }
        }
        for (uint j = 0; j < 3; j++) {
            p_rotate += body[i].wi[j] * temp[j];
        }
        body[i].p = p_linear + 0.5*p_rotate;
        body[i].r_hat = body[i].K*(Y[i] - body[i].p);
    }

    memcpy(Yp_old, Yp, sizeof(double) * (num_body - 1));
    memcpy(Y_old, Y, sizeof(double) * (num_body - 1));

    t_current += h;

    //    for (uint i = 0; i < num_body; i++) {
    //        printf("P%d : %.10f[rad] ", i, q[i]);
    //    }
    //    for (uint i = 0; i < num_body; i++) {
    //        printf("R : %.5f[Nm] ", body[i].r_hat);
    //    }
    //    printf("\n");

    for(uint i = 0; i < num_body; i++){
        if (body[i].PThreshold < body[i].r_hat){
            collision_flag[i] = 1;
        }
        else if (body[i].NThreshold > body[i].r_hat){
            collision_flag[i] = 1;
        }
        else{
            0;
        }
    }
}

void DOB::analysis() {
    kinematics_analysis();
    generalized_mass_force();
    residual_analysis();
}

void DOB::kinematics_analysis() {
    for (uint indx = 0; indx < num_body; indx++) {
        // Orientation
        double *Aijpp_ptr = body[indx].Aijpp;
        *(Aijpp_ptr++) = cos(body[indx].qi);	*(Aijpp_ptr++) = -sin(body[indx].qi);	*(Aijpp_ptr++) = 0;
        *(Aijpp_ptr++) = sin(body[indx].qi);	*(Aijpp_ptr++) = cos(body[indx].qi);	*(Aijpp_ptr++) = 0;
        *(Aijpp_ptr++) = 0;						*(Aijpp_ptr++) = 0;						*(Aijpp_ptr++) = 1;
        memset(body[indx].Hi, 0, sizeof(double) * 3);
        memset(body[indx].Ai, 0, sizeof(double) * 9);
        if (indx == 0) {
            double A0_C01[9] = { 0, };
            for (uint i = 0; i < 3; i++) {
                for (uint j = 0; j < 3; j++) {
                    for (uint k = 0; k < 3; k++) {
                        A0_C01[i * 3 + j] += body[indx].A0[i * 3 + k] * body[indx].C01[k * 3 + j];
                    }
                }
            }
            for (uint i = 0; i < 3; i++) {
                for (uint j = 0; j < 3; j++) {
                    body[indx].Hi[i] += A0_C01[i * 3 + j] * body[indx].u_vec[j];
                    for (uint k = 0; k < 3; k++) {
                        body[indx].Ai[i * 3 + j] += A0_C01[i * 3 + k] * body[indx].Aijpp[k * 3 + j];
                    }
                }
            }
        }
        else {
            double Ai_Cij[9] = { 0, };
            for (uint i = 0; i < 3; i++) {
                for (uint j = 0; j < 3; j++) {
                    for (uint k = 0; k < 3; k++) {
                        Ai_Cij[i * 3 + j] += body[indx - 1].Ai[i * 3 + k] * body[indx - 1].Cij[k * 3 + j];
                    }
                }
            }
            for (uint i = 0; i < 3; i++) {
                for (uint j = 0; j < 3; j++) {
                    body[indx].Hi[i] += Ai_Cij[i * 3 + j] * body[indx].u_vec[j];
                    for (uint k = 0; k < 3; k++) {
                        body[indx].Ai[i * 3 + j] += Ai_Cij[i * 3 + k] * body[indx].Aijpp[k * 3 + j];
                    }
                }
            }
        }
        // Position
        if (indx == 0) {
            memset(body[indx].ri, 0, sizeof(double) * 3);
            for (uint i = 0; i < 3; i++) {
                for (uint j = 0; j < 3; j++) {
                    body[indx].ri[i] += body[indx].A0[i * 3 + j] * body[indx].s01p[j];
                }
            }
        }
        else {
            memset(body[indx - 1].sij, 0, sizeof(double) * 3);
            for (uint i = 0; i < 3; i++) {
                for (uint j = 0; j < 3; j++) {
                    body[indx - 1].sij[i] += body[indx - 1].Ai[i * 3 + j] * body[indx - 1].sijp[j];
                }
                body[indx].ri[i] = body[indx - 1].ri[i] + body[indx - 1].sij[i];
            }
        }
        memset(body[indx].rhoi, 0, sizeof(double) * 3);
        for (uint i = 0; i < 3; i++) {
            for (uint j = 0; j < 3; j++) {
                body[indx].rhoi[i] += body[indx].Ai[i * 3 + j] * body[indx].rhoip[j];
            }
            body[indx].ric[i] = body[indx].ri[i] + body[indx].rhoi[i];
        }
        // Inertial matrix
        double Ai_Cii[9] = { 0, };
        for (uint i = 0; i < 3; i++) {
            for (uint j = 0; j < 3; j++) {
                for (uint k = 0; k < 3; k++) {
                    Ai_Cii[i * 3 + j] += body[indx].Ai[i * 3 + k] * body[indx].Cii[k * 3 + j];
                }
            }
        }
        memset(body[indx].Jic, 0, sizeof(double) * 9);
        double temp[9] = { 0, };
        for (uint i = 0; i < 3; i++) {
            for (uint j = 0; j < 3; j++) {
                for (uint k = 0; k < 3; k++) {
                    temp[i * 3 + j] += Ai_Cii[i * 3 + k] * body[indx].Jip[k * 3 + j];
                }
            }
        }
        for (uint i = 0; i < 3; i++) {
            for (uint j = 0; j < 3; j++) {
                body[indx].Jic[i * 3 + j] = 0;
                for (uint k = 0; k < 3; k++) {
                    body[indx].Jic[i * 3 + j] += temp[i * 3 + k] * Ai_Cii[j * 3 + k];
                }
            }
        }
    }
}

void DOB::generalized_mass_force() {
    for (uint indx = 0; indx < num_body; indx++) {
        // Velocity State
        tilde(body[indx].ri, body[indx].rit);
        memset(body[indx].Bi, 0, sizeof(double) * 3);
        for (uint i = 0; i < 3; i++) {
            for (uint j = 0; j < 3; j++) {
                body[indx].Bi[i] += body[indx].rit[i * 3 + j] * body[indx].Hi[j];
            }
        }
        memcpy(body[indx].Bi + 3, body[indx].Hi, sizeof(double) * 3);
        if (indx == 0) {
            for (uint i = 0; i < 6; i++) {
                body[indx].Yih[i] = body[indx].Bi[i] * body[indx].qi_dot;
            }
        }
        else {
            for (uint i = 0; i < 6; i++) {
                body[indx].Yih[i] = body[indx - 1].Yih[i] + body[indx].Bi[i] * body[indx].qi_dot;
            }
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
        double mi_rict[9] = { 0, };
        for (uint i = 0; i < 9; i++) {
            mi_rict[i] = body[indx].mi*body[indx].rict[i];
        }
        memset(body[indx].Mih, 0, sizeof(double) * 36);
        for (uint i = 0; i < 3; i++) {
            for (uint j = 0; j < 3; j++) {
                body[indx].Mih[i * 6 + j] = i == j ? body[indx].mi : 0;
                body[indx].Mih[i * 6 + (j + 3)] = -mi_rict[i * 3 + j];
                body[indx].Mih[(i + 3) * 6 + j] = mi_rict[i * 3 + j];
                for (uint k = 0; k < 3; k++) {
                    body[indx].Mih[(i + 3) * 6 + (j + 3)] += -mi_rict[i * 3 + k] * body[indx].rict[k * 3 + j];
                }
                body[indx].Mih[(i + 3) * 6 + (j + 3)] += body[indx].Jic[i * 3 + j];
            }
        }
        memset(body[indx].Fic, 0, sizeof(double) * 3);
        body[indx].Fic[2] = body[indx].mi*g;

        double mi_rict_drict_wi[3] = { 0, }, wit_Jic_wi[3] = { 0, };
        for (uint i = 0; i < 3; i++) {
            for (uint j = 0; j < 3; j++) {
                double temp1[3] = { 0, }, temp2[3] = { 0, };
                for (uint k = 0; k < 3; k++) {
                    for (uint m = 0; m < 3; m++) {
                        temp1[k] += body[indx].rict_dot[k * 3 + m] * body[indx].wi[m];
                        temp2[k] += body[indx].Jic[k * 3 + m] * body[indx].wi[m];
                    }
                }
                mi_rict_drict_wi[i] += mi_rict[i * 3 + j] * temp1[j];
                wit_Jic_wi[i] += body[indx].wit[i * 3 + j] * temp2[j];
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
            body[indx].Qih_c[i + 3] += (mi_rict_drict_wi[i] - wit_Jic_wi[i]);
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
            double temp1 = 0, temp2 = 0;
            for (uint j = 0; j < 3; j++) {
                temp1 += body[indx].rit_dot[i * 3 + j] * body[indx].Hi[j];
                temp2 += body[indx].rit[i * 3 + j] * body[indx].dHi[j];
            }
            body[indx].Di[i] = (temp1 + temp2)*body[indx].qi_dot;
            body[indx].Di[i + 3] = body[indx].dHi[i] * body[indx].qi_dot;
        }
    }

    int sub_indx = num_body - 1;
    for (int indx = sub_indx; indx >= 0; indx--) {
        memcpy(body[indx].Ki, body[indx].Mih, sizeof(double) * 36);
        memcpy(body[indx].Li_g, body[indx].Qih_g, sizeof(double) * 6);
        memcpy(body[indx].Li_c, body[indx].Qih_c, sizeof(double) * 6);
        if (indx != sub_indx) {
            for (uint i = 0; i < 36; i++) {
                body[indx].Ki[i] += body[indx + 1].Ki[i];
            }
            for (uint i = 0; i < 6; i++) {
                double temp = 0;
                for (uint j = 0; j < 6; j++) {
                    temp += body[indx + 1].Ki[i * 6 + j] * body[indx + 1].Di[j];
                }
                body[indx].Li_g[i] += (body[indx + 1].Li_g[i] - temp);
                body[indx].Li_c[i] += (body[indx + 1].Li_c[i] - temp);
            }
        }
    }
}

void DOB::residual_analysis() {
    for (uint i = 0; i < num_body; i++) {
        double D_temp[6] = { 0, };
        for (uint j = 0; j <= i; j++) {
            for (uint k = 0; k < 6; k++) {
                D_temp[k] += body[j].Di[k];
            }
        }
        double temp1[6] = { 0, };
        body[i].Tg = 0;
        body[i].Tc = 0;
        for (uint j = 0; j < 6; j++) {
            for (uint k = 0; k < 6; k++) {
                temp1[j] += body[i].Ki[j * 6 + k] * D_temp[k];
            }
            body[i].Tg += body[i].Bi[j] * (body[i].Li_g[j] - temp1[j]);
            body[i].Tc += body[i].Bi[j] * (body[i].Li_c[j] - temp1[j]);
        }
        body[i].alpha = body[i].Tg;
        body[i].Ta = body[i].tor;
        body[i].yp = body[i].Ta + body[i].alpha - body[i].r_hat;
    }
}
