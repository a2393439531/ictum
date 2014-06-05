#ifndef FUNCTION_H
#define FUNCTION_H

#include <QDialog>

class QTableView;

class Function : public QDialog
{
	Q_OBJECT
 public: 
	Function(QWidget* parent=0);
	void refreshFunctionTable();
	private slots:
		void addFunction();
		void editFunction();

 private:
		QTableView* table;
};
#endif
