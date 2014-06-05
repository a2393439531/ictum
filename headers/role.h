#ifndef ROLE_H
#define ROLE_H

#include <QDialog>

class QTableView;

class Role : public QDialog
{
	Q_OBJECT

 public:
	Role(QWidget* parent=0);
	void refreshRoleTable();
	
	private slots:
		void addRole();
		void editRole();
 private:
		QTableView* table;
};
#endif
