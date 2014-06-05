#ifndef ORGANIZATIONAL_UNIT_H
#define ORGANIZATIONAL_UNIT_H

#include <QDialog>

class QTableView;

class OrganizationalUnit : public QDialog
{
 Q_OBJECT 
 public:
	OrganizationalUnit(QWidget* parent=0);
	void refreshOuTable();
	private slots:
		void addOrganizationalUnit();
		void editOrganizationalUnit();
 private:
		QTableView* table;
};
#endif
