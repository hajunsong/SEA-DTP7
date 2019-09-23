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
    timer->setInterval(10);
    timer->start();

    connect(ui->btnUp, SIGNAL(clicked()), this, SLOT(btnUpClicked()));
    connect(ui->btnDown, SIGNAL(clicked()), this, SLOT(btnDownClicked()));
    connect(ui->btnClear,SIGNAL(clicked()), this, SLOT(btnClearClicked()));

    connect(ui->btnIntervalUp, SIGNAL(clicked()), this, SLOT(btnIntervalUpClicked()));
    connect(ui->btnIntervalDown, SIGNAL(clicked()), this, SLOT(btnIntervalDownClicked()));

    connect(ui->btnOn, SIGNAL(clicked()), this, SLOT(btnOnClicked()));
    connect(ui->btnOff, SIGNAL(clicked()), this, SLOT(btnOffClicked()));

    tor_interval = 0;
}

Form::~Form()
{
    delete ui;
}

void Form::timeout(){
    enc1 = get_enc1();
    enc2 = get_enc2();
    pos = get_pos();
    vel = get_vel();
    tor = get_torque();
    pos_deg = get_pos_deg();
    vel_rpm = get_vel_rpm();
    vel_deg = get_vel_deg();
    torque = get_torque_cal();

    ui->txtEnc1->setText(QString::number(enc1));
    ui->txtEnc2->setText(QString::number(enc2));
    ui->txtPos->setText(QString::number(pos));
//    ui->txtPosDeg->setText(QString::number(0.001f,'f',6));
    ui->txtVel->setText(QString::number(vel));
//    ui->txtVelRPM->setText(QString::number(vel_rpm, 'f', 6));
//    ui->txtVelDeg->setText(QString::number(vel_deg, 'f', 6));
    ui->txtTor->setText(QString::number(tor));
    printf("pos : %3.3f[DEG]\t vel : %3.3f[RPM], \t%3.3f[DEG/S]\t tor : %3.3f[Nm]\n", pos_deg, vel_rpm, vel_deg, torque);
//    printf("enc1 : %ld\t, enc2 : %ld\t, tor : %f\n", enc1, enc2, K);
}

void Form::btnUpClicked()
{
    long tmp_tor = get_torque();

    short set_tor = static_cast<short>(tmp_tor) + tor_interval;
    set_torque(set_tor);
}

void Form::btnDownClicked(){
    long tmp_tor = get_torque();

    short set_tor = static_cast<short>(tmp_tor) - tor_interval;
    set_torque(set_tor);
}

void Form::btnClearClicked()
{
    set_torque(0);
}

void Form::btnOnClicked()
{
    set_torque_mode(1);
}

void Form::btnOffClicked()
{
    set_torque_mode(0);
}

void Form::btnIntervalUpClicked()
{
    tor_interval += tick;
    ui->txtInterval->setText(QString::number(tor_interval));
}

void Form::btnIntervalDownClicked()
{
    tor_interval -= tick;
    ui->txtInterval->setText(QString::number(tor_interval));
}
