#ifndef ADDPROJECTDIALOG_H
#define ADDPROJECTDIALOG_H

#include <QDialog>

namespace Ui {
	class AddProjectDialog;
}

class AddProjectDialog : public QDialog
{
	Q_OBJECT

public:
	explicit AddProjectDialog(QWidget *parent = 0);
	~AddProjectDialog();

	QString name() const;

private slots:
	void onOK();
	void onCancel();

private:
	Ui::AddProjectDialog *ui;
	QString m_name;
};

#endif // ADDPROJECTDIALOG_H
