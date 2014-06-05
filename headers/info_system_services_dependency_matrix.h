#ifndef INFO_SYSTEM_SERVICES_DEPENDENCY_MATRIX_H
#define INFO_SYSTEM_SERVICES_DEPENDENCY_MATRIX_H

#include <QDialog>

class QListView;
class QTableView;
class QStandardItemModel;

class InfoSystemServicesDependencyMatrix : public QDialog
{
 Q_OBJECT
 
 public:
	InfoSystemServicesDependencyMatrix(QWidget* parent = 0);
	private slots:
		void addDependencyRelation();
		void delDependencyRelationElement();
		void revealISS(const QModelIndex&);

 private:
	QListView* iSSList;
	QTableView* iSSTable;
	QStandardItemModel* iSSListModel;};
#endif
