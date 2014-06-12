#include "../headers/navigation.h"
#include "../headers/roles_navigation.h"
#include "../headers/ou_navigation.h"
#include "../headers/data_entity_navigation.h"
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
	QPushButton* OU = new QPushButton("Unidades Organizacionales");
	OU->setFlat(true);
	QPushButton* dataEntity = new QPushButton("Entidad de Datos");
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
		/*this deletes the all the widgets that were at the screen before placing the widgets definded here*/
	while ((item = mainlayout->takeAt(0))){
		if ((widget = item->widget()) !=0 ){widget->hide(); delete widget;}
		else {delete item;}
	}

	delete startScreen;    //deletes previos widgets on the screen
	delete mainlayout;

    // sets RolesNavigation widget as the central widget of the MainWindow
    MainWindow::instance()->setCentralWidget(new RolesNavigation(MainWindow::instance()));
}

void Navigation::showOUInfo()
{
	QLayoutItem* item; 
	QWidget* widget;


	/*this deletes the all the widgets that were at the screen before placing the widgets definded here*/
	while ((item = mainlayout->takeAt(0))){
		if ((widget = item->widget()) !=0 ){widget->hide(); delete widget;}
		else {delete item;}
	}

	delete startScreen;    //deletes previos widgets on the screen
	delete mainlayout;

    // set OuNavigation as the central widget in the MainWindow
    MainWindow::instance()->setCentralWidget(new OuNavigation(MainWindow::instance()));
}



/*******************************************************************Data Entity***************************************************/
//---------------------------------------------------------------------------------------------------------------------------------
void Navigation::showDataEntityInfo()
{
	
	QLayoutItem* item; 
	QWidget* widget;

		/*this deletes the all the widgets that were at the screen before placing the widgets definded here*/
	while ((item = mainlayout->takeAt(0))){
		if ((widget = item->widget()) !=0 ){widget->hide(); delete widget;}
		else {delete item;}
	}

	delete startScreen;    //deletes previos widgets on the screen
	delete mainlayout;

    // sets DataEntityNavigation widget as the central of the mainwindow
    MainWindow::instance()->setCentralWidget(new DataEntityNavigation(MainWindow::instance()));
	/***********************************************************************************************************/

													   
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
	/**************************************************************Data Entity ************************************************/
		currentAnalyzedEntityTable->setModel(searchRoles);
}


void Navigation::goBack()
{
	if(navigationController.pop() == "startScreen"){
		qDebug()<<"tamo en start";
		Navigation();
	}
	
}
