#include <../headers/location.h>
#include <../headers/location_add_edit_dialog.h>
#include <QTableView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QtSql>

Location::Location(QWidget* parent) : QDialog(parent) 
{

	//QWidget* actorWidget = new QWidget;

	//initialize widgets
	QHBoxLayout* mainlayout = new QHBoxLayout();
	QVBoxLayout* buttonsLayout = new QVBoxLayout;

	QPushButton* addLocation = new QPushButton("Agregar Ubicacion");
	QPushButton* editLocation = new QPushButton("Editar Ubicacion");
	QPushButton* deleteLocation = new QPushButton("Eliminar Ubicacion");

	table = new QTableView;

	refreshLocationTable();

	//add widgets to layout

	buttonsLayout->addWidget(addLocation);
	buttonsLayout->addWidget(editLocation);
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(deleteLocation);

	mainlayout->addWidget(table);
	mainlayout->addLayout(buttonsLayout);
	this->setLayout(mainlayout);

	connect(addLocation, SIGNAL(clicked()),
			this, SLOT(addLocation()));
	connect(editLocation, SIGNAL(clicked()),
			this, SLOT(editLocation()));
}

void Location::refreshLocationTable()
{
	//sets query model to show data in the table view
	QSqlQueryModel* locationCatalogQueryModel = new QSqlQueryModel();
	locationCatalogQueryModel->setQuery("SELECT * FROM Locations");  //query the database

	table->setSelectionBehavior(QAbstractItemView::SelectRows); // select entire rows
	table->setSelectionMode(QAbstractItemView::SingleSelection); //select one item at time
	table->setModel(locationCatalogQueryModel); // sets locationCatalogQueryModel as the table model
}
void Location::addLocation()
{
	LocationAddEditDialog* dlg = new LocationAddEditDialog(this); 
	QSqlQuery qry;         //QSqlQuery object that will save the data in to the database

	//if ok is pressed in dlg (actor add edit dialog)
	if(dlg->exec() == QDialog::Accepted)
	{
		/*inserts data to database*/
		//prepare the sql statment
		qry.prepare("INSERT INTO Locations(location) VALUES (:location)");
		
		//gives each field it value
		qry.bindValue(":location", dlg->location());
				
		//if something went wrong with the querry print what was it
		if (!qry.exec()){
			qDebug()<<qry.lastError();
		}
		refreshLocationTable();    //updata table data
	}
}

void Location::editLocation()
{
	int rowIndex = table->selectionModel()->currentIndex().row();    //takes the index of the clicked row
 	LocationAddEditDialog* dlg = new LocationAddEditDialog(this);          
	QString currentLocation;
	QSqlQuery qry;         //this is the object that will hold the update query
	
	/*sets the text into the dialog controls*/
	dlg->setLocation(table->model()->index(rowIndex,1).data().toString());
		
	currentLocation = dlg->location();
	dlg->exec();
	
	if(QDialog::Accepted){
		/*edit the database row*/
		//prepare the sql statment
		QString id = table->model()->index(rowIndex,0).data().toString();
		qry.prepare(QString("UPDATE Locations SET location = :location where location_id = %1").arg(id));
		
		//does nothing if the data is not changed
		if(dlg->location()==currentLocation)
		   return;
		
		//gives each field it value	
		qry.bindValue(":location", dlg->location());
			
		//ifsomething went wrong with the querry print what was it
		if (!qry.exec()){
			qDebug()<<qry.lastError();
		}
		qDebug()<<"antes de actualizar la tabla";
		refreshLocationTable();			//update table data
	}
}
