#include "database.h"
#include <QDebug>
#include <QStringList>
#include <QSqlError>
#include <QSqlQuery>

/*------- class Database --------------------------------*/
Database::Database()
{
	m_db = QSqlDatabase::addDatabase("QSQLITE");
}

Database::~Database()
{
}

void Database::setDatabasePath(const QString &path)
{
	m_path = path;
}

QString Database::databasePath() const
{
	return m_path;
}

bool Database::open()
{
	if (m_path.isEmpty()) {
		return false;
	}

	QStringList drivers = m_db.drivers();

	foreach (QString driver, drivers) {
		qDebug() << driver;
	}

	m_db.setDatabaseName(m_path);

	if (!m_db.open()) {
		return false;
	}

	QSqlQuery query;
	query.prepare("CREATE TABLE IF NOT EXISTS Projects("
				  "Id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
				  "Name TEXT)");
	if (!query.exec()) {
		qDebug() << query.lastError().text();
		return false;
	}

	query.prepare("CREATE TABLE IF NOT EXISTS Data("
				  "Id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
				  "ProjectId INTEGER,"
				  "Name TEXT,"
				  "Data TEXT)");
	if (!query.exec()) {
		qDebug() << query.lastError().text();
		return false;
	}

	return true;
}

void Database::close()
{
	m_db.close();
}

bool Database::addProject(const QString &name)
{
	QSqlQuery query;
	QString tmp = QString("INSERT INTO Projects (Name) VALUES ('%1')").arg(name);
	query.prepare(tmp);
	if (!query.exec()) {
		qDebug() << query.lastError().text();
		return false;
	}

	return true;
}

bool Database::removeProject(const QString &name)
{
	const int projectId = this->projectId(name);

	QSqlQuery query;
	query.prepare("DELETE FROM Projects WHERE Name = ?");
	query.addBindValue(name);
	if (!query.exec()) {
		qDebug() << query.lastError().text();
		return false;
	}

	query.prepare("DELETE FROM Data WHERE ProjectId = ?");
	query.addBindValue(projectId);
	if (!query.exec()) {
		qDebug() << query.lastError().text();
	}

	return true;
}

bool Database::addData(const QString &projectName, const QString &dataName, const QString &data)
{
	int projectId = this->projectId(projectName);

	QString strQuery = QString("INSERT INTO Data "
							   "(ProjectId, Name, Data) "
							   "VALUES (%1, '%2', '%3')").
					   arg(projectId).
					   arg(dataName).
					   arg(data);

	QSqlQuery query;
	query.prepare(strQuery);
	if (!query.exec()) {
		qDebug() << query.lastError().text();
		return false;
	}

	return true;
}

bool Database::removeData(const QString &projectName, const int index)
{
	const int projectId = this->projectId(projectName);

	QSqlQuery query;
	query.prepare("SELECT * FROM Data WHERE ProjectId = ?");
	query.addBindValue(projectId);
	if (!query.exec()) {
		qDebug() << query.lastError().text();
		return false;
	}

	QList<int> ids;
	while (query.next()) {
		ids.append(query.value(0).toInt());
	}

	if (index < ids.count()) {
		query.prepare("DELETE FROM Data WHERE Id = ?");
		query.addBindValue(ids[index]);
		if (!query.exec()) {
			qDebug() << query.lastError().text();
			return false;
		}
	}

	return true;
}

QStringList Database::projects() const
{
	QStringList projects;

	QSqlQuery query;
	query.prepare("SELECT Name FROM Projects");
	if (!query.exec()) {
		qDebug() << query.lastError().text();
		return projects;
	}

	while (query.next()) {
		projects.append(query.value(0).toString());
	}

	return projects;
}

QList<QPair<QString, QString> > Database::data(const QString &projectName) const
{
	int projectId = this->projectId(projectName);

	QList<QPair<QString, QString> > result;

	QSqlQuery query;
	query.prepare("SELECT Name, Data FROM Data "
				  "WHERE ProjectId = ?");
	query.addBindValue(projectId);
	if (!query.exec()) {
		qDebug() << query.lastError().text();
		return result;
	}

	while (query.next()) {
		QPair<QString, QString> pair;
		pair.first = query.value(0).toString();
		pair.second = query.value(1).toString();
		result << pair;
	}

	return result;
}

int Database::projectId(const QString &name) const
{
	int projectId = -1;

	QSqlQuery query;
	query.prepare("SELECT Id FROM Projects "
				  "WHERE Name = ?");
	query.addBindValue(name);
	if (!query.exec()) {
		qDebug() << query.lastError().text();
		return projectId;
	}

	while (query.next()) {
		projectId = query.value(0).toInt();
	}

	return projectId;
}
