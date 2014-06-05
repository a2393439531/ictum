#include "../headers/physical_technology_component_add_edit_dialog.h"
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QTextEdit>
#include <QtSql>

PhysicalTechnologyComponentAddEditDialog::PhysicalTechnologyComponentAddEditDialog(QWidget* parent) : QDialog(parent)
{
	QVBoxLayout* physicalTechnologyComponentDialogMainLayout = new QVBoxLayout;    // creates the dialog layout
	QGridLayout* inputFieldsLayout = new QGridLayout;
	
	//initializes dialog widgets
	nameEdit = new QLineEdit;
	objectiveEdit = new QLineEdit;
	descriptionTextEdit = new QTextEdit;
	locationComboBox = new QComboBox;

	QSqlQueryModel* locationCatalogQueryModel = new QSqlQueryModel();
	locationCatalogQueryModel->setQuery("SELECT location FROM Locations");
	locationComboBox->setModel(locationCatalogQueryModel);

	
	QDialogButtonBox* PhysicalTechnologyComponentDialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox:: Cancel);

	//add widgets to the grid layout
	inputFieldsLayout->addWidget(new QLabel("Nombre"),0,0);
	inputFieldsLayout->addWidget(nameEdit,0,1);
	inputFieldsLayout->addWidget(new QLabel("Objetivo"),1,0);
	inputFieldsLayout->addWidget(objectiveEdit,1,1);
	inputFieldsLayout->addWidget(new QLabel("Descripcion"),2,0);
	inputFieldsLayout->addWidget(descriptionTextEdit,3,0);
	inputFieldsLayout->addWidget(new QLabel("Ubicacion:"),4,0);
	inputFieldsLayout->addWidget(locationComboBox,4,1);
	
	physicalTechnologyComponentDialogMainLayout->addLayout(inputFieldsLayout);
	physicalTechnologyComponentDialogMainLayout->addStretch();
	physicalTechnologyComponentDialogMainLayout->addWidget(PhysicalTechnologyComponentDialogButtonBox);
	this->setLayout(physicalTechnologyComponentDialogMainLayout);

	// signals slots connections
	connect(PhysicalTechnologyComponentDialogButtonBox, SIGNAL(accepted()),
			this,SLOT(accept()));
	connect(PhysicalTechnologyComponentDialogButtonBox, SIGNAL(rejected()),
			this,SLOT(reject()));
}
const QString PhysicalTechnologyComponentAddEditDialog::name() const
{
	return nameEdit->text();
}

const QString PhysicalTechnologyComponentAddEditDialog::objective() const
{
	return objectiveEdit->text();
}

const QString PhysicalTechnologyComponentAddEditDialog::description() const
{
	return descriptionTextEdit->toPlainText();
}

const QString PhysicalTechnologyComponentAddEditDialog::location() const
{
	return locationComboBox->currentText();
}

void PhysicalTechnologyComponentAddEditDialog::setName(const QString& aName)
{
	nameEdit->setText(aName);
}

void PhysicalTechnologyComponentAddEditDialog::setObjective(const QString& anObjective)
{
	objectiveEdit->setText(anObjective);
}

void PhysicalTechnologyComponentAddEditDialog::setDescription(const QString& aDescription)
{
	descriptionTextEdit->setPlainText(aDescription);
}
