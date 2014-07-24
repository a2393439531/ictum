#include <../headers/information_system_service.h>
#include <../headers/information_system_service_add_edit_dialog.h>
#include <QTableView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDebug>
#include <QtSql>
#include <QHeaderView>

InformationSystemService::InformationSystemService(QWidget* parent) : QDialog(parent)
{
	//initializes the layouts
	QHBoxLayout* mainlayout = new QHBoxLayout();
	QVBoxLayout* buttonsLayout = new QVBoxLayout;

	//initializes the widgets
	QPushButton* addSystemService = new QPushButton("Agregar SS");
	QPushButton* editSystemService = new QPushButton("Editar SS");
	QPushButton* deleteSystemService = new QPushButton("Eliminar SS");

	table = new QTableView;
    table->verticalHeader()->setVisible(false);
        
	refreshInformationSystemServiceTable();
	
	buttonsLayout->addWidget(addSystemService);
	buttonsLayout->addWidget(editSystemService);
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(deleteSystemService);

	mainlayout->addWidget(table);
	mainlayout->addLayout(buttonsLayout);
	this->setLayout(mainlayout);

	connect(addSystemService, SIGNAL(clicked()),
			this, SLOT(addInformationSystemService()));
	connect(editSystemService, SIGNAL(clicked()),
			this, SLOT(editInformationSystemService()));
}

void InformationSystemService::refreshInformationSystemServiceTable()
{
	//creates an sql query model to show information from the data base in the table	
	QSqlQueryModel* issCatalogQueryModel = new QSqlQueryModel();
	//this query will be sent to the database	
	issCatalogQueryModel->setQuery("SELECT information_service_id as ID, name as Nombre, description as Descripción, (SELECT name FROM PhysicalTechnologiesComponents WHERE physical_technology_component_id = InformationSystemServices.physical_technology_component_id) AS 'Alojado En' FROM InformationSystemServices;");  
	
	table->setSelectionBehavior(QAbstractItemView::SelectRows);   //selects entires rows
	table->setSelectionMode(QAbstractItemView::SingleSelection);  //two rows can't be selected at the same time 
	table->setModel(issCatalogQueryModel);                      // tells the table to use the actorCatalogQueryModel
	issCatalogQueryModel->lastError();
}

void InformationSystemService::addInformationSystemService()
{
	InformationSystemServiceAddEditDialog* dlg = new InformationSystemServiceAddEditDialog(this);
	QSqlQuery qry;         //QSqlQuery object that will save the data in to the database
	QSqlQuery getPhysicalTechCompId;
	int physicalTechCompId = 0;
	QString queryString;

	//if ok is pressed in dlg
	qDebug()<<"antes de if accepted";
	if(dlg->exec() == QDialog::Accepted)
	{
		//gets physical technology id
		queryString = QString("SELECT physical_technology_component_id FROM PhysicalTechnologiesComponents WHERE name = '%1'").arg(dlg->physicalTechnologyComponent());
		getPhysicalTechCompId.exec(queryString);
		while(getPhysicalTechCompId.next())
			physicalTechCompId = getPhysicalTechCompId.value(0).toInt();

		/*inserts data to database*/
		//prepare the sql statment
		qry.prepare("INSERT INTO InformationSystemServices(name, description, physical_technology_component_id) VALUES (:name, :description, :PhysicalTechComp)");
		
		//gives each field it value
		qry.bindValue(":name", dlg->name());
		qry.bindValue(":description", dlg->description());
		qry.bindValue(":PhysicalTechComp", physicalTechCompId);
				
		//if something went wrong with the querry print what was it
		if (!qry.exec()){
			qDebug()<<qry.lastError();
		}
		refreshInformationSystemServiceTable();    //updata table data
	}	
}

void InformationSystemService::editInformationSystemService()
{
	int rowIndex = table->selectionModel()->currentIndex().row();    //takes the index of the clicked row
	InformationSystemServiceAddEditDialog* dlg = new InformationSystemServiceAddEditDialog(this);
	QSqlQuery qry;         //QSqlQuery object that will save the data in to the database
	QSqlQuery getPhysicalTechCompId;
	int physicalTechCompId = 0;
	QString queryString;
	QString currentName, currentdescription, hosted;


	/*sets the text into the dialog controls*/
	dlg->setName(table->model()->index(rowIndex,1).data().toString());
	dlg->setDescription(table->model()->index(rowIndex,2).data().toString());
		
	currentName = dlg->name();
	currentdescription = dlg->description();	
	hosted = dlg->physicalTechnologyComponent();	
	
	//if ok is pressed in dlg
	//dlg->exec();

	if(dlg->exec()==QDialog::Accepted){
		/*edit the database row*/
		//prepare the sql statment
		QString id = table->model()->index(rowIndex,0).data().toString();
		qry.prepare(QString("UPDATE InformationSystemServices SET name = :name, description = :description, physical_technology_component_id = :PhysicalTechComp WHERE information_service_id = %1").arg(id));
		
		//does nothing if the data is not changed
		if((dlg->name()==currentName) 
		   && (dlg->description()==currentdescription)
		   && (dlg->physicalTechnologyComponent()==hosted))
			return;
		
		//gets physical technology id
		queryString = QString("SELECT physical_technology_component_id FROM PhysicalTechnologiesComponents WHERE name = '%1'").arg(dlg->physicalTechnologyComponent());
		getPhysicalTechCompId.exec(queryString);
		while(getPhysicalTechCompId.next())
			physicalTechCompId = getPhysicalTechCompId.value(0).toInt();

		//gives each field it value
		qry.bindValue(":name", dlg->name());
		qry.bindValue(":description", dlg->description());
		qry.bindValue(":PhysicalTechComp", physicalTechCompId);
				
		//ifsomething went wrong with the querry print what was it
		if (!qry.exec()){
			qDebug()<<qry.lastError();
		}
		refreshInformationSystemServiceTable();    //updata table data
	}
}
