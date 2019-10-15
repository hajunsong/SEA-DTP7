﻿#include "form.h"
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
    timer->setInterval(200);
    timer->start();

    connect(ui->btnStart, SIGNAL(clicked()), this, SLOT(btnStartClicked()));
    connect(ui->btnStop, SIGNAL(clicked()), this, SLOT(btnStopClicked()));

    connect(ui->btnSetGain, SIGNAL(clicked()), this, SLOT(btnSetGainClicked()));
    connect(ui->btnGetGain, SIGNAL(clicked()), this, SLOT(btnGetGainClicked()));

    connect(ui->btnTurnOn, SIGNAL(clicked()), this, SLOT(btnTurnOnClicked()));
    connect(ui->btnTurnOff, SIGNAL(clicked()), this, SLOT(btnTurnOffClicked()));

    flag = false;
}

Form::~Form()
{
    delete ui;
}

void Form::timeout(){
    get_data(data, &indx);

    if (flag){
        for(uint i = 0; i < indx; i++){
            fprintf(fp, "%d\t%f\t%f\t%f\t%f\t%f\n", indx, data[i*5+0], data[i*5+1], data[i*5+2], data[i*5+3], data[i*5+4]);
        }
    }
}

void Form::btnStartClicked()
{
    set_flag(true);
    flag = true;

    fp = fopen("/mnt/mtd5/KETI_data.txt", "w+");
}

void Form::btnStopClicked()
{
    set_flag(false);
    flag = false;

    fclose(fp);
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
