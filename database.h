#ifndef DATABASE_DATABASE_H
#define DATABASE_DATABASE_H

#include <QPair>
#include <QString>
#include <QSqlDatabase>

/*------- class Database --------------------------------*/
class Database
{
public:
	Database();
	~Database();

	void setDatabasePath(const QString &path);
	QString databasePath() const;

	bool open();
	void close();

	bool addProject(const QString &name);
	bool removeProject(const QString &name);

	bool addData(const QString &projectName, const QString &dataName, const QString &data);
	bool removeData(const QString &dataName);

	QStringList projects() const;
	QList<QPair<QString, QString> > data(const QString &projectName) const;

private:
	QString m_path;
	QSqlDatabase m_db;

	int projectId(const QString &name) const;
};

#endif // DATABASE_DATABASE_H
