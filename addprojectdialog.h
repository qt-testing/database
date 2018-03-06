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

	void setProjects(const QStringList &projects);

	QString name() const;

private slots:
	void onOK();
	void onCancel();
	void checkName(const QString &);

private:
	Ui::AddProjectDialog *ui;
	QString m_name;
	QStringList m_projects;
};

#endif // ADDPROJECTDIALOG_H
