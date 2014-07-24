#include "../headers/process.h"
#include "../headers/process_add_edit_dialog.h"
#include <QTableView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDebug>
#include <QtSql>
#include <QHeaderView>

Process::Process(QWidget* parent) : QDialog(parent)
{
	//QWidget* actorWidget = new QWidget;

	QHBoxLayout* mainlayout = new QHBoxLayout();
	QVBoxLayout* buttonsLayout = new QVBoxLayout;

	QPushButton* addProcess = new QPushButton("Agregar Proceso");
	QPushButton* editProcess = new QPushButton("Editar Proceso");
	QPushButton* deleteProcess = new QPushButton("Eliminar Proceso");

	table = new QTableView;
    table->verticalHeader()->setVisible(false);

	refreshProcessTable();

	buttonsLayout->addWidget(addProcess);
	buttonsLayout->addWidget(editProcess);
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(deleteProcess);

	mainlayout->addWidget(table);
	mainlayout->addLayout(buttonsLayout);
	this->setLayout(mainlayout);

	connect(addProcess, SIGNAL(clicked()),
			this, SLOT(addProcess()));
	connect(editProcess, SIGNAL(clicked()),
			this, SLOT(editProcess()));
}

void Process::refreshProcessTable()
{
	//sets query model to show data in the table view
	QSqlQueryModel* processCatalogQueryModel = new QSqlQueryModel();
	processCatalogQueryModel->setQuery("SELECT process_id as ID, name as Nombre, objective as Objetivo, description as Descripción FROM Processes");  //query the database
	
	table->setSelectionBehavior(QAbstractItemView::SelectRows); // select entire rows
	table->setSelectionMode(QAbstractItemView::SingleSelection); //select one item at time
	table->setModel(processCatalogQueryModel); // sets ouCatalogQueryModel as the table model
	
}

void Process::addProcess()
{
	ProcessAddEditDialog* dlg = new ProcessAddEditDialog(this);
	QSqlQuery qry;         //QSqlQuery object that will save the data in to the database

	//if ok is pressed in dlg (actor add edit dialog)
	if(dlg->exec() == QDialog::Accepted)
	{
		/*inserts data to database*/
		//prepare the sql statment
		qry.prepare("INSERT INTO Processes (name, objective, description) VALUES (:name, :objective, :description)");
		
		//gives each field it value
		qry.bindValue(":name", dlg->name());
		qry.bindValue(":objective", dlg->objective());
		qry.bindValue(":description", dlg->description());
		
		//if something went wrong with the querry print what was it
		if (!qry.exec()){
			qDebug()<<qry.lastError();
		}
		refreshProcessTable();    //updata table data
	}
}

void Process::editProcess()
{
	int rowIndex = table->selectionModel()->currentIndex().row();    //takes the index of the clicked row
 	ProcessAddEditDialog* dlg = new ProcessAddEditDialog(this);          
	QString currentName, currentObjective, currentDescription;
	QSqlQuery qry;         //this is the object that will hold the update query
	
	
	/*sets the text into the dialog controls*/
	dlg->setName(table->model()->index(rowIndex,1).data().toString());
	dlg->setObjective(table->model()->index(rowIndex,2).data().toString());
	dlg->setDescription(table->model()->index(rowIndex,3).data().toString()); 
	
	currentName = dlg->name();
	currentObjective = dlg->objective();
	currentDescription = dlg->description();	
		
	
	if(dlg->exec()==QDialog::Accepted){
			
		/*edit the database row*/
		//prepare the sql statment
		QString id = table->model()->index(rowIndex,0).data().toString();
		qry.prepare(QString("UPDATE Processes SET name = :name, objective = :objective, description = :description where process_id = %1").arg(id));
		
		//does nothing if the data is not changed
		if((dlg->name()==currentName) 
		   && (dlg->objective()==currentObjective) 
		   && (dlg->description()==currentDescription))
		   return;
		
		//gives each field it value	
		qry.bindValue(":name", dlg->name());
		qry.bindValue(":objective", dlg->objective());
		qry.bindValue(":description", dlg->description());
				
		//ifsomething went wrong with the querry print what was it
		if (!qry.exec()){
			qDebug()<<qry.lastError();
		}
		refreshProcessTable();			//update table data
	}
}
