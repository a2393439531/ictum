#ifndef PROCESS_H
#define PROCESS_H

#include <QDialog>

class QTableView;

class Process : public QDialog
{
 Q_OBJECT 
 public:
	Process(QWidget* parent=0);
	void refreshProcessTable();
	private slots:
		void addProcess();
		void editProcess();
 private:
		QTableView* table;
};
#endif
