#ifndef LOCATION_H
#define LOCATION_H

#include <QDialog>

class QTableView;

class Location : public QDialog
{
	Q_OBJECT
	
 public: 
	Location(QWidget* parent);
	void refreshLocationTable();
	
	private slots:
		void addLocation();
		void editLocation();
		
 private:
	QTableView* table;
};
#endif
