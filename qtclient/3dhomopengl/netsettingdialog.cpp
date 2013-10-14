#include "netsettingdialog.h"
#include "ui_netsettingdialog.h"

netsettingDialog::netsettingDialog(QWidget *parent)
:   QDialog(parent)
{
    ui = new Ui::netsettingDialog;
    ui->setupUi(this);
    ui->portlineEdit->setValidator(new QIntValidator(1, 65535, this));
}

netsettingDialog::~netsettingDialog()
{
    delete ui;
}

QString netsettingDialog::getHost()
{
    return ui->hostcomboBox->currentText();

}

QString netsettingDialog::getPort()
{
    return ui->portlineEdit->text();

}
