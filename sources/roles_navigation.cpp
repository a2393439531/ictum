#include "../headers/roles_navigation.h"
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

RolesNavigation::RolesNavigation(QWidget* parent) : QWidget(parent)
{

	QGridLayout* dataViewLayout = new QGridLayout();
	QSqlQueryModel* currentAnalyzedEntityTableModel = new QSqlQueryModel;
	QStandardItemModel* relatedEntitiesModel = new QStandardItemModel;

    relatedEntitiesModel->setItem(0,0,new QStandardItem("Actores"));
	relatedEntitiesModel->setItem(1,0,new QStandardItem("Funciones"));
	relatedEntitiesModel->setItem(2,0,new QStandardItem("Procesos"));

	
	/* initiealizes the widgets*/
	currentAnalyzedEntityTable = new QTableView;
	releatedEntityInformationListView = new QListView;
	descriptionTextEdit = new QTextEdit;
	QLineEdit* searchEdit = new QLineEdit;
	relatedEntitiesListView = new QListView;
	QPushButton* back = new QPushButton("<-Atras");
	elementDescriptionTextEdit = new QTextEdit;

	relatedEntitiesListView->setModel(relatedEntitiesModel);  //displays elements of the relatedEntities Model in the list view;
	
	searchEdit->setPlaceholderText("Search");  //puts search in the QLineEdit while is empty

	currentAnalyzedEntityTable->setSelectionBehavior(QAbstractItemView::SelectRows);   //selects entires rows
	currentAnalyzedEntityTable->setSelectionMode(QAbstractItemView::SingleSelection);  //two rows can't be selected at the same time
	
	
	currentAnalyzedEntityTableModel->setQuery("SELECT rol_id, name FROM Roles"); // takes information from the database
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
			this, SLOT(rolesEntities(const QModelIndex&)));
	connect(searchEdit, SIGNAL(textChanged(const QString&)),
			this, SLOT(rolesSearch(const QString&)));
	connect(releatedEntityInformationListView, SIGNAL(clicked(const QModelIndex&)),
			this, SLOT(showRolesEntitiesElementInfo(const QModelIndex&)));
}
  
void RolesNavigation::rolesEntities(const QModelIndex& index)
{
	//isFirstTime = false;
	//currentScreen = "rolesScreen";
	QSqlQueryModel* relatedEntitiesListModel = new QSqlQueryModel;
	QSqlQuery* getDescription = new QSqlQuery;
	QString descriptionInfo;
	
	QString formatedDescriptionInfo = "This Role Tasks are: \n";
	QList<QString> formatInfo;

	if((relatedEntitiesListView->model()->index(relatedEntitiesListView->selectionModel()->currentIndex().row(),0).data().toString()) == "Actores"){
		
		//takes information from the database	
		relatedEntitiesListModel->setQuery(QString("SELECT name, lastName FROM Actors WHERE rol_id = '%1'").arg(currentAnalyzedEntityTable->model()->index(index.row(),0).data().toString()));
		releatedEntityInformationListView->setModel(relatedEntitiesListModel); // display data in the list view
	
		getDescription->exec(QString("SELECT tasks FROM Roles WHERE rol_id = %1").arg(currentAnalyzedEntityTable->model()->index(index.row(),0).data().toString()));
		while(getDescription->next())
			descriptionInfo += getDescription->value(0).toString();
	}
	else if((relatedEntitiesListView->model()->index(relatedEntitiesListView->selectionModel()->currentIndex().row(),0).data().toString()) == "Funciones"){
		relatedEntitiesListModel->setQuery(QString("SELECT name AS Function FROM RolesFunctions INNER JOIN Functions ON Functions.function_id = RolesFunctions.function_id WHERE RolesFunctions.rol_id = %1 GROUP BY name").arg(currentAnalyzedEntityTable->model()->index(index.row(),0).data().toString()));
		releatedEntityInformationListView->setModel(relatedEntitiesListModel); // display data in the list view
	
		getDescription->exec(QString("SELECT tasks FROM Roles WHERE rol_id = %1").arg(currentAnalyzedEntityTable->model()->index(index.row(),0).data().toString()));
		while(getDescription->next())
			descriptionInfo += getDescription->value(0).toString();
	}
	else if((relatedEntitiesListView->model()->index(relatedEntitiesListView->selectionModel()->currentIndex().row(),0).data().toString()) == "Procesos"){
		relatedEntitiesListModel->setQuery(QString("SELECT name AS Process FROM RolesProcesses INNER JOIN Processes ON Processes.process_id = RolesProcesses.process_id WHERE RolesProcesses.rol_id = %1 GROUP BY name").arg(currentAnalyzedEntityTable->model()->index(index.row(),0).data().toString()));
		releatedEntityInformationListView->setModel(relatedEntitiesListModel); // display data in the list view
	
		getDescription->exec(QString("SELECT tasks FROM Roles WHERE rol_id = %1").arg(currentAnalyzedEntityTable->model()->index(index.row(),0).data().toString()));
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

	//connect(back, SIGNAL(clicked()),
	//		this, SLOT(goBack()));
}

void RolesNavigation::showRolesEntitiesElementInfo(const QModelIndex& index)
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
	else if (selectedRelatedEntity == "Procesos"){
		getDescription.exec(QString("SELECT description FROM Processes WHERE name = '%1'").arg(elementName));
		getDescription.lastError();
		while(getDescription.next())
			description = getDescription.value(0).toString();
	}
	
	elementDescriptionTextEdit->setPlainText(description);								   
}

void RolesNavigation::rolesSearch(const QString& text)
{
    /* search roles using the user input in the LineEdit*/
	
	QSqlQueryModel* searchRoles = new QSqlQueryModel;
    /*******************************************Roles Scren***********************************************************************/
	if (text != "")
		searchRoles->setQuery(QString("SELECT rol_id, name FROM Roles WHERE name LIKE '%1%'").arg(text));
	else
	    searchRoles->setQuery("SELECT rol_id, name FROM Roles");

    // Display the Query results
    currentAnalyzedEntityTable->setModel(searchRoles);

}
