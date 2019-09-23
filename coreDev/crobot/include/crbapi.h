#ifndef __CRBAPI_H__
#define __CRBAPI_H__	1

#define DLL_EXPORT __attribute__ ((visibility ("default")))


class DLL_EXPORT  crbapi
{
public:
    crbapi();

    static int version;

    static int get_axis_count();
    static int get_ctl_mode();


    static void get_cur_joint(int id, float* joint);
    static void get_cmd_joint(int id, float* joint);
    static void get_cur_enc(int id, long* enc);
    static void get_cmd_enc(int id, long* enc);

    static int calc_foward_kinematics(int id, float* ang, cxmatrix* trans);
    static int calc_inverse_kinematics(int id, cxmatrix* trans, float* oldang, float* newang, CxConstraint *conf);

    static int get_cur_tool(int id, cxmatrix* tftool, float* weight);
    static int get_cur_base(int id, cxmatrix* base);

    static int get_cycletime_ms();


    static int get_cur_torque(int id, short* tor);
    static int get_ref_torque(int id, short* tor);

    static int get_user_input1(int id, long* input1, int naxis); //sea_torque
    static int get_user_input2(int id, long* input2, int naxis);
    static int get_user_input3(int id, long* input3, int naxis);

    static int set_user_output1(int id, long* output1, int naxis); //sea_torque
    static int set_user_output2(int id, long* output2, int naxis); //sea_torque_mode
    static int set_user_output3(int id, long* output3, int naxis);

    static int get_override_speed(int id, int speed);

    static int get_cur_uc(int id, cxmatrix* out);
    static int get_cmd_uc(int id, cxmatrix* out);

    static int set_collision_detect(int id, int value);
    static int set_cmd_tor(int id, int naxis, short* tor);

    static int get_run_done_status();

    static int get_ftsensor_force(int* value, int index); /*value -> force x,y,z, index means sensor index */
    static int get_ftsensor_torque(int* value, int index); /*value -> torque rx,ry,rz, index means sensor index*/

    static int get_current_first_encoder(int id, long* value, int naxis);
    static int get_current_second_encoder(int id, long* value, int naxis);

    static int get_cur_velocity(int id, long* value, int naxis);



};

#endif
