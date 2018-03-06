#ifndef DATABASE_DATABASE_H
#define DATABASE_DATABASE_H

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

	QStringList projects() const;

private:
	QString m_path;
	QSqlDatabase m_db;
};

#endif // DATABASE_DATABASE_H
