#ifndef PHYSICAL_TECHNOLOGY_COMPONENT_H
#define PHYSICAL_TECHNOLOGY_COMPONENT_H

#include <QDialog>

class QTableView;

class PhysicalTechnologyComponent : public QDialog
{
	Q_OBJECT

 public:
	PhysicalTechnologyComponent(QWidget* parent = 0);
	void refreshPhysicalTechnologyComponentTable();

	private slots:
		void addPhysicalTechnologyComponent();
		void editPhysicalTechnologyComponent();
 private:
	QTableView* table;
};
#endif
