#include "../headers/navigation.h"
#include "../headers/roles_navigation.h"
#include "ou_navigation.h"
#include "../headers/mainwindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QTableView>
#include <QGroupBox>
#include <QGridLayout>
#include <QtSql>
#include <QListView>
#include <QLayoutItem>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QStandardItemModel>
#include <QStack>

OuNavigation::OuNavigation(QWidget* parent) : QWidget(parent)
{
	QGridLayout* dataViewLayout = new QGridLayout();
	QSqlQueryModel* currentAnalyzedEntityTableModel = new QSqlQueryModel;
	QStandardItemModel* relatedEntitiesModel = new QStandardItemModel;

	relatedEntitiesModel->setItem(0,0,new QStandardItem("Actores"));
	relatedEntitiesModel->setItem(1,0,new QStandardItem("Funciones"));
		
	/* initiealizes the widgets*/
	currentAnalyzedEntityTable = new QTableView;
	releatedEntityInformationListView = new QListView;
	descriptionTextEdit = new QTextEdit;
	QLineEdit* searchEdit = new QLineEdit;
	relatedEntitiesListView = new QListView;
	elementDescriptionTextEdit = new QTextEdit;
	QPushButton* back = new QPushButton("<-Atras");

	relatedEntitiesListView->setModel(relatedEntitiesModel);  //displays elements of the relatedEntities Model in the list view;
	
	searchEdit->setPlaceholderText("Search");  //puts search in the QLineEdit while is empty

	currentAnalyzedEntityTable->setSelectionBehavior(QAbstractItemView::SelectRows);   //selects entires rows
	currentAnalyzedEntityTable->setSelectionMode(QAbstractItemView::SingleSelection);  //two rows can't be selected at the same time
	
	
	currentAnalyzedEntityTableModel->setQuery("SELECT ou_id, name FROM OrganizationalUnits"); // takes information from the database
	currentAnalyzedEntityTable->setModel(currentAnalyzedEntityTableModel);  //display data in the table view
	
	//places items in the screen
	dataViewLayout->addWidget(back,1,0,1,1);
	dataViewLayout->addWidget(searchEdit,2,0);
	dataViewLayout->addWidget(currentAnalyzedEntityTable,3,0);
	dataViewLayout->addWidget(new QLabel("Entidades Relacionadas"),2,1);
	dataViewLayout->addWidget(relatedEntitiesListView,3,1);
	dataViewLayout->addWidget(releatedEntityInformationListView,3,2);
	dataViewLayout->addWidget(new QLabel("Descripcion"),4,0);
	dataViewLayout->addWidget(descriptionTextEdit,5,0,1,2);
	dataViewLayout->addWidget(new QLabel("Descripcion del Elemento"),4,2);
	dataViewLayout->addWidget(elementDescriptionTextEdit,5,2,1,2);
	
	this->setLayout(dataViewLayout);    //show widgets

	connect(currentAnalyzedEntityTable, SIGNAL(clicked(const QModelIndex&)),
			this, SLOT(oUEntities(const QModelIndex&)));
	connect(searchEdit, SIGNAL(textChanged(const QString&)),
			this, SLOT(oUSearch(const QString&))); 
	connect(releatedEntityInformationListView, SIGNAL(clicked(const QModelIndex&)),
			this, SLOT(showOuEntitiesElementInfo(const QModelIndex&)));
	
}

void OuNavigation::oUEntities(const QModelIndex& index)
{
	//isFirstTime = false;
	
	QSqlQueryModel* relatedEntitiesListModel = new QSqlQueryModel;
	QSqlQuery* getDescription = new QSqlQuery;
	QString descriptionInfo;
	
	QString formatedDescriptionInfo = "This Role Tasks are: \n";
	QList<QString> formatInfo;

	if((relatedEntitiesListView->model()->index(relatedEntitiesListView->selectionModel()->currentIndex().row(),0).data().toString()) == "Actores"){
		
		//takes information from the database	
		relatedEntitiesListModel->setQuery(QString("SELECT name FROM Actors WHERE ou_id = '%1'").arg(currentAnalyzedEntityTable->model()->index(index.row(),0).data().toString()));
		releatedEntityInformationListView->setModel(relatedEntitiesListModel); // display data in the list view
	
		getDescription->exec(QString("SELECT tasks FROM OrganizationalUnits WHERE ou_id = %1").arg(currentAnalyzedEntityTable->model()->index(index.row(),0).data().toString()));
		while(getDescription->next())
			descriptionInfo += getDescription->value(0).toString();
	}
	else if((relatedEntitiesListView->model()->index(relatedEntitiesListView->selectionModel()->currentIndex().row(),0).data().toString()) == "Funciones"){
		
		relatedEntitiesListModel->setQuery(QString("SELECT Functions.name FROM OrganizationalUnits JOIN Actors ON OrganizationalUnits.ou_id = Actors.ou_id JOIN RolesFunctions ON Actors.rol_id = RolesFunctions.rol_id JOIN Functions ON RolesFunctions.function_id = Functions.function_id WHERE OrganizationalUnits.ou_id = %1 GROUP BY Functions.name").arg(currentAnalyzedEntityTable->model()->index(index.row(),0).data().toString()));

		releatedEntityInformationListView->setModel(relatedEntitiesListModel); // display data in the list view
	
		getDescription->exec(QString("SELECT tasks FROM OrganizationalUnits WHERE ou_id = %1").arg(currentAnalyzedEntityTable->model()->index(index.row(),0).data().toString()));
		while(getDescription->next())
			descriptionInfo += getDescription->value(0).toString();
	}
	
	
	formatInfo = descriptionInfo.split(",", QString::SkipEmptyParts);  //break the string tha comes out form the database in parts
	
	// gives format to the string that is comming from the database
	foreach(QString e, formatInfo){
		//e+= "\n";
		formatedDescriptionInfo += e +"\n" ;
	}
	descriptionTextEdit->setPlainText(formatedDescriptionInfo);

}

void OuNavigation::showOuEntitiesElementInfo(const QModelIndex& index)
{
	QSqlQuery getDescription;
    QString elementName = releatedEntityInformationListView->model()->index(index.row(),0).data().toString();
	QString selectedRelatedEntity = relatedEntitiesListView->model()->index(relatedEntitiesListView->selectionModel()->currentIndex().row(),0).data().toString();
	QString description;

	if (selectedRelatedEntity == "Funciones"){
		getDescription.exec(QString("SELECT description FROM Functions WHERE name = '%1'").arg(elementName));
		getDescription.lastError();
		while(getDescription.next())
			description = getDescription.value(0).toString();
	}
	elementDescriptionTextEdit->setPlainText(description);								   
}


void OuNavigation::oUSearch(const QString& text)
{
    /* search roles using the user input in the LineEdit*/
	
	QSqlQueryModel* searchRoles = new QSqlQueryModel;
    /*******************************************Roles Scren***********************************************************************/
    if (text != "")
	    searchRoles->setQuery(QString("SELECT ou_id, name FROM OrganizationalUnits WHERE name LIKE '%1%'").arg(text));
	else
	    searchRoles->setQuery("SELECT ou_id, name FROM OrganizationalUnits");
	
    // Display the Query results
    currentAnalyzedEntityTable->setModel(searchRoles);
}
