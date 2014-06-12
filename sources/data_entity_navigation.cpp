#include "../headers/roles_navigation.h"
#include "data_entity_navigation.h"
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

DataEntityNavigation::DataEntityNavigation(QWidget* parent) : QWidget(parent)
{
    QGridLayout* dataViewLayout = new QGridLayout();
	QSqlQueryModel* currentAnalyzedEntityTableModel = new QSqlQueryModel;
	QStandardItemModel* relatedEntitiesModel = new QStandardItemModel;

	relatedEntitiesModel->setItem(0,0,new QStandardItem("Sis. de Servcios de Informacion"));
		
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
		
	currentAnalyzedEntityTableModel->setQuery("SELECT information_service_id AS ID, name FROM DataEntity"); // takes information from the database
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
			this, SLOT(dataEntities(const QModelIndex&)));
	connect(searchEdit, SIGNAL(textChanged(const QString&)),
			this, SLOT(dataEntitySearch(const QString&))); 
	connect(releatedEntityInformationListView, SIGNAL(clicked(const QModelIndex&)),
			this, SLOT(showDataEntitiesElementInfo(const QModelIndex&)));
		
}

void DataEntityNavigation::dataEntities(const QModelIndex& index)
{
	//isFirstTime = false;
	
	QSqlQueryModel* relatedEntitiesListModel = new QSqlQueryModel;
	QSqlQuery* getDescription = new QSqlQuery;
	QString descriptionInfo;
	
	QString formatedDescriptionInfo;
	QList<QString> formatInfo;

	//takes information from the database	
	relatedEntitiesListModel->setQuery(QString("SELECT InformationSystemServices.name FROM InformationSystemServices JOIN DataEntity ON DataEntity.information_service_id = InformationSystemServices.information_service_id WHERE DataEntity.information_service_id = '%1' GROUP BY InformationSystemServices.name").arg(currentAnalyzedEntityTable->model()->index(index.row(),0).data().toString()));
	releatedEntityInformationListView->setModel(relatedEntitiesListModel); // display data in the list view
	
	getDescription->exec(QString("SELECT description FROM DataEntity WHERE name = '%1'").arg(currentAnalyzedEntityTable->model()->index(index.row(),1).data().toString()));
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

void DataEntityNavigation::showDataEntitiesElementInfo(const QModelIndex& index)
{
	QSqlQuery getDescription;
    QString elementName = releatedEntityInformationListView->model()->index(index.row(),0).data().toString();
	QString selectedRelatedEntity = relatedEntitiesListView->model()->index(relatedEntitiesListView->selectionModel()->currentIndex().row(),0).data().toString();
	QString description;

	if (selectedRelatedEntity == "Sis. de Servcios de Informacion"){
		getDescription.exec(QString("SELECT description FROM InformationSystemServices WHERE name = '%1'").arg(elementName));
		getDescription.lastError();
		while(getDescription.next())
			description = getDescription.value(0).toString();
	}
	elementDescriptionTextEdit->setPlainText(description);								   
}

void DataEntityNavigation::dataEntitySearch(const QString& text)
{
    /* search roles using the user input in the LineEdit*/
	
	QSqlQueryModel* searchRoles = new QSqlQueryModel;
	
	if (text != "")
	    searchRoles->setQuery(QString("SELECT information_service_id AS ID, name FROM DataEntity WHERE name LIKE '%1%'").arg(text));
	else
	    searchRoles->setQuery("SELECT information_service_id AS ID, name FROM DataEntity");

       // Display the Query results
    currentAnalyzedEntityTable->setModel(searchRoles);

}
