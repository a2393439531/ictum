#include "../headers/data_entity_add_edit_dialog.h"
#include "../headers/add_roles_helper_dialog.h"
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QPushButton>
#include <QListView>
#include <QtSql>

DataEntityAddEditDialog::DataEntityAddEditDialog(QWidget* parent) : QDialog(parent)
{
	QVBoxLayout* dataEntityDialogMainLayout = new QVBoxLayout;    // creates the dialog layout
	QGridLayout* inputFieldsLayout = new QGridLayout;
	//initializes dialog widgets
	
	nameEdit = new QLineEdit;
	descriptionTextEdit = new QTextEdit;
	processedByComboBox = new QComboBox;
	
	QSqlQueryModel* processedQueryModel = new QSqlQueryModel();
	processedQueryModel->setQuery("SELECT name FROM InformationSystemServices");
	processedByComboBox->setModel(processedQueryModel);

	QDialogButtonBox* dataEntityDialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox:: Cancel);

	//add widgets to the grid layout
	inputFieldsLayout->addWidget(new QLabel("Nombre"),0,0);
	inputFieldsLayout->addWidget(nameEdit,0,1);
	inputFieldsLayout->addWidget(new QLabel("Description"),1,0);
	inputFieldsLayout->addWidget(descriptionTextEdit,2,0);
	inputFieldsLayout->addWidget(new QLabel("Procesada Por"),3,0);
	inputFieldsLayout->addWidget(processedByComboBox,3,1);
	
	dataEntityDialogMainLayout->addLayout(inputFieldsLayout);
	dataEntityDialogMainLayout->addStretch();
	dataEntityDialogMainLayout->addWidget(dataEntityDialogButtonBox);
	this->setLayout(dataEntityDialogMainLayout);

	// signals slots connections
	connect(dataEntityDialogButtonBox, SIGNAL(accepted()),
			this,SLOT(accept()));
	connect(dataEntityDialogButtonBox, SIGNAL(rejected()),
			this,SLOT(reject()));
	
}

/*void DataEntityAddEditDialog::addRoles()
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
	}*/

const QString DataEntityAddEditDialog::name() const
{
	return nameEdit->text();
}

const QString DataEntityAddEditDialog::description() const
{
	return descriptionTextEdit->toPlainText();
}

const QString DataEntityAddEditDialog::processedBy() const
{
	return processedByComboBox->currentText();
}

void DataEntityAddEditDialog::setName(const QString& aName)
{
	nameEdit->setText(aName);
}

void DataEntityAddEditDialog::setDescription(const QString& aDescription)
{
	descriptionTextEdit->setPlainText(aDescription);
}
