
/*
 *  CUSTOMUI
 *
 */
#include <stdio.h>
#include <memory.h>
#include <string.h>

#include "crbtype.h"
#include "crbapi.h"

#ifdef __cplusplus
extern "C" {
#endif

/* get widget pointer */
extern int cx_cmdtor();
extern void* cui_get_subwidget();
extern void* createTestSubWidget();

#ifdef __cplusplus
}
#endif

static void* s_subwidget_ptr;

void* cui_get_subwidget()
{
    if(s_subwidget_ptr == NULL)
        s_subwidget_ptr = (void*)createTestSubWidget();

    return s_subwidget_ptr;
}

#include "variables.h"
#include "functions.h"

int cx_cmdtor()
{
	crbapi::get_user_input1(0, enc_diff, 6);
	crbapi::get_cur_enc(0, pos);
	crbapi::get_cur_velocity(0, vel, 6);

	for(int i = 0; i < 6; i++){
		diff[i] = enc_diff[i]*ENC2DEG*DEG2RAD;
        if (i < 3) diff[i] = 0;
		actual_torque[i] = k[i]*diff[i];
        pos_rad[i] = (pos[i] - offset[i])*ENC2DEG*DEG2RAD;
		vel_rad[i] = vel[i]*VEL2RPM*RPM2DEG*DEG2RAD;
	}

	robot.run_DOB_DTP(pos_rad, vel_rad, actual_torque, r_hat_limit_p, r_hat_limit_n, collision, r_hat);
	crbapi::set_collision_array(0, collision, 12); // KETI
	//		crbapi::get_collision_array(0, &collision, 1); // KIRO

	if (flag){
		tpData[indx].indx = indx;
		for(int i = 0; i < 6; i++)	tpData[indx].pos[i] = pos_rad[i];
		for(int i = 0; i < 6; i++)	tpData[indx].vel[i] = vel_rad[i];
		for(int i = 0; i < 6; i++)	tpData[indx].tor[i] = actual_torque[i];
        for(int i = 0; i < 6; i++)	tpData[indx].r_hat[i] = collision[i + 6];

		indx++;

		if (indx >= max_indx) indx = max_indx - 1;
	}
}

void get_data(float *req_data, uint *data_size)
{
	*data_size = indx;
	for(uint i =0; i < *data_size; i++){
		for(uint ii = 0; ii < 6; ii++) req_data[(i+1)*ii] = tpData[i].pos[ii];
		for(uint ii = 0; ii < 6; ii++) req_data[(i+1)*ii + 6] = tpData[i].vel[ii];
		for(uint ii = 0; ii < 6; ii++) req_data[(i+1)*ii + 12] = tpData[i].tor[ii];
		for(uint ii = 0; ii < 6; ii++) req_data[(i+1)*ii + 18] = tpData[i].r_hat[ii];
	}
	indx = 0;
}

void set_flag(bool in_flag){
	flag = in_flag;
}

void get_enc(long *enc){
//	enc = &pos[0];
    for(int i = 0; i < 6; i++){
        enc[i] = pos[i];
    }
}

void get_rhat(float *rhat){
    for(int i = 0; i < 6; i++){
        rhat[i] = r_hat[i];
    }
}

void get_enc_diff(long *diff){
    for(int i = 0; i < 6; i++){
        diff[i] = enc_diff[i];
    }
}

void get_pos(float *pos){
    for(int i = 0; i < 6; i++){
        pos[i] = pos_rad[i];
    }
}
