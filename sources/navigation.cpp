#include "../headers/navigation.h"
#include "../headers/roles_navigation.h"
#include "../headers/ou_navigation.h"
#include "../headers/data_entity_navigation.h"
#include "../headers/physical_tech_component_navigation.h"
#include "../headers/mainwindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLayoutItem>

Navigation::Navigation(QWidget* parent) : QWidget(parent)
{
	
	mainlayout = new QVBoxLayout();
	
    QPushButton* roles = new QPushButton("Roles");
	roles->setFlat(true);
	QPushButton* OU = new QPushButton("Unidades Organizacionales");
	OU->setFlat(true);
	QPushButton* dataEntity = new QPushButton("Entidad de Datos");
	dataEntity->setFlat(true);
    QPushButton* physicalTechComponents = new QPushButton("Componentes Fisicos Tecnologicos");
    physicalTechComponents->setFlat(true);

	mainlayout->addWidget(roles);
	mainlayout->addWidget(OU);
	mainlayout->addWidget(dataEntity);
    mainlayout->addWidget(physicalTechComponents);

	setLayout(mainlayout);

	connect(roles, SIGNAL(clicked()),
			this, SLOT(showRolesInfo()));
	connect(OU, SIGNAL(clicked()),
			this, SLOT(showOUInfo()));
	connect(dataEntity, SIGNAL(clicked()),
			this, SLOT(showDataEntityInfo()));
    connect(physicalTechComponents,SIGNAL(clicked()),
            this, SLOT(showPhysicalTechComponentInfo()));
}

void Navigation::deleteScreenWidgets()
{
    QLayoutItem* item; 
	QWidget* widget;
		/*this deletes the all the widgets that were at the screen before placing the widgets definded here*/
	while ((item = mainlayout->takeAt(0))){
		if ((widget = item->widget()) !=0 ){widget->hide(); delete widget;}
		else {delete item;}
	}

	delete mainlayout;
}


void Navigation::showRolesInfo()
{
	deleteScreenWidgets();
    
    // sets RolesNavigation widget as the central widget of the MainWindow
    MainWindow::instance()->setCentralWidget(new RolesNavigation(MainWindow::instance()));
}

void Navigation::showOUInfo()
{
	deleteScreenWidgets();
    // set OuNavigation as the central widget in the MainWindow
    MainWindow::instance()->setCentralWidget(new OuNavigation(MainWindow::instance()));
}


void Navigation::showDataEntityInfo()
{
	deleteScreenWidgets();
    
    // sets DataEntityNavigation widget as the central of the mainwindow
    MainWindow::instance()->setCentralWidget(new DataEntityNavigation(MainWindow::instance()));
													   
}
void Navigation::showPhysicalTechComponentInfo()
{
    deleteScreenWidgets();

    MainWindow::instance()->setCentralWidget(new PhysicalTechComponentNavigation(MainWindow::instance()));
}
