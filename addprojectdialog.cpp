#include "addprojectdialog.h"
#include "ui_addprojectdialog.h"

AddProjectDialog::AddProjectDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AddProjectDialog)
{
	ui->setupUi(this);
	ui->lineEdit->setFocus();

	connect(ui->pushButtonOK, SIGNAL(clicked()),
			SLOT(onOK()));

	connect(ui->pushButtonCancel, SIGNAL(clicked()),
			SLOT(onCancel()));

	connect(ui->lineEdit, SIGNAL(textChanged(const QString &)),
			SLOT(checkName(const QString &)));
}

AddProjectDialog::~AddProjectDialog()
{
	delete ui;
}

void AddProjectDialog::setProjects(const QStringList &projects)
{
	m_projects = projects;
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

void AddProjectDialog::checkName(const QString &text)
{
	if (m_projects.contains(text)) {
		ui->lineEdit->setStyleSheet("color: red");
		ui->pushButtonOK->setEnabled(false);
	} else {
		ui->lineEdit->setStyleSheet("color: black");
		ui->pushButtonOK->setEnabled(true);
	}
}
