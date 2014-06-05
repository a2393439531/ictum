#ifndef DATA_ENTITY_H
#define DATA_ENTITY_H

#include<QDialog>

class QTableView;

class DataEntity : public QDialog
{

 Q_OBJECT

 public:
    DataEntity(QWidget* parent= 0);
	void refreshDataEntityTable();
 
	private slots:
		void addDataEntity();
		void editDataEntity();
		
  private:
	QTableView* table;
};
#endif
