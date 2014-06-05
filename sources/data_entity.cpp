#include "../headers/data_entity.h"
#include "../headers/data_entity_add_edit_dialog.h"
#include <QTableView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDebug>
#include <QtSql>

DataEntity::DataEntity(QWidget* parent) : QDialog(parent)
{
	//initializes the layouts
	QHBoxLayout* mainlayout = new QHBoxLayout();
	QVBoxLayout* buttonsLayout = new QVBoxLayout;

	//initializes the widgets
	QPushButton* addDataEntity = new QPushButton("Agregar Entidad de Datos");
	QPushButton* editDataEntity = new QPushButton("Editar Entidad de Datos");
	QPushButton* deleteDataEntity = new QPushButton("Eliminar Entidad de Datos");

	table = new QTableView;
	
	refreshDataEntityTable();

	buttonsLayout->addWidget(addDataEntity);
	buttonsLayout->addWidget(editDataEntity);
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(deleteDataEntity);

	mainlayout->addWidget(table);
	mainlayout->addLayout(buttonsLayout);
	this->setLayout(mainlayout);

	connect(addDataEntity, SIGNAL(clicked()),
			this, SLOT(addDataEntity()));
	connect(editDataEntity, SIGNAL(clicked()),
	  this, SLOT(editDataEntity()));
}

void DataEntity::refreshDataEntityTable()
{
	//sets query model to show data in the table view
	QSqlQueryModel* dataEntityCatalogQueryModel = new QSqlQueryModel();
	dataEntityCatalogQueryModel->setQuery("SELECT data_entity_id, name, description,(SELECT name FROM InformationSystemServices WHERE InformationSystemServices.information_service_id = DataEntity.information_service_id ) AS 'Processed By' FROM DataEntity");  //query the database

	table->setSelectionBehavior(QAbstractItemView::SelectRows); // select entire rows
	table->setSelectionMode(QAbstractItemView::SingleSelection); //select one item at time
	table->setModel(dataEntityCatalogQueryModel); // sets roleCatalogQueryModel as the table model
}

void DataEntity::addDataEntity()
{
	DataEntityAddEditDialog* dlg = new DataEntityAddEditDialog(this);
	QSqlQuery qry;         //QSqlQuery object that will save the data in to the database function table
	int infoServiceId = 0;
	QSqlQuery getInfoServiceId;
	
	//if ok is pressed in dlg (actor add edit dialog)
	if(dlg->exec() == QDialog::Accepted)
	{
		/*inserts data to database*/
		//prepare the sql statment
		qry.prepare("INSERT INTO DataEntity(name, description, information_service_id) VALUES (:name, :description, :infoServiceId)");
		
		//queryString = QString("SELECT information_service_id FROM InformationSystemServices WHERE name ='%1'").arg(dlg->processedBy());
		getInfoServiceId.exec(QString("SELECT information_service_id FROM InformationSystemServices WHERE name ='%1'").arg(dlg->processedBy()));
		while(getInfoServiceId.next())
			infoServiceId = getInfoServiceId.value(0).toInt();
		

		//gives each field it value
		qry.bindValue(":name", dlg->name());
		qry.bindValue(":description", dlg->description());
		qry.bindValue(":infoServiceId",infoServiceId);

		//if something went wrong with the querry print what was it
		if (!qry.exec()){
			qDebug()<<qry.lastError();
		}
			refreshDataEntityTable();    //updata table data
	}
	
			
}

void DataEntity::editDataEntity()
{
	int rowIndex = table->selectionModel()->currentIndex().row();    //takes the index of the clicked row
	DataEntityAddEditDialog* dlg = new DataEntityAddEditDialog(this);
	QString currentName, currentDescription, currentProcessedBy;
	QSqlQuery qry;         //this is the object that will hold the update query
	int infoServiceId = 0;
	QSqlQuery getInfoServiceId;
	
		
	/*sets the text into the dialog controls	*/
	dlg->setName(table->model()->index(rowIndex,1).data().toString());
	dlg->setDescription(table->model()->index(rowIndex,2).data().toString());
		
	currentName = dlg->name();
	currentDescription = dlg->description();
	currentProcessedBy = dlg->processedBy();
	
	//dlg->exec();
	
	if(dlg->exec() == QDialog::Accepted){
		/*edit the database row*/
		//prepare the sql statment
		QString id = table->model()->index(rowIndex,0).data().toString();
		qry.prepare(QString("UPDATE DataEntity SET name = :name, description = :description, information_service_id = :infoServiceId  WHERE data_entity_id = %1").arg(id));
		
		//queryString = QString("SELECT information_service_id FROM InformationSystemServices WHERE name ='%1'").arg(dlg->processedBy());
		getInfoServiceId.exec(QString("SELECT information_service_id FROM InformationSystemServices WHERE name ='%1'").arg(dlg->processedBy()));
		while(getInfoServiceId.next())
			infoServiceId = getInfoServiceId.value(0).toInt();
		

		//gives each field it value	
		qry.bindValue(":name", dlg->name());
		qry.bindValue(":description", dlg->description());
		qry.bindValue(":infoServiceId", infoServiceId);
				
		//ifsomething went wrong with the querry print what was it
		if (!qry.exec()){
			qDebug()<<qry.lastError();
		}

		refreshDataEntityTable();    //updata table data	
	}
}
