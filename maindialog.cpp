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

	QStringList labels;
	labels << "Name" << "Data";

	ui->tableWidget->clear();
	ui->tableWidget->setColumnCount(2);
	ui->tableWidget->setHorizontalHeaderLabels(labels);

	connect(ui->pushButtonAdd, SIGNAL(clicked(bool)),
			SLOT(onAdd()));

	connect(ui->pushButtonRemove, SIGNAL(clicked(bool)),
			SLOT(onRemove()));

	connect(ui->pushButtonClose, SIGNAL(clicked(bool)),
			SLOT(accept()));

	connect(ui->pushButtonAddData, SIGNAL(clicked(bool)),
			SLOT(onAddData()));

	connect(ui->pushButtonRemoveData, SIGNAL(clicked(bool)),
			SLOT(onRemoveData()));

	connect(ui->listWidget, SIGNAL(itemSelectionChanged()),
			SLOT(enableControls()));

	connect(ui->listWidget, SIGNAL(itemSelectionChanged()),
			SLOT(updateDataTable()));

	connect(ui->tableWidget, SIGNAL(itemSelectionChanged()),
			SLOT(enableControls()));

	updateProjectList();
	updateDataTable();
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
	updateDataTable();
	enableControls();
}

void MainDialog::onAddData()
{
	QString projectName = ui->listWidget->selectedItems()[0]->text();
	m_db.addData(projectName,
				 QString("%1: Data1").arg(projectName),
				 QString("%1: Data2").arg(projectName));

	updateDataTable();
	enableControls();
}

void MainDialog::onRemoveData()
{
	m_db.removeData(ui->listWidget->currentItem()->text(),
					ui->tableWidget->currentRow());

	updateDataTable();
	enableControls();
}

void MainDialog::enableControls()
{
	ui->pushButtonRemove->setEnabled(
				ui->listWidget->selectedItems().count());

	ui->pushButtonAddData->setEnabled(
				ui->listWidget->selectedItems().count());

	ui->pushButtonRemoveData->setEnabled(
				ui->tableWidget->selectedItems().count());
}

void MainDialog::updateProjectList()
{
	ui->listWidget->clear();
	ui->listWidget->addItems(m_db.projects());
}

void MainDialog::updateDataTable()
{
	ui->tableWidget->clearContents();
	ui->tableWidget->setRowCount(0);

	QList<QListWidgetItem *> list = ui->listWidget->selectedItems();
	if (!list.count()) {
		return;
	}

	const QString projectName = list[0]->text();

	QList<QPair<QString, QString> > pairs = m_db.data(projectName);
	const int count = pairs.count();

	for (int i = 0; i < count; i++) {
		ui->tableWidget->insertRow(ui->tableWidget->rowCount());
		ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0,
								 new QTableWidgetItem(pairs[i].first));
		ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1,
								 new QTableWidgetItem(pairs[i].second));
	}
}
