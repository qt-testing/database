#include "addprojectdialog.h"
#include "ui_addprojectdialog.h"

AddProjectDialog::AddProjectDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AddProjectDialog)
{
	ui->setupUi(this);

	connect(ui->pushButtonOK, SIGNAL(clicked()),
			SLOT(onOK()));

	connect(ui->pushButtonCancel, SIGNAL(clicked()),
			SLOT(onCancel()));
}

AddProjectDialog::~AddProjectDialog()
{
	delete ui;
}

QString AddProjectDialog::name() const
{
	return m_name;
}

void AddProjectDialog::onOK()
{
	m_name = ui->lineEdit->text();

	QDialog::accept();
}

void AddProjectDialog::onCancel()
{
	m_name = "";

	QDialog::reject();
}
