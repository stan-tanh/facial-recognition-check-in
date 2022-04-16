#include "dialog.h"
#include "ui_dialog.h"
#include <string>
QString samplename;
extern int function_choose;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{

    samplename = ui->textEdit->toPlainText();
    function_choose = 1;       //RUN_GETSANPLES;
    this->reject();
    printf("sample name save\n");
}
