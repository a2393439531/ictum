#include "../headers/actor_add_edit_dialog.h"
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QtSql>

ActorAddEditDialog::ActorAddEditDialog(QWidget* parent) : QDialog(parent)
{
	QVBoxLayout* actorDialogMainLayout = new QVBoxLayout;    // creates the dialog layout
	QGridLayout* inputFieldsLayout = new QGridLayout;
	//initializes dialog widgets
	nameEdit = new QLineEdit;
	middleNameEdit = new QLineEdit;
	lastNameEdit = new QLineEdit;
	roleComboBox = new QComboBox;
	ouComboBox = new QComboBox;
	
	//creates an sql query model to show information from the data base in the table	
   	QSqlQueryModel *rolesCatalogQueryModel = new QSqlQueryModel();
	rolesCatalogQueryModel->setQuery("SELECT name FROM Roles");    //this query will be sent to the database	
	roleComboBox->setModel(rolesCatalogQueryModel);

	//creates an sql query model to show infor	mation from the data base in the table	
   	QSqlQueryModel *ouCatalogQueryModel = new QSqlQueryModel();
	ouCatalogQueryModel->setQuery("SELECT name FROM OrganizationalUnits");    //this query will be sent to the database	
	ouComboBox->setModel(ouCatalogQueryModel);
	
	QDialogButtonBox* actorDialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox:: Cancel);

	//add widgets to the grid layout
	inputFieldsLayout->addWidget(new QLabel("Nombre"),0,0);
	inputFieldsLayout->addWidget(nameEdit,0,1);
	inputFieldsLayout->addWidget(new QLabel("Segundo Nombre"),1,0);
	inputFieldsLayout->addWidget(middleNameEdit,1,1);
	inputFieldsLayout->addWidget(new QLabel("Apellido"),2,0);
	inputFieldsLayout->addWidget(lastNameEdit,2,1);
	inputFieldsLayout->addWidget(new QLabel("Rol"),3,0);
	inputFieldsLayout->addWidget(roleComboBox,3,1);
	inputFieldsLayout->addWidget(new QLabel("Organizational Unit"),4,0);
	inputFieldsLayout->addWidget(ouComboBox,4,1);

	actorDialogMainLayout->addLayout(inputFieldsLayout);
	actorDialogMainLayout->addStretch();
	actorDialogMainLayout->addWidget(actorDialogButtonBox);
	this->setLayout(actorDialogMainLayout);

	// signals slots connections
	connect(actorDialogButtonBox, SIGNAL(accepted()),
			this,SLOT(accept()));
	connect(actorDialogButtonBox, SIGNAL(rejected()),
			this,SLOT(reject()));
}

const QString ActorAddEditDialog::name() const
{
	return nameEdit->text();
}

const QString ActorAddEditDialog::middleName() const
{
	return middleNameEdit->text();
}

const QString ActorAddEditDialog::lastName() const
{
	return lastNameEdit->text();
}

const QString ActorAddEditDialog::role() const
{
	return roleComboBox->currentText();
}

const QString ActorAddEditDialog::ou() const
{
	return ouComboBox->currentText();
}

void ActorAddEditDialog::setName(const QString& aName)
{
	this->nameEdit->setText(aName);
}

void ActorAddEditDialog::setLastName(const QString& aLastName)
{
	this->lastNameEdit->setText(aLastName);
}

void ActorAddEditDialog::setMiddleName(const QString& aMiddleName)
{
	this->middleNameEdit->setText(aMiddleName);
}

void ActorAddEditDialog::setRole(const QString& aRole)
{
	this->roleComboBox->setEditText(aRole);
}

void ActorAddEditDialog::setOu(const QString& anOu)
{
	this->ouComboBox->setEditText(anOu);
}
