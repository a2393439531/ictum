#ifndef ROLE_FUNCTION_MATRIX_H
#define ROLE_FUNCTION_MATRIX_H

#include <QDialog>

class QListView;
class QTableView;
class QStandardItemModel;

class RoleFunctionMatrix : public QDialog
{
 Q_OBJECT
 
 public:
	RoleFunctionMatrix(QWidget* parent = 0);
	private slots:
		void addFunctionRoleRelation();
		void delFunctionRoleRelationElement();
		void revealRoles(const QModelIndex&);

 private:
	QListView* rolesList;
	QTableView* functionTable;
	QStandardItemModel* rolesListModel;
};
#endif
