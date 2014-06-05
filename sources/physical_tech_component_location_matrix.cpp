#include "../headers/physical_tech_component_location_matrix.h"
#include <QTableView>
#include <QVBoxLayout>
#include <QtSql>
#include <QDebug>
#include <QDialogButtonBox>

PhysicalTechComponentLocationMatrix::PhysicalTechComponentLocationMatrix(QWidget* parent) : QDialog(parent)
{
	QVBoxLayout* mainlayout = new QVBoxLayout;
	physicalTechComponentLocationMatrixTable = new QTableView;
	
	QSqlQueryModel* physicalTechComponentLocationMatrixModel = new QSqlQueryModel();
	physicalTechComponentLocationMatrixModel->setQuery("SELECT name, (SELECT location FROM Locations WHERE Locations.location_id = PhysicalTechnologiesComponents.location) FROM PhysicalTechnologiesComponents");
	physicalTechComponentLocationMatrixTable->setModel(physicalTechComponentLocationMatrixModel);
	
	QDialogButtonBox* physicalTechnologyComponentMatrixButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
	

	mainlayout->addWidget(physicalTechComponentLocationMatrixTable);
	mainlayout->addWidget(physicalTechnologyComponentMatrixButtonBox);
	this->setLayout(mainlayout);

	connect(physicalTechnologyComponentMatrixButtonBox, SIGNAL(accepted()),
			this,SLOT(accept()));
	connect(physicalTechnologyComponentMatrixButtonBox, SIGNAL(rejected()),
			this,SLOT(reject()));
}
