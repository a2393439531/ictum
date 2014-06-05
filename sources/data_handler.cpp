#include "../headers/data_handler.h"
#include <QtSql>
#include <QDebug>

void DataHandler::connect()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("localhost");

	db.setDatabaseName("ICTUMTest");

	db.setUserName("root");
	db.setPassword("aeiouA123456789");

	if (!db.open()){
		qDebug()<<db.lastError();
		qDebug()<<"no conecto";
	}
	else {
		qDebug()<<"conected Sucessfully";
	}
}
