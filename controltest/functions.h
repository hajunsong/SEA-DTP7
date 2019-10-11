extern void set_torque(short value);
extern void set_torque_mode(long value);

extern short get_torque();
extern double get_torque_cal();
extern long int get_enc1();
extern long int get_enc2();
extern long int get_enc_diff();
extern long int get_pos();
extern long int get_vel();
extern double get_pos_deg();
extern double get_vel_rpm();
extern double get_vel_deg();
extern void get_data(double *req_data);
extern void set_flag(bool in_flag);
extern void set_gain();
extern void get_gain(unsigned long *rdata);
extern void set_turn_on();
extern void set_turn_off();
