#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include "database.h"
#include <QDialog>

namespace Ui {
	class MainDialog;
}

class MainDialog : public QDialog
{
	Q_OBJECT

public:
	explicit MainDialog(QWidget *parent = 0);
	~MainDialog();

private slots:
	void onAdd();
	void onRemove();
	void onAddData();
	void onRemoveData();
	void enableControls();
	void updateProjectList();
	void updateDataTable();

private:
	Ui::MainDialog *ui;
	Database m_db;
};

#endif // MAINDIALOG_H
