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

    flag = false;
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
//	fp = fopen("/mnt/mtd5/KETI_logging.txt", "w+");
}

void Form::btnStopClicked()
{
	flag = false;
	set_flag(flag);
//	fclose(fp);
}

void Form::timeout()
{
	if (flag){
        get_data(data, &indx);
//		for(uint i = 0; i < indx; i++){
//			fprintf(fp, "%d\t", i);
//			for(uint ii = 0; ii < 6; ii++) fprintf(fp, "%f\t", static_cast<double>(data[(i+1)*ii]));
//			for(uint ii = 0; ii < 6; ii++) fprintf(fp, "%f\t", static_cast<double>(data[(i+1)*ii + 6]));
//			for(uint ii = 0; ii < 6; ii++) fprintf(fp, "%f\t", static_cast<double>(data[(i+1)*ii + 12]));
//			for(uint ii = 0; ii < 6; ii++) fprintf(fp, "%f\t", static_cast<double>(data[(i+1)*ii + 18]));
//			fprintf(fp, "\n");
//		}
//		get_enc(&enc);
//		printf("%ld\n", enc);
	}

//    get_enc(enc);
//    for(uint ii = 0; ii < 6; ii++) printf("%ld\t", enc[ii]);
//    printf("\n");
//    get_pos(pos_rad);
//    for(uint ii = 0; ii < 6; ii++) printf("%f\t", pos_rad[ii]);
//    printf("\n");

//    get_rhat(rhat);
//    for(uint ii = 0; ii < 6; ii++) printf("%f\t", rhat[ii]);
//    printf("\n");

//    get_enc_diff(diff);
//    for(uint ii = 0; ii < 6; ii++) printf("%ld\t", diff[ii]);
//    printf("\n");
}
