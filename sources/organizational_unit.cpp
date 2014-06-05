#include "../headers/organizational_unit.h"
#include "../headers/ou_add_edit_dialog.h"
#include <QTableView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDebug>
#include <QtSql>


OrganizationalUnit::OrganizationalUnit(QWidget* parent) : QDialog(parent)
{
	//QWidget* actorWidget = new QWidget;

	QHBoxLayout* mainlayout = new QHBoxLayout();
	QVBoxLayout* buttonsLayout = new QVBoxLayout;

	QPushButton* addOrganizationalUnit = new QPushButton("Agregar OU");
	QPushButton* editOrganizationalUnit = new QPushButton("Editar OU");
	QPushButton* deleteOrganizationalUnit = new QPushButton("Eliminar OU");

	table = new QTableView;

	refreshOuTable();

	buttonsLayout->addWidget(addOrganizationalUnit);
	buttonsLayout->addWidget(editOrganizationalUnit);
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(deleteOrganizationalUnit);

	mainlayout->addWidget(table);
	mainlayout->addLayout(buttonsLayout);
	this->setLayout(mainlayout);

	connect(addOrganizationalUnit, SIGNAL(clicked()),
			this, SLOT(addOrganizationalUnit()));
	connect(editOrganizationalUnit, SIGNAL(clicked()),
			this, SLOT(editOrganizationalUnit()));
}

void OrganizationalUnit::refreshOuTable()
{
	//sets query model to show data in the table view
	QSqlQueryModel* ouCatalogQueryModel = new QSqlQueryModel();
	ouCatalogQueryModel->setQuery("SELECT * FROM OrganizationalUnits");  //query the database
	
	table->setSelectionBehavior(QAbstractItemView::SelectRows); // select entire rows
	table->setSelectionMode(QAbstractItemView::SingleSelection); //select one item at time
	table->setModel(ouCatalogQueryModel); // sets ouCatalogQueryModel as the table model
}

void OrganizationalUnit::addOrganizationalUnit()
{
	OuAddEditDialog* dlg = new OuAddEditDialog(this); 
	QSqlQuery qry;         //QSqlQuery object that will save the data in to the database

	//if ok is pressed in dlg (actor add edit dialog)
	if(dlg->exec() == QDialog::Accepted)
	{
		/*inserts data to database*/
		//prepare the sql statment
		qry.prepare("INSERT INTO OrganizationalUnits(name, objective, location, tasks) VALUES (:name, :objective, :location, :tasks)");
		
		//gives each field it value
		qry.bindValue(":name", dlg->name());
		qry.bindValue(":objective", dlg->objective());
		qry.bindValue(":location", dlg->location());
		qry.bindValue(":tasks", dlg->tasks());
		
		//if something went wrong with the querry print what was it
		if (!qry.exec()){
			qDebug()<<qry.lastError();
		}
		refreshOuTable();    //updata table data
	}
}

void OrganizationalUnit::editOrganizationalUnit()
{
	int rowIndex = table->selectionModel()->currentIndex().row();    //takes the index of the clicked row
 	OuAddEditDialog* dlg = new OuAddEditDialog(this);          
	QString currentName, currentObjective, currentTasks, currentLocation;
	QSqlQuery qry;         //this is the object that will hold the update query
	
	/*sets the text into the dialog controls*/
	dlg->setName(table->model()->index(rowIndex,1).data().toString());
	dlg->setObjective(table->model()->index(rowIndex,2).data().toString());
	dlg->setTasks(table->model()->index(rowIndex,4).data().toString()); 
		
	currentName = dlg->name();
	currentObjective = dlg->objective();
	currentTasks = dlg->tasks();	
	currentLocation = dlg->location();
	
	dlg->exec();
	
	if(QDialog::Accepted){
		/*edit the database row*/
		//prepare the sql statment
		QString id = table->model()->index(rowIndex,0).data().toString();
		qry.prepare(QString("UPDATE OrganizationalUnits SET name = :name, objective = :objective, location = :location, tasks = :tasks where ou_id = %1").arg(id));
		
		//does nothing if the data is not changed
		if((dlg->name()==currentName) 
		   && (dlg->objective()==currentObjective) 
		   && (dlg->tasks()==currentTasks)
		   && (dlg->location()==currentLocation))
		   return;
		
		//gives each field it value	
		qry.bindValue(":name", dlg->name());
		qry.bindValue(":objective", dlg->objective());
		qry.bindValue(":location",dlg->location());
		qry.bindValue(":tasks", dlg->tasks());
				
		//ifsomething went wrong with the querry print what was it
		if (!qry.exec()){
			qDebug()<<qry.lastError();
		}
		refreshOuTable();			//update table data
	}
}
