#include <../headers/physical_technology_component.h>
#include <../headers/physical_technology_component_add_edit_dialog.h>
#include <QTableView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDebug>
#include <QtSql>
#include <QHeaderView>

PhysicalTechnologyComponent::PhysicalTechnologyComponent(QWidget* parent) : QDialog(parent) 
{

	//initialize widgets
	QHBoxLayout* mainlayout = new QHBoxLayout();
	QVBoxLayout* buttonsLayout = new QVBoxLayout;

	QPushButton* addTechComp = new QPushButton("Agregar Componente Físico");
	QPushButton* editTechComp = new QPushButton("Editar Componente Físico");
	QPushButton* deleteTechComp = new QPushButton("Eliminar Componente Físico");

	table = new QTableView;
    table->verticalHeader()->setVisible(false);

	refreshPhysicalTechnologyComponentTable();

	//add widgets to layout

	buttonsLayout->addWidget(addTechComp);
	buttonsLayout->addWidget(editTechComp);
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(deleteTechComp);

	mainlayout->addWidget(table);
	mainlayout->addLayout(buttonsLayout);
	this->setLayout(mainlayout);

	connect(addTechComp, SIGNAL(clicked()),
			this, SLOT(addPhysicalTechnologyComponent()));
	connect(editTechComp, SIGNAL(clicked()),
			this, SLOT(editPhysicalTechnologyComponent()));
}

void PhysicalTechnologyComponent::refreshPhysicalTechnologyComponentTable()
{
	//sets query model to show data in the table view
	QSqlQueryModel* physicalTechnologyComponentCatalogQueryModel = new QSqlQueryModel();
	physicalTechnologyComponentCatalogQueryModel->setQuery("SELECT physical_technology_component_id as ID, name as Nombre, objective as Objetivo, description as Descripción,"
														   "(SELECT location FROM Locations WHERE location_id = PhysicalTechnologiesComponents.location) AS Ubicación FROM PhysicalTechnologiesComponents");  //query the database	


	table->setSelectionBehavior(QAbstractItemView::SelectRows); // select entire rows
	table->setSelectionMode(QAbstractItemView::SingleSelection); //select one item at time
	table->setModel(physicalTechnologyComponentCatalogQueryModel); // sets PhysicalCatalogQueryModel as the table model
}

void PhysicalTechnologyComponent::addPhysicalTechnologyComponent()
{
	PhysicalTechnologyComponentAddEditDialog* dlg = new PhysicalTechnologyComponentAddEditDialog(this);
	QSqlQuery qry;         //QSqlQuery object that will save the data in to the database
	QSqlQuery getLocationId;
	int locationId = 0;
	QString queryString;

	//if ok is pressed in dlg
	if(dlg->exec() == QDialog::Accepted)
	{
		queryString = QString("SELECT location_id FROM Locations WHERE location = '%1'").arg(dlg->location());
		getLocationId.exec(queryString);
		while(getLocationId.next())
			locationId = getLocationId.value(0).toInt();
		
		/*inserts data to database*/
		//prepare the sql statment
		qry.prepare("INSERT INTO PhysicalTechnologiesComponents(name, objective, location, description) VALUES (:name, :objective, :location, :description)");
		
		//gives each field it value
		qry.bindValue(":name", dlg->name());
		qry.bindValue(":objective", dlg->objective());
		qry.bindValue(":location", locationId);
		qry.bindValue(":description", dlg->description());
		
		//if something went wrong with the querry print what was it
		if (!qry.exec()){
			qDebug()<<qry.lastError();
		}
		refreshPhysicalTechnologyComponentTable();    //updata table data
	}	
}

void PhysicalTechnologyComponent::editPhysicalTechnologyComponent()
{
	int rowIndex = table->selectionModel()->currentIndex().row();    //takes the index of the clicked row
 	PhysicalTechnologyComponentAddEditDialog* dlg = new PhysicalTechnologyComponentAddEditDialog(this);          
	QString currentName, currentdescription, currentObjective, currentLocation;
	QSqlQuery qry;         //this is the object that will hold the update query
	QSqlQuery getLocationId;
	int locationId = 0;
	QString queryString;   // to create the query that will map the ou and role name to their respectives ids	
	
		/*sets the text into the dialog controls*/
		dlg->setName(table->model()->index(rowIndex,1).data().toString());
		dlg->setObjective(table->model()->index(rowIndex,2).data().toString());
		dlg->setDescription(table->model()->index(rowIndex,3).data().toString()); 
		
		currentName = dlg->name();
		currentObjective = dlg->objective();
		currentdescription = dlg->description();	
		currentLocation = dlg->location();	
		
		dlg->exec();

		if(QDialog::Accepted){
			/*edit the database row*/
			//prepare the sql statment
			QString id = table->model()->index(rowIndex,0).data().toString();
			qry.prepare(QString("UPDATE PhysicalTechnologiesComponents SET name = :name, objective = :objective, description = :description, location = :location WHERE physical_technology_component_id = %1").arg(id));
			
			//does nothing if the data is not changed
			if((dlg->name()==currentName) 
			   && (dlg->objective()==currentObjective) 
			   && (dlg->description()==currentdescription)
			   && (dlg->location()==currentLocation))
				return;
			
			/*queryString = QString("SELECT location_id FROM Locations WHERE location = '%1'").arg(dlg->location());
			getLocationId.exec(queryString);
			while(getLocationId.next())
			locationId = getLocationId.value(0).toInt();*/
		

			//get current location id
			queryString = QString("SELECT location_id FROM Locations WHERE location = '%1'").arg(dlg->location());
			getLocationId.exec(queryString);
			while(getLocationId.next())
				locationId = getLocationId.value(0).toInt();
				
			//gives each field it value
			qry.bindValue(":name", dlg->name());
			qry.bindValue(":objective", dlg->objective());
			qry.bindValue(":description", dlg->description());
			qry.bindValue(":location", locationId);
			
			//ifsomething went wrong with the querry print what was it
			if (!qry.exec()){
				qDebug()<<qry.lastError();
			}
			refreshPhysicalTechnologyComponentTable();			//update table data
		}
}

