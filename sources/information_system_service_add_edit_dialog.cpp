#include "../headers/information_system_service_add_edit_dialog.h"
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QListView>
#include <QLabel>
#include <QtSql>
#include <QTextEdit>

InformationSystemServiceAddEditDialog::InformationSystemServiceAddEditDialog(QWidget* parent) : QDialog(parent)
{
	QVBoxLayout* issDialogMainLayout = new QVBoxLayout;    // creates the dialog layout
	QGridLayout* inputFieldsLayout = new QGridLayout;
	//initializes dialog widgets
	nameEdit = new QLineEdit;
	descriptionTextEdit = new QTextEdit;
	physicalTechCompComboBox = new QComboBox;

	//creates an sql query model to show information from the data base in the table	
   	QSqlQueryModel *ptcCatalogQueryModel = new QSqlQueryModel();
	ptcCatalogQueryModel->setQuery("SELECT name FROM PhysicalTechnologiesComponents");    //this query will be sent to the database	
	physicalTechCompComboBox->setModel(ptcCatalogQueryModel);

	QDialogButtonBox* issDialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox:: Cancel);

	//add widgets to the grid layout
	inputFieldsLayout->addWidget(new QLabel("Nombre"),0,0);
	inputFieldsLayout->addWidget(nameEdit,0,1);
	inputFieldsLayout->addWidget(new QLabel("Descripcion"),1,0);
	inputFieldsLayout->addWidget(descriptionTextEdit,2,0);
	inputFieldsLayout->addWidget(new QLabel("Alojado en"),3,0);
	inputFieldsLayout->addWidget(physicalTechCompComboBox,3,1);
	
	issDialogMainLayout->addLayout(inputFieldsLayout);
	issDialogMainLayout->addStretch();
	issDialogMainLayout->addWidget(issDialogButtonBox);
	this->setLayout(issDialogMainLayout);

	// signals slots connections
	connect(issDialogButtonBox, SIGNAL(accepted()),
			this,SLOT(accept()));
	connect(issDialogButtonBox, SIGNAL(rejected()),
			this,SLOT(reject()));
}

const QString InformationSystemServiceAddEditDialog::name() const
{
	return nameEdit->text();
}
const QString InformationSystemServiceAddEditDialog::description() const
{
	return descriptionTextEdit->toPlainText();
}
const QString InformationSystemServiceAddEditDialog::physicalTechnologyComponent() const
{
	return physicalTechCompComboBox->currentText();
}

void InformationSystemServiceAddEditDialog::setName(const QString& aName)
{
	nameEdit->setText(aName);
}
void InformationSystemServiceAddEditDialog::setDescription(const QString& aDescription)
{
	descriptionTextEdit->setPlainText(aDescription);
}
