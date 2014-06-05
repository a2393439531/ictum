#ifndef PHYSICAL_TECH_COMPONENT_LOCATION_MATRIX_H
#define PHYSICAL_TECH_COMPONENT_LOCATION_MATRIX_H

#include <QDialog>

class QTableView;

class PhysicalTechComponentLocationMatrix : public QDialog
{
 public:
	PhysicalTechComponentLocationMatrix(QWidget* parent = 0);
 private:
	QTableView* physicalTechComponentLocationMatrixTable;
};
#endif
