#include<../headers/ou_add_edit_dialog.h>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QTextEdit>
#include <QtSql>

OuAddEditDialog::OuAddEditDialog(QWidget* parent) : QDialog(parent)
{
	QVBoxLayout* ouDialogMainLayout = new QVBoxLayout;    // creates the dialog layout
	QGridLayout* inputFieldsLayout = new QGridLayout;
	//initializes dialog widgets
	nameEdit = new QLineEdit;
	objectiveEdit = new QLineEdit;
	tasksTextEdit = new QTextEdit;
	locationComboBox = new QComboBox;

	QSqlQueryModel* locationComboBoxModel = new QSqlQueryModel();
	locationComboBoxModel->setQuery("SELECT location FROM Locations");
	locationComboBox->setModel(locationComboBoxModel);

	QDialogButtonBox* ouDialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox:: Cancel);
	

	//add widgets to the grid layout
	inputFieldsLayout->addWidget(new QLabel("Nombre"),0,0);
	inputFieldsLayout->addWidget(nameEdit,0,1);
	inputFieldsLayout->addWidget(new QLabel("Objetivo"),1,0);
	inputFieldsLayout->addWidget(objectiveEdit,1,1);
	inputFieldsLayout->addWidget(new QLabel("Ubicacion"),2,0);
	inputFieldsLayout->addWidget(locationComboBox,2,1);
	inputFieldsLayout->addWidget(new QLabel("Tareas"),3,0);
	inputFieldsLayout->addWidget(tasksTextEdit,4,0);

	ouDialogMainLayout->addLayout(inputFieldsLayout);
	ouDialogMainLayout->addStretch();
	ouDialogMainLayout->addWidget(ouDialogButtonBox);
	this->setLayout(ouDialogMainLayout);

	// signals slots connections
	connect(ouDialogButtonBox, SIGNAL(accepted()),
			this,SLOT(accept()));
	connect(ouDialogButtonBox, SIGNAL(rejected()),
			this,SLOT(reject()));
}

const QString OuAddEditDialog::name() const
{
	return nameEdit->text();
}

const QString OuAddEditDialog::objective() const
{
	return  objectiveEdit->text();
}

const QString OuAddEditDialog::location() const 
{
	return locationComboBox->currentText();
}

const QString OuAddEditDialog::tasks() const
{
	return tasksTextEdit->toPlainText();
}

void OuAddEditDialog::setName(const QString& aName)
{
	nameEdit->setText(aName);
}

void OuAddEditDialog::setObjective(const QString& anObjective)
{
	objectiveEdit->setText(anObjective);
}

void OuAddEditDialog::setTasks(const QString& tasks)
{
	tasksTextEdit->setPlainText(tasks);
}
