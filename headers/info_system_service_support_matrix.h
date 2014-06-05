#ifndef INFO_SYSTEM_SERVICES_SUPPORT_MATRIX_H
#define INFO_SYSTEM_SERVICES_SUPPORT_MATRIX_H

#include <QDialog>

class QListView;
class QTableView;
class QStandardItemModel;

class InfoSystemServiceSupportMatrix : public QDialog
{
 Q_OBJECT
 
 public:
	InfoSystemServiceSupportMatrix(QWidget* parent = 0);
	private slots:
		void addSupportRelation();
		void delSupportRelationElement();
		void revealISS(const QModelIndex&);

 private:
	QListView* iSSList;
	QTableView* iSSTable;
	QStandardItemModel* iSSListModel;
};
#endif
