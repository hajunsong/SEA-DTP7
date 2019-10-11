#include "form.h"
#include "ui_form.h"

extern "C" void* createTestSubWidget()
{
    Form* pW = new Form();

    return reinterpret_cast<void*>(pW);
}

Form::Form(QWidget *parent) : QWidget(parent), ui(new Ui::Form)
{
    ui->setupUi(this);

    this->setWindowTitle("KETI");

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
    timer->setInterval(100);
    timer->start();

    connect(ui->btnStart, SIGNAL(clicked()), this, SLOT(btnStartClicked()));
    connect(ui->btnStop, SIGNAL(clicked()), this, SLOT(btnStopClicked()));

    connect(ui->btnSetGain, SIGNAL(clicked()), this, SLOT(btnSetGainClicked()));
    connect(ui->btnGetGain, SIGNAL(clicked()), this, SLOT(btnGetGainClicked()));

    connect(ui->btnTurnOn, SIGNAL(clicked()), this, SLOT(btnTurnOnClicked()));
    connect(ui->btnTurnOff, SIGNAL(clicked()), this, SLOT(btnTurnOffClicked()));

    tor_interval = 0;

    up_flag = false;
    down_flag = false;

    tick = 1;
    interval_up_flag = false;
    interval_down_flag = false;

    flag = false;
}

Form::~Form()
{
    delete ui;
}

void Form::timeout(){
    enc1 = get_enc1();
    enc2 = get_enc2();
    enc_diff = get_enc_diff();
    pos = get_pos();
    vel = get_vel();
    tor = get_torque();
    pos_deg = get_pos_deg();
    vel_rpm = get_vel_rpm();
    vel_deg = get_vel_deg();
    torque = get_torque_cal();

    ui->txtEnc1->setText(QString::number(enc1));
    ui->txtEnc2->setText(QString::number(enc2));
    ui->txtEncDiff->setText(QString::number(enc_diff));
    ui->txtPos->setText(QString::number(pos));
    ui->txtVel->setText(QString::number(vel));
    ui->txtTor->setText(QString::number(tor));
//    printf("pos : %3.3f[DEG]\t vel : %3.3f[RPM], \t%3.3f[DEG/S]\n", pos_deg, vel_rpm, vel_deg);
////    printf("enc1 : %ld\t, enc2 : %ld\t, tor : %f\n", enc1, enc2, K);

//    long tmp_tor = get_torque();

//    if (up_flag){
//        short set_tor = static_cast<short>(tmp_tor) + tor_interval;
//        set_torque(set_tor);
//    }

//    if (down_flag){
//        short set_tor = static_cast<short>(tmp_tor) - tor_interval;
//        set_torque(set_tor);
//    }

//    if (interval_up_flag){
//        tor_interval += tick;
//        ui->txtInterval->setText(QString::number(tor_interval));
//    }

//    if (interval_down_flag){
//        tor_interval -= tick;
//        ui->txtInterval->setText(QString::number(tor_interval));
//    }

//    get_data(TP_data);

    if (flag){
//        printf("pos : %f\t vel : %f\t diff : %f\t torque : %f\t torque_in : %f\n", TP_data[0], TP_data[1], TP_data[2], TP_data[3], TP_data[4]);
    }
}

void Form::btnStartClicked()
{
    set_flag(true);
    flag = true;
}

void Form::btnStopClicked()
{
    set_flag(false);
}

void Form::btnSetGainClicked(){
    set_gain();

}

void Form::btnGetGainClicked(){
    unsigned long data[15] = {0,};
    get_gain(data);

    for(int i = 0; i < 15; i++){
        printf("%ld\t", data[i]);
    }
    printf("\n");

}

void Form::btnTurnOnClicked()
{
    set_turn_on();
}

void Form::btnTurnOffClicked()
{
    set_turn_off();
}
