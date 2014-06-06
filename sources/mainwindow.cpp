#include "../headers/mainwindow.h"
#include "../headers/artifacts.h"
#include "../headers/navigation.h"
#include "../headers/data_handler.h"
#include <QDockWidget>
#include <QListView>
#include <QStandardItemModel>

MainWindow::MainWindow()
{
	DataHandler::connect();   //open database conection

	setWindowTitle("ICTUM");  
	resize(1024,720);           // sets windows size

	Artifacts* artifacts = new Artifacts(this);
 
	// creates a model to puts elements in the list
	QStandardItemModel* listModel = new QStandardItemModel;
	listModel->setItem(0,0,new QStandardItem("Artefactos"));
	listModel->setItem(1,0,new QStandardItem("Navegacion"));	
	//creates the dock bar
	QDockWidget* dockBar = new QDockWidget;
	dockBar->setObjectName("options");
	addDockWidget(Qt::LeftDockWidgetArea, dockBar);
	
	//creates a list view that will live inside the dockbar
	options = new QListView;
	//assings the options to the options listview
	options->setModel(listModel);
	//puts the list view inside the toolbar
	dockBar->setWidget(options);
	
	this->setCentralWidget(artifacts);

	connect(options, SIGNAL(clicked(const QModelIndex&)),
			this, SLOT(changeCentralWidget(const QModelIndex&)));
}

void MainWindow::changeCentralWidget(const QModelIndex& index)
{
	if(options->model()->index(index.row(),0).data().toString() == "Navegacion")
		this->setCentralWidget(new Navigation(this));
	else
		this->setCentralWidget(new Artifacts(this));
}


