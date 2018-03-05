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

	return true;
}

void Database::close()
{
	m_db.close();
}

bool Database::addProject(const QString &name)
{
	QSqlQuery query;
	QString tmp = QString("INSERT INTO Projects (Name) VALUES ('%1');").arg(name);
	query.prepare(tmp);
	if (!query.exec()) {
		qDebug() << query.lastError().text();
		return false;
	}

	return true;
}
