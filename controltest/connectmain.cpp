
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

//#include "functions.h"
//#include "variables.h"
static int collision[5] = {0,};
int cx_cmdtor()
{

//    if (flag){
//        if (turn_on){
//            if (delay == 0){
//                crbapi::set_rs485_pdo_communication(0);

//                sdoSetData += 500;
//                sdoSetData = sdoSetData > goal_vel ? goal_vel : sdoSetData;

//                capp->setSDO(0, &sdoIndexGoalVel, 1, &sdoSetData);

//                crbapi::set_rs485_pdo_communication(1);
//            }
//        }

//        if (turn_off){
//            capp->setServoOn(false);
//            sdoSetData = 0;

//            turn_off = false;
//        }

//        delay++;
//        if (delay >= 1000 && sdoSetData < 2200){
//            delay = 0;
//        }

////        crbapi::get_current_first_encoder(0, &enc1, 1);
////        crbapi::get_current_second_encoder(0, &enc2, 1);
//        crbapi::get_user_input1(0, &enc_diff, 1);
//        crbapi::get_cur_enc(0, &pos);
//        crbapi::get_cur_velocity(0, &vel, 1);

//        diff = enc_diff*ENC2DEG*DEG2RAD;
//        actual_torque = k*diff;
//        pos_rad = (pos*ENC2DEG - offset)*DEG2RAD;
//        vel_rad = vel*VEL2RPM*RPM2DEG*DEG2RAD;

//		robot.run_DOB_DTP(&pos_rad, &vel_rad, &actual_torque, &r_hat, &collision);
		collision[0] = 10;
		crbapi::set_collision_array(0, collision, 5); // KETI
//		crbapi::get_collision_array(0, &collision, 1); // KIRO


//        tpData[indx].indx = indx;
//        tpData[indx].pos = pos_rad;
//        tpData[indx].vel = vel_rad;
//        tpData[indx].tor = actual_torque;
//        tpData[indx].r_hat = r_hat;
//        tpData[indx].r_hat_filter = r_hat_filter;

//        indx++;
//        if (indx >= max_indx) indx = max_indx - 1;

//        if (r_hat_filter > 0.17) set_turn_off();
//    }

//	if (flag){
//		crbapi::get_user_input1(0, &enc_diff, 1);
//		crbapi::get_cur_enc(0, &pos);
//		crbapi::get_cur_velocity(0, &vel, 1);

//		diff = enc_diff*ENC2DEG*DEG2RAD;
//		actual_torque = k*diff;
//		pos_rad = (pos*ENC2DEG - offset)*DEG2RAD;
//		vel_rad = vel*VEL2RPM*RPM2DEG*DEG2RAD;

////		robot.run_DOB_DTP(&pos_rad, &vel_rad, &actual_torque, &r_hat, &collision);

//		tpData[indx].indx = indx;
//		tpData[indx].pos = pos_rad;
//		tpData[indx].vel = vel_rad;
//		tpData[indx].tor = actual_torque;
//		tpData[indx].r_hat = r_hat;
//		tpData[indx].r_hat_filter = r_hat_filter;

//		tpData[indx].value = value;

//		indx++;

//		if (indx >= max_indx) indx = max_indx - 1;
//	}
}

//void get_data(double *req_data, uint *data_size)
//{
//    *data_size = indx;
//    for(uint i =0; i < *data_size; i++){
//		req_data[i*6 + 0] = tpData[i].pos;
//		req_data[i*6 + 1] = tpData[i].vel;
//		req_data[i*6 + 2] = tpData[i].tor;
//		req_data[i*6 + 3] = tpData[i].r_hat;
//		req_data[i*6 + 4] = tpData[i].r_hat_filter;
//		req_data[i*6 + 5] = tpData[i].value;
//    }
//    indx = 0;
//}

//void set_flag(bool in_flag){
////    if (in_flag){
////        crbapi::set_rs485_pdo_communication(0);

////        int index[2] = {sdoIndexOperatingMode, sdoIndexGoalVel};
////        unsigned long data[2] = {1, 0};
////        capp->setSDO(0, index, 1, data);

////        crbapi::set_rs485_pdo_communication(1);
////    }
//	capp->setServoOn(in_flag);
//	flag = in_flag;
//}

//void set_gain(){
//    crbapi::set_rs485_pdo_communication(0);

//    int sdoIndex[15] = {0x03160020, 0x031A0020, 0x031E0020, 0x03220020, 0x03260020,
//                        0x032A0020, 0x032E0020, 0x03320020, 0x03360020, 0x033A0020,
//                        0x033E0020, 0x03420020, 0x03460020, 0x034A0020, 0x034E0020};
//    unsigned long sdoSetData[15] = {0,};

//    capp->setSDO(0, sdoIndex, 15, sdoSetData);

//    crbapi::set_rs485_pdo_communication(1);
//}

//void get_gain(unsigned long *rdata){
//    crbapi::set_rs485_pdo_communication(0);

//    int sdoIndex[15] = {0x03160020, 0x031A0020, 0x031E0020, 0x03220020, 0x03260020,
//                        0x032A0020, 0x032E0020, 0x03320020, 0x03360020, 0x033A0020,
//                        0x033E0020, 0x03420020, 0x03460020, 0x034A0020, 0x034E0020};
//    unsigned long sdoGetData[15] = {0,};

//    capp->getSDO(0, sdoIndex, 15, sdoGetData);

//    for (int i = 0; i < 15; i++){
//        rdata[i] = sdoGetData[i];
//    }

//    crbapi::set_rs485_pdo_communication(1);
//}

//void set_turn_on(){
//    turn_on = true;
//    turn_off = false;
//    sdoSetData = 0;
//}

//void set_turn_off(){
//    turn_on = false;
//    turn_off = true;
//    sdoSetData = 0;
//}

//void set_torque_mode(){
//    mode = 1;
//    crbapi::set_user_output2(0, &mode, 1);
//}

//void set_up(){
//    value += 500;
//    crbapi::set_user_output1(0, &value, 1);
//}

//void set_down(){
//    value -= 500;
//    crbapi::set_user_output1(0, &value, 1);
//}

//void get_value(long *get_value){
//    *get_value = value;
//}

//void get_servo(bool *status){
//	*status = capp->getServoOn();
//}
