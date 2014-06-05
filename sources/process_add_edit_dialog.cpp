#include "../headers/process_add_edit_dialog.h"
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QTextEdit>
#include <QtSql>

ProcessAddEditDialog::ProcessAddEditDialog(QWidget* parent) : QDialog(parent)
{
	QVBoxLayout* processDialogMainLayout = new QVBoxLayout;    // creates the dialog layout
	QGridLayout* inputFieldsLayout = new QGridLayout;

	//initializes dialog widgets
	nameEdit = new QLineEdit;
	objectiveEdit = new QLineEdit;
	descriptionTextEdit = new QTextEdit;
	
	QDialogButtonBox* processDialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox:: Cancel);
	
	//add widgets to the grid layout
	inputFieldsLayout->addWidget(new QLabel("Nombre"),0,0);
	inputFieldsLayout->addWidget(nameEdit,0,1);
	inputFieldsLayout->addWidget(new QLabel("Objetivo"),1,0);
	inputFieldsLayout->addWidget(objectiveEdit,1,1);
	inputFieldsLayout->addWidget(new QLabel("Descripcion"),2,0);
	inputFieldsLayout->addWidget(descriptionTextEdit,3,0);

	processDialogMainLayout->addLayout(inputFieldsLayout);
	processDialogMainLayout->addStretch();
	processDialogMainLayout->addWidget(processDialogButtonBox);
	this->setLayout(processDialogMainLayout);

	// signals slots connections
	connect(processDialogButtonBox, SIGNAL(accepted()),
			this,SLOT(accept()));
	connect(processDialogButtonBox, SIGNAL(rejected()),
			this,SLOT(reject()));
}

const QString ProcessAddEditDialog::name() const
{
	return nameEdit->text();
}

const QString ProcessAddEditDialog::objective() const
{
	return  objectiveEdit->text();
}

const QString ProcessAddEditDialog::description () const
{
	return descriptionTextEdit->toPlainText();
}

void ProcessAddEditDialog::setName(const QString& aName)
{
	nameEdit->setText(aName);
}

void ProcessAddEditDialog::setObjective(const QString& anObjective)
{
	objectiveEdit->setText(anObjective);
}

void ProcessAddEditDialog::setDescription(const QString& aDescription)
{
	descriptionTextEdit->setPlainText(aDescription);
}
