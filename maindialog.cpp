#include "maindialog.h"
#include "addprojectdialog.h"
#include <QSqlQuery>
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

	connect(ui->pushButtonRemove, SIGNAL(clicked(bool)),
			SLOT(onRemove()));

	connect(ui->pushButtonClose, SIGNAL(clicked(bool)),
			SLOT(accept()));

	connect(ui->listWidget, SIGNAL(itemSelectionChanged()),
			SLOT(enableControls()));

	updateProjectList();
	enableControls();
}

MainDialog::~MainDialog()
{
	delete ui;
	m_db.close();
}

void MainDialog::onAdd()
{
	AddProjectDialog dlg;
	dlg.setProjects(m_db.projects());
	if (dlg.exec() == QDialog::Accepted) {
		m_db.addProject(dlg.name());
	}

	updateProjectList();
	enableControls();
}

void MainDialog::onRemove()
{
	QString name = ui->listWidget->selectedItems()[0]->text();
	m_db.removeProject(name);

	updateProjectList();
	enableControls();
}

void MainDialog::enableControls()
{
	if (ui->listWidget->selectedItems().count()) {
		ui->pushButtonRemove->setEnabled(true);
	} else {
		ui->pushButtonRemove->setEnabled(false);
	}
}

void MainDialog::updateProjectList()
{
	ui->listWidget->clear();
	ui->listWidget->addItems(m_db.projects());
}
