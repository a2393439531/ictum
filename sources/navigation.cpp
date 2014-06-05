#include "../headers/navigation.h"
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

Navigation::Navigation(QWidget* parent) : QWidget(parent)
{
	
	/*if (!isFirstTime){
		QLayoutItem* item; 
		QWidget* widget;
		qDebug()<<"aqui afuera";
		this deletes the all the widgets that were at the screen before placing the widgets definded here
		while ((item = dataViewLayout->takeAt(0))){
			qDebug()<<"entreaqui";
			if ((widget = item->widget()) !=0 ){widget->hide(); delete widget;}
			else {delete item;}
		}
	}*/
	startScreen = new QWidget;
	mainlayout = new QVBoxLayout(startScreen);

	QPushButton* roles = new QPushButton("Roles");
	roles->setFlat(true);
	QPushButton* OU = new QPushButton("Organizational Units");
	OU->setFlat(true);
	QPushButton* dataEntity = new QPushButton("Data Enities");
	dataEntity->setFlat(true);
	//QPushButton* technologyComponets = new("Componentes Fisicos Tecnologicos");
	
	mainlayout->addWidget(roles);
	mainlayout->addWidget(OU);
	mainlayout->addWidget(dataEntity);
	//mainlayout->addWidget(technologyComponets);

	setLayout(mainlayout);

	connect(roles, SIGNAL(clicked()),
			this, SLOT(showRolesInfo()));
	connect(OU, SIGNAL(clicked()),
			this, SLOT(showOUInfo()));
	connect(dataEntity, SIGNAL(clicked()),
			this, SLOT(showDataEntityInfo()));
}


void Navigation::showRolesInfo()
{
	
	QLayoutItem* item; 
	QWidget* widget;
	currentScreen = "rolesScreen";
	navigationController.push("startScreen");  // save the acces order to the deferent screens

	screen = new QWidget;
	QGridLayout* dataViewLayout = new QGridLayout(screen);
	QSqlQueryModel* currentAnalyzedEntityTableModel = new QSqlQueryModel;
	QStandardItemModel* relatedEntitiesModel = new QStandardItemModel;

	relatedEntitiesModel->setItem(0,0,new QStandardItem("Actors"));
	relatedEntitiesModel->setItem(1,0,new QStandardItem("Functions"));
	relatedEntitiesModel->setItem(2,0,new QStandardItem("Processes"));

	
	/* initiealizes the widgets*/
	currentAnalyzedEntityTable = new QTableView;
	releatedEntityInformationListView = new QListView;
	descriptionTextEdit = new QTextEdit;
	searchEdit = new QLineEdit;
	relatedEntitiesListView = new QListView;
	back = new QPushButton("<-Atras");
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
	dataViewLayout->addWidget(new QLabel("Related Entities"),2,1);
	dataViewLayout->addWidget(relatedEntitiesListView,3,1);
	dataViewLayout->addWidget(releatedEntityInformationListView,3,2);
	dataViewLayout->addWidget(new QLabel("Description"),4,0);
	dataViewLayout->addWidget(descriptionTextEdit,5,0,1,2);
	dataViewLayout->addWidget(new QLabel("Element Description"),4,2);
	dataViewLayout->addWidget(elementDescriptionTextEdit,5,2,1,2);

	/*this deletes the all the widgets that were at the screen before placing the widgets definded here*/
	while ((item = mainlayout->takeAt(0))){
		if ((widget = item->widget()) !=0 ){widget->hide(); delete widget;}
		else {delete item;}
	}

	delete startScreen;    //deletes previos widgets on the screen
	delete mainlayout;
	/***********************************************************************************************************/

	this->setLayout(dataViewLayout);    //show widgets

	connect(currentAnalyzedEntityTable, SIGNAL(clicked(const QModelIndex&)),
			this, SLOT(rolesEntities(const QModelIndex&)));
	connect(searchEdit, SIGNAL(textChanged(const QString&)),
			this, SLOT(entitySearch(const QString&)));
	connect(releatedEntityInformationListView, SIGNAL(clicked(const QModelIndex&)),
			this, SLOT(showRolesEntitiesElementInfo(const QModelIndex&)));
}

