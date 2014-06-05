#ifndef ROLE_PROCESS_MATRIX_H
#define ROLE_PROCESS_MATRIX_H

#include <QDialog>

class QListView;
class QTableView;
class QStandardItemModel;

class RoleProcessMatrix : public QDialog
{
 Q_OBJECT
 
 public:
	RoleProcessMatrix(QWidget* parent = 0);
	private slots:
		void addRoleProcessRelation();
		void delRoleProcessRelationElement();
		void revealProcesses(const QModelIndex&);

 private:
	QListView* processesList;
	QTableView* rolesTable;
	QStandardItemModel* processesListModel;
};
#endif
