#include "../headers/role_add_edit_dialog.h"
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QTextEdit>

RoleAddEditDialog::RoleAddEditDialog(QWidget* parent) : QDialog(parent)
{
	QVBoxLayout* roleDialogMainLayout = new QVBoxLayout;    // creates the dialog layout
	QGridLayout* inputFieldsLayout = new QGridLayout;
	
	//initializes dialog widgets
	nameEdit = new QLineEdit;
	objectiveEdit = new QLineEdit;
	tasksTextEdit = new QTextEdit;
	
	QDialogButtonBox* roleDialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox:: Cancel);

	//add widgets to the grid layout
	inputFieldsLayout->addWidget(new QLabel("Nombre"),0,0);
	inputFieldsLayout->addWidget(nameEdit,0,1);
	inputFieldsLayout->addWidget(new QLabel("Objetivo"),1,0);
	inputFieldsLayout->addWidget(objectiveEdit,1,1);
	inputFieldsLayout->addWidget(new QLabel("Tareas:"),2,0);
	inputFieldsLayout->addWidget(tasksTextEdit,3,0);
	
	roleDialogMainLayout->addLayout(inputFieldsLayout);
	roleDialogMainLayout->addStretch();
	roleDialogMainLayout->addWidget(roleDialogButtonBox);
	this->setLayout(roleDialogMainLayout);

	// signals slots connections
	connect(roleDialogButtonBox, SIGNAL(accepted()),
			this,SLOT(accept()));
	connect(roleDialogButtonBox, SIGNAL(rejected()),
			this,SLOT(reject()));
}
const QString RoleAddEditDialog::name() const
{
	return nameEdit->text();
}

const QString RoleAddEditDialog::objective() const
{
	return objectiveEdit->text();
}

const QString RoleAddEditDialog::tasks() const
{
	return tasksTextEdit->toPlainText();
}

void RoleAddEditDialog::setName(const QString& aName)
{
	nameEdit->setText(aName);
}

void RoleAddEditDialog::setObjective(const QString& anObjective)
{
	objectiveEdit->setText(anObjective);
}

void RoleAddEditDialog::setTasks(const QString& taks)
{
	tasksTextEdit->setPlainText(taks);
}
