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
	timer->setInterval(200);
	timer->start();

	connect(ui->btnStart, SIGNAL(clicked()), this, SLOT(btnStartClicked()));
	connect(ui->btnStop, SIGNAL(clicked()), this, SLOT(btnStopClicked()));
}

Form::~Form()
{
	delete timer;
	delete ui;
}

void Form::btnStartClicked()
{
	flag = true;
	set_flag(flag);
	fp = fopen("/mnt/mtd5/KETI_logging.txt", "w+");
}

void Form::btnStopClicked()
{
	flag = false;
	set_flag(flag);
	fclose(fp);
}

void Form::timeout()
{
	if (flag){
		get_data(data, &indx);
		for(uint i = 0; i < indx; i++){
			fprintf(fp, "%d\t", i);
			for(uint ii = 0; ii < 6; ii++) fprintf(fp, "%f\t", static_cast<double>(data[(i+1)*ii]));
			for(uint ii = 0; ii < 6; ii++) fprintf(fp, "%f\t", static_cast<double>(data[(i+1)*ii + 6]));
			for(uint ii = 0; ii < 6; ii++) fprintf(fp, "%f\t", static_cast<double>(data[(i+1)*ii + 12]));
			for(uint ii = 0; ii < 6; ii++) fprintf(fp, "%f\t", static_cast<double>(data[(i+1)*ii + 18]));
			fprintf(fp, "\n");
		}
	}
}