/*************************************************************************************Roles**********************************************************************************************/
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Navigation::rolesEntities(const QModelIndex& index)
{
	//isFirstTime = false;
	currentScreen = "rolesScreen";
	QSqlQueryModel* relatedEntitiesListModel = new QSqlQueryModel;
	QSqlQuery* getDescription = new QSqlQuery;
	QString descriptionInfo;
	
	QString formatedDescriptionInfo = "This Role Tasks are: \n";
	QList<QString> formatInfo;

	if((relatedEntitiesListView->model()->index(relatedEntitiesListView->selectionModel()->currentIndex().row(),0).data().toString()) == "Actors"){
		
		//takes information from the database	
		relatedEntitiesListModel->setQuery(QString("SELECT name, lastName FROM Actors WHERE rol_id = '%1'").arg(currentAnalyzedEntityTable->model()->index(index.row(),0).data().toString()));
		releatedEntityInformationListView->setModel(relatedEntitiesListModel); // display data in the list view
	
		getDescription->exec(QString("SELECT tasks FROM Roles WHERE rol_id = %1").arg(currentAnalyzedEntityTable->model()->index(index.row(),0).data().toString()));
		while(getDescription->next())
			descriptionInfo += getDescription->value(0).toString();
	}
	else if((relatedEntitiesListView->model()->index(relatedEntitiesListView->selectionModel()->currentIndex().row(),0).data().toString()) == "Functions"){
		relatedEntitiesListModel->setQuery(QString("SELECT name AS Function FROM RolesFunctions INNER JOIN Functions ON Functions.function_id = RolesFunctions.function_id WHERE RolesFunctions.rol_id = %1 GROUP BY name").arg(currentAnalyzedEntityTable->model()->index(index.row(),0).data().toString()));
		releatedEntityInformationListView->setModel(relatedEntitiesListModel); // display data in the list view
	
		getDescription->exec(QString("SELECT tasks FROM Roles WHERE rol_id = %1").arg(currentAnalyzedEntityTable->model()->index(index.row(),0).data().toString()));
		while(getDescription->next())
			descriptionInfo += getDescription->value(0).toString();
	}
	else if((relatedEntitiesListView->model()->index(relatedEntitiesListView->selectionModel()->currentIndex().row(),0).data().toString()) == "Processes"){
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

	connect(back, SIGNAL(clicked()),
			this, SLOT(goBack()));
}

void Navigation::showRolesEntitiesElementInfo(const QModelIndex& index)
{
	QSqlQuery getDescription;
    QString elementName = releatedEntityInformationListView->model()->index(index.row(),0).data().toString();
	QString selectedRelatedEntity = relatedEntitiesListView->model()->index(relatedEntitiesListView->selectionModel()->currentIndex().row(),0).data().toString();
	QString description;

	if (selectedRelatedEntity == "Functions"){
		getDescription.exec(QString("SELECT description FROM Functions WHERE name = '%1'").arg(elementName));
		getDescription.lastError();
		while(getDescription.next())
			description = getDescription.value(0).toString();
	}
	else if (selectedRelatedEntity == "Processes"){
		getDescription.exec(QString("SELECT description FROM Processes WHERE name = '%1'").arg(elementName));
		getDescription.lastError();
		while(getDescription.next())
			description = getDescription.value(0).toString();
	}

	
	
	elementDescriptionTextEdit->setPlainText(description);								   
}

/*************************************************************Organizational Units************************************************************/
//--------------------------------------------------------------------------------------------------------------------------------------------
void Navigation::showOUInfo()
{
	
	QLayoutItem* item; 
	QWidget* widget;
	currentScreen = "OUScreen";

	navigationController.push("startScreen");  // save the acces order to the deferent screens

	screen = new QWidget;
	QGridLayout* dataViewLayout = new QGridLayout(screen);
	QSqlQueryModel* currentAnalyzedEntityTableModel = new QSqlQueryModel;
	QStandardItemModel* relatedEntitiesModel = new QStandardItemModel;

	relatedEntitiesModel->setItem(0,0,new QStandardItem("Actors"));
	relatedEntitiesModel->setItem(1,0,new QStandardItem("Functions"));
		
	/* initiealizes the widgets*/
	currentAnalyzedEntityTable = new QTableView;
	releatedEntityInformationListView = new QListView;
	descriptionTextEdit = new QTextEdit;
	searchEdit = new QLineEdit;
	relatedEntitiesListView = new QListView;
	elementDescriptionTextEdit = new QTextEdit;
	back = new QPushButton("<-Atras");

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
	dataViewLayout->addWidget(new QLabel("Related Entities"),2,1);
	dataViewLayout->addWidget(relatedEntitiesListView,3,1);
	dataViewLayout->addWidget(releatedEntityInformationListView,3,2);
	dataViewLayout->addWidget(new QLabel("Description"),4,0);
	dataViewLayout->addWidget(descriptionTextEdit,5,0,1,2);
	dataViewLayout->addWidget(new QLabel("Element Description"),4,2);
	dataViewLayout->addWidget(elementDescriptionTextEdit,5,2,1,2);
	
	/*this deletes the all the widgets that were at the screen before placing the widgets definded here*/
	while ((item = mainlayout->takeAt(0))){
		if ((widget = item->widget()) !=0 ){widget->hide(); delete widget;}
		else {delete item;}
	}

	delete startScreen;    //deletes previos widgets on the screen
	delete mainlayout;
	/***********************************************************************************************************/

	this->setLayout(dataViewLayout);    //show widgets

	connect(currentAnalyzedEntityTable, SIGNAL(clicked(const QModelIndex&)),
			this, SLOT(oUEntities(const QModelIndex&)));
	connect(searchEdit, SIGNAL(textChanged(const QString&)),
			this, SLOT(entitySearch(const QString&))); 
	connect(releatedEntityInformationListView, SIGNAL(clicked(const QModelIndex&)),
			this, SLOT(showOUEntitiesElementInfo(const QModelIndex&)));
														   
}

void Navigation::oUEntities(const QModelIndex& index)
{
	//isFirstTime = false;
	
	QSqlQueryModel* relatedEntitiesListModel = new QSqlQueryModel;
	QSqlQuery* getDescription = new QSqlQuery;
	QString descriptionInfo;
	
	QString formatedDescriptionInfo = "This Role Tasks are: \n";
	QList<QString> formatInfo;

	if((relatedEntitiesListView->model()->index(relatedEntitiesListView->selectionModel()->currentIndex().row(),0).data().toString()) == "Actors"){
		
		//takes information from the database	
		relatedEntitiesListModel->setQuery(QString("SELECT name FROM Actors WHERE ou_id = '%1'").arg(currentAnalyzedEntityTable->model()->index(index.row(),0).data().toString()));
		releatedEntityInformationListView->setModel(relatedEntitiesListModel); // display data in the list view
	
		getDescription->exec(QString("SELECT tasks FROM OrganizationalUnits WHERE ou_id = %1").arg(currentAnalyzedEntityTable->model()->index(index.row(),0).data().toString()));
		while(getDescription->next())
			descriptionInfo += getDescription->value(0).toString();
	}
	else if((relatedEntitiesListView->model()->index(relatedEntitiesListView->selectionModel()->currentIndex().row(),0).data().toString()) == "Functions"){
		
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

	connect(back, SIGNAL(clicked()),
			this, SLOT(goBack()));
}

void Navigation::showOUEntitiesElementInfo(const QModelIndex& index)
{
	QSqlQuery getDescription;
    QString elementName = releatedEntityInformationListView->model()->index(index.row(),0).data().toString();
	QString selectedRelatedEntity = relatedEntitiesListView->model()->index(relatedEntitiesListView->selectionModel()->currentIndex().row(),0).data().toString();
	QString description;

	if (selectedRelatedEntity == "Functions"){
		getDescription.exec(QString("SELECT description FROM Functions WHERE name = '%1'").arg(elementName));
		getDescription.lastError();
		while(getDescription.next())
			description = getDescription.value(0).toString();
	}
	elementDescriptionTextEdit->setPlainText(description);								   
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------


/*******************************************************************Data Entity***************************************************/
//---------------------------------------------------------------------------------------------------------------------------------
void Navigation::showDataEntityInfo()
{
	
	QLayoutItem* item; 
	QWidget* widget;
	currentScreen = "dataEntity";

	navigationController.push("startScreen");  // save the acces order to the deferent screens

	screen = new QWidget;
	QGridLayout* dataViewLayout = new QGridLayout(screen);
	QSqlQueryModel* currentAnalyzedEntityTableModel = new QSqlQueryModel;
	QStandardItemModel* relatedEntitiesModel = new QStandardItemModel;

	relatedEntitiesModel->setItem(0,0,new QStandardItem("Information System Services"));
		
	/*initiealizes the widgets*/
	currentAnalyzedEntityTable = new QTableView;
	releatedEntityInformationListView = new QListView;
	descriptionTextEdit = new QTextEdit;
	searchEdit = new QLineEdit;
	relatedEntitiesListView = new QListView;
	elementDescriptionTextEdit = new QTextEdit;
	back = new QPushButton("<-Atras");

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
	dataViewLayout->addWidget(new QLabel("Related Entities"),2,1);
	dataViewLayout->addWidget(relatedEntitiesListView,3,1);
	dataViewLayout->addWidget(releatedEntityInformationListView,3,2);
	dataViewLayout->addWidget(new QLabel("Description"),4,0);
	dataViewLayout->addWidget(descriptionTextEdit,5,0,1,2);
	dataViewLayout->addWidget(new QLabel("Element Description"),4,2);
	dataViewLayout->addWidget(elementDescriptionTextEdit,5,2,1,2);
	
	/*this deletes the all the widgets that were at the screen before placing the widgets definded here*/
	while ((item = mainlayout->takeAt(0))){
		if ((widget = item->widget()) !=0 ){widget->hide(); delete widget;}
		else {delete item;}
	}

	delete startScreen;    //deletes previos widgets on the screen
	delete mainlayout;
	/***********************************************************************************************************/

	this->setLayout(dataViewLayout);    //show widgets

	connect(currentAnalyzedEntityTable, SIGNAL(clicked(const QModelIndex&)),
			this, SLOT(dataEntities(const QModelIndex&)));
	connect(searchEdit, SIGNAL(textChanged(const QString&)),
			this, SLOT(entitySearch(const QString&))); 
	connect(releatedEntityInformationListView, SIGNAL(clicked(const QModelIndex&)),
			this, SLOT(showDataEntitiesElementInfo(const QModelIndex&)));
														   
}

void Navigation::dataEntities(const QModelIndex& index)
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
	
	connect(back, SIGNAL(clicked()),
			this, SLOT(goBack()));
}

void Navigation::showDataEntitiesElementInfo(const QModelIndex& index)
{
	QSqlQuery getDescription;
    QString elementName = releatedEntityInformationListView->model()->index(index.row(),0).data().toString();
	QString selectedRelatedEntity = relatedEntitiesListView->model()->index(relatedEntitiesListView->selectionModel()->currentIndex().row(),0).data().toString();
	QString description;

	if (selectedRelatedEntity == "Information System Services"){
		getDescription.exec(QString("SELECT description FROM InformationSystemServices WHERE name = '%1'").arg(elementName));
		getDescription.lastError();
		while(getDescription.next())
			description = getDescription.value(0).toString();
	}
	elementDescriptionTextEdit->setPlainText(description);								   
}
void Navigation::entitySearch(const QString& text)
{
	/* search roles using the user input in the LineEdit*/
	
	QSqlQueryModel* searchRoles = new QSqlQueryModel;
    /*******************************************Roles Scren***********************************************************************/
	if (currentScreen == "rolesScreen"){
		if (text != "")
			searchRoles->setQuery(QString("SELECT rol_id, name FROM Roles WHERE name LIKE '%1%'").arg(text));
		else
			searchRoles->setQuery("SELECT rol_id, name FROM Roles");
	}
	/********************************************OranizationalUnits Screen*********************************************************/
	else if (currentScreen == "OUScreen"){ 
		if (text != "")
			searchRoles->setQuery(QString("SELECT ou_id, name FROM OrganizationalUnits WHERE name LIKE '%1%'").arg(text));
		else
			searchRoles->setQuery("SELECT ou_id, name FROM OrganizationalUnits");
	}
	/**************************************************************Data Entity ************************************************/
	if (currentScreen == "dataEntity"){
		if (text != "")
			searchRoles->setQuery(QString("SELECT information_service_id AS ID, name FROM DataEntity WHERE name LIKE '%1%'").arg(text));
		else
			searchRoles->setQuery("SELECT information_service_id AS ID, name FROM DataEntity");
	}
	qDebug()<<"klk ta pasando";
	currentAnalyzedEntityTable->setModel(searchRoles);
}


void Navigation::goBack()
{
	if(navigationController.pop() == "startScreen"){
		qDebug()<<"tamo en start";
		Navigation();
	}
	
}
