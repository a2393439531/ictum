#include "../headers/physical_tech_component_navigation.h"
//#include "data_entity_navigation.h"
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

PhysicalTechComponentNavigation::PhysicalTechComponentNavigation(QWidget* parent) : QWidget(parent)
{
    QGridLayout* dataViewLayout = new QGridLayout();
	QSqlQueryModel* currentAnalyzedEntityTableModel = new QSqlQueryModel;
	QStandardItemModel* relatedEntitiesModel = new QStandardItemModel;

	relatedEntitiesModel->setItem(0,0,new QStandardItem("Actores"));
	relatedEntitiesModel->setItem(1,0,new QStandardItem("Roles"));
	//relatedEntitiesModel->setItem(2,0,new QStandardItem("Sis. de Servcios de Informacion"));
	
    /*initiealizes the widgets*/
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
		
	currentAnalyzedEntityTableModel->setQuery("SELECT physical_technology_component_id AS ID, name FROM PhysicalTechnologiesComponents"); // takes information from the database
	currentAnalyzedEntityTable->setModel(currentAnalyzedEntityTableModel);  //display data in the table view
	
	//places items in the screen
	dataViewLayout->addWidget(back,1,0,1,1);
	dataViewLayout->addWidget(searchEdit,2,0);
	dataViewLayout->addWidget(currentAnalyzedEntityTable,3,0);
	dataViewLayout->addWidget(new QLabel("Entidades Realcionadas"),2,1);
	dataViewLayout->addWidget(relatedEntitiesListView,3,1);
	dataViewLayout->addWidget(releatedEntityInformationListView,3,2);
	dataViewLayout->addWidget(new QLabel("Descripcion"),4,0);
	dataViewLayout->addWidget(descriptionTextEdit,5,0,1,2);
	dataViewLayout->addWidget(new QLabel("Descripcion del Elemento"),4,2);
	dataViewLayout->addWidget(elementDescriptionTextEdit,5,2,1,2);
	
    this->setLayout(dataViewLayout);    //show widgets

	connect(currentAnalyzedEntityTable, SIGNAL(clicked(const QModelIndex&)),
			this, SLOT(physicalTechComponents(const QModelIndex&)));
	connect(searchEdit, SIGNAL(textChanged(const QString&)),
			this, SLOT(physicalTechComponentSearch(const QString&))); 
	connect(releatedEntityInformationListView, SIGNAL(clicked(const QModelIndex&)),
			this, SLOT(showPhysicalTechComponentsElementInfo(const QModelIndex&)));
		
}

void PhysicalTechComponentNavigation::physicalTechComponents(const QModelIndex& index)
{
	//isFirstTime = false;
	
	QSqlQueryModel* relatedEntitiesListModel = new QSqlQueryModel;
	QSqlQuery* getDescription = new QSqlQuery;
	QString descriptionInfo;
	
	QString formatedDescriptionInfo;
	QList<QString> formatInfo;

	if((relatedEntitiesListView->model()->index(relatedEntitiesListView->selectionModel()->currentIndex().row(),0).data().toString()) == "Roles"){
    
        //takes information from the database	
	    relatedEntitiesListModel->setQuery(QString("SELECT Roles.name FROM Roles JOIN PhysicalComponentsRoles ON Roles.rol_id = PhysicalComponentsRoles.rol_id WHERE PhysicalComponentsRoles.physical_technology_component_id = %1").arg(currentAnalyzedEntityTable->model()->index(index.row(),0).data().toString()));
    
        releatedEntityInformationListView->setModel(relatedEntitiesListModel); // display data in the list view
    }

    else if((relatedEntitiesListView->model()->index(relatedEntitiesListView->selectionModel()->currentIndex().row(),0).data().toString()) == "Actores"){
	    relatedEntitiesListModel->setQuery(QString("SELECT Actors.name FROM Actors JOIN PhysicalComponentsRoles ON Actors.rol_id = PhysicalComponentsRoles.rol_id WHERE PhysicalComponentsRoles.physical_technology_component_id = %1").arg(currentAnalyzedEntityTable->model()->index(index.row(),0).data().toString()));
		
        releatedEntityInformationListView->setModel(relatedEntitiesListModel); // display data in the list view
	
		}
/*	else if((relatedEntitiesListView->model()->index(relatedEntitiesListView->selectionModel()->currentIndex().row(),0).data().toString()) == "Roles"){
		relatedEntitiesListModel->setQuery(QString("SELECT name FROM Roles JOIN RolesDataEntity ON Roles.rol_id = RolesDataEntity.rol_id WHERE RolesDataEntity.data_entity_id = %1 GROUP BY name").arg(currentAnalyzedEntityTable->model()->index(index.row(),0).data().toString()));
		releatedEntityInformationListView->setModel(relatedEntitiesListModel); // display data in the list view
	
		}*/

	
	getDescription->exec(QString("SELECT objective FROM PhysicalTechnologiesComponents WHERE name = '%1'").arg(currentAnalyzedEntityTable->model()->index(index.row(),1).data().toString()));
	while(getDescription->next())
		descriptionInfo += getDescription->value(0).toString();
    
    qDebug()<<getDescription->lastError();
	relatedEntitiesListModel->lastError();
	//formatInfo = descriptionInfo.split(",", QString::SkipEmptyParts);  //break the string tha comes out form the database in parts
	
	/*// gives format to the string that is comming from the database
	  foreach(QString e, formatInfo){
	  //e+= "\n";
	  formatedDescriptionInfo += e +"\n" ;
	  }*/
	descriptionTextEdit->setPlainText(descriptionInfo);
	
}

void PhysicalTechComponentNavigation::showPhysicalTechComponentsElementInfo(const QModelIndex& index)
{
	QSqlQuery getDescription;
    QString elementName = releatedEntityInformationListView->model()->index(index.row(),0).data().toString();
	QString selectedRelatedEntity = relatedEntitiesListView->model()->index(relatedEntitiesListView->selectionModel()->currentIndex().row(),0).data().toString();
	QString description;

	if (selectedRelatedEntity == "Roles"){
		getDescription.exec(QString("SELECT objective FROM Roles WHERE name = '%1'").arg(elementName));
		while(getDescription.next())
			description = getDescription.value(0).toString();
	}
	elementDescriptionTextEdit->setPlainText(description);								   
}

void PhysicalTechComponentNavigation::physicalTechComponentSearch(const QString& text)
{
    /* search roles using the user input in the LineEdit*/
	
	QSqlQueryModel* searchRoles = new QSqlQueryModel;
	
	if (text != "")
	    searchRoles->setQuery(QString("SELECT physical_technology_component_id AS ID, name FROM PhysicalTechnologiesComponents WHERE name LIKE '%1%'").arg(text));
	else
	    searchRoles->setQuery("SELECT physical_technology_component_id AS ID, name FROM PhysicalTechnologiesComponents");

    // Display the Query results
    currentAnalyzedEntityTable->setModel(searchRoles);

}
