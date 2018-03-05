#include "maindialog.h"
#include "addprojectdialog.h"
#include "ui_maindialog.h"

MainDialog::MainDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::MainDialog)
{
	m_db.setDatabasePath("E:\\test.db");
	m_db.open();

	ui->setupUi(this);

	connect(ui->pushButtonAdd, SIGNAL(clicked(bool)),
			SLOT(onAdd()));
}

MainDialog::~MainDialog()
{
	delete ui;
	m_db.close();
}

void MainDialog::onAdd()
{
	AddProjectDialog dlg;
	if (dlg.exec() == QDialog::Accepted) {
		m_db.addProject(dlg.name());
	}
}
