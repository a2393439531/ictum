#include "../headers/function_add_edit_dialog.h"
#include "../headers/add_roles_helper_dialog.h"
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QTextEdit>
#include <QListView>
#include <QPushButton>
#include <QStandardItemModel>
#include <QDebug>
#include <QStandardItemModel>
#include <QtSql>

FunctionAddEditDialog::FunctionAddEditDialog(QWidget* parent) : QDialog(parent)
{
	QVBoxLayout* functionDialogMainLayout = new QVBoxLayout;    // creates the dialog layout
	QGridLayout* inputFieldsLayout = new QGridLayout;
	
	//initializes dialog widgets
	nameEdit = new QLineEdit;
	descriptionTextEdit = new QTextEdit;
	usedByListView = new QListView;
	QPushButton* addRolesButton = new QPushButton("Agregar");

	QDialogButtonBox* functionDialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox:: Cancel);

	//add widgets to the grid layout
	inputFieldsLayout->addWidget(new QLabel("Nombre"),0,0);
	inputFieldsLayout->addWidget(nameEdit,0,1);
	inputFieldsLayout->addWidget(new QLabel("Descripcion:"),1,0);
	inputFieldsLayout->addWidget(descriptionTextEdit,2,0);
	inputFieldsLayout->addWidget(new QLabel("Usada por"),3,0);
	inputFieldsLayout->addWidget(addRolesButton,3,1);
	inputFieldsLayout->addWidget(usedByListView,4,0);
	
	functionDialogMainLayout->addLayout(inputFieldsLayout);
	functionDialogMainLayout->addStretch();
	functionDialogMainLayout->addWidget(functionDialogButtonBox);
	this->setLayout(functionDialogMainLayout);

	// signals slots connections
	connect(functionDialogButtonBox, SIGNAL(accepted()),
			this,SLOT(accept()));
	connect(functionDialogButtonBox, SIGNAL(rejected()),
			this,SLOT(reject()));
	connect(addRolesButton, SIGNAL(clicked()),
			this, SLOT(addRoles()));
}

void FunctionAddEditDialog::addRoles()
{
	AddRolesHelperDialog* dlgHelper = new AddRolesHelperDialog(this);
	QStandardItemModel* selectedRolesModel = new QStandardItemModel;
	int row=0; //keeps track of the rows when the returning selected items from dlgHelper

	if (dlgHelper->exec()==QDialog::Accepted){
		foreach(QModelIndex itemIndex, dlgHelper->rolesList->selectionModel()->selectedIndexes()){
			QStandardItem* i = new QStandardItem(dlgHelper->rolesList->model()->index(itemIndex.row(), itemIndex.column()).data().toString());
			selectedRolesModel->setItem(row++, itemIndex.column(), i); //add an item to the usedBy model(which is selectedRolesModel)
		}
		usedByListView->setModel(selectedRolesModel);
	}
}

const QString FunctionAddEditDialog::name() const
{
	return nameEdit->text();
} 

const QString FunctionAddEditDialog::description() const
{
	return descriptionTextEdit->toPlainText();
}

const QString FunctionAddEditDialog::usedBy() const
{
	int column = 0; 
	int row  = 0;
	QString listElements;
	while(usedByListView->model()->index(row, column).isValid())
		listElements += usedByListView->model()->index(row++,column).data().toString() + ";";
		
	return listElements;
}

void FunctionAddEditDialog::setName(const QString& aName)
{
	nameEdit->setText(aName);
}
void FunctionAddEditDialog::setDescription(const QString& aDescription)
{
	descriptionTextEdit->setPlainText(aDescription);
}

void FunctionAddEditDialog::setUsedBy()
{
	QSqlQuery roleList;
	QStandardItemModel* roles = new QStandardItemModel();
	int row = 0;
	roleList.exec("SELECT (SELECT name FROM Roles WHERE Roles.rol_id = RolesFunctions.rol_id) AS Role FROM RolesFunctions GROUP BY Role");
	while(roleList.next()){
		QStandardItem* Item = new QStandardItem(roleList.value(0).toString());
		roles->setItem(row++,0,Item);
	}
	qDebug()<<roleList.lastError();
	usedByListView->setModel(roles);
}
