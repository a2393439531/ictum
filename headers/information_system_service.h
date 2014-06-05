#ifndef INFORMATION_SYSTEM_SERVICE_H
#define INFORMATION_SYSTEM_SERVICE_H

#include <QDialog>

class QTableView;

class InformationSystemService : public QDialog
{
 Q_OBJECT
 
 public:
	InformationSystemService(QWidget* parent = 0);
	void refreshInformationSystemServiceTable();

	private slots:
		void addInformationSystemService();
		void editInformationSystemService();


 private:
	QTableView* table;


};
#endif
