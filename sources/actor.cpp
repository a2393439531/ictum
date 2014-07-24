#include "../headers/actor.h"
#include "../headers/actor_add_edit_dialog.h"
#include <QTableView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDebug>
#include <QtSql>
#include <QHeaderView>

Actor::Actor(QWidget* parent) : QDialog(parent)
{
	//initializes the layouts
	QHBoxLayout* mainlayout = new QHBoxLayout();
	QVBoxLayout* buttonsLayout = new QVBoxLayout;

	//initializes the widgets
	QPushButton* addActor = new QPushButton("Agregar Actor");
	QPushButton* editActor = new QPushButton("Editar Actor");
	QPushButton* deleteActor = new QPushButton("Eliminar Actor");

	table = new QTableView;
    table->verticalHeader()->setVisible(false);
	refreshActorTable();

	/*CheckBoxDelegate *testDelegate = new CheckBoxDelegate();
	  table->setItemDelegateForColumn(0, testDelegate);*/

	buttonsLayout->addWidget(addActor);
	buttonsLayout->addWidget(editActor);
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(deleteActor);

	mainlayout->addWidget(table);
	mainlayout->addLayout(buttonsLayout);
	this->setLayout(mainlayout);

	connect(addActor, SIGNAL(clicked()),
			this, SLOT(addActor()));
	connect(editActor, SIGNAL(clicked()),
			this, SLOT(editActor()));
}

void Actor::refreshActorTable()
{
	//creates an sql query model to show information from the data base in the table	
	QSqlQueryModel* actorCatalogQueryModel = new QSqlQueryModel();
	actorCatalogQueryModel->setQuery("SELECT actor_id AS ID,name AS Nombre,middleName AS 'Segundo Nombre',lastName AS 'Apellido',"
									 "(SELECT name FROM Roles WHERE rol_id = Actors.rol_id) AS Rol," 
									 "(SELECT name FROM OrganizationalUnits WHERE ou_id = Actors.ou_id) AS OU FROM Actors");    //this query will be sent to the database
	
	table->setSelectionBehavior(QAbstractItemView::SelectRows);   //selects entires rows
	table->setSelectionMode(QAbstractItemView::SingleSelection);  //two rows can't be selected at the same time 
	table->setModel(actorCatalogQueryModel);                      // tells the table to use the actorCatalogQueryModel
}

void Actor::addActor()
{
	ActorAddEditDialog* dlg = new ActorAddEditDialog(this); 
	QSqlQuery qry;         //QSqlQuery object that will save the data in to the database
	QSqlQuery getRoleId;   //QSqlQuery object that will map the rol name in the role combobox to a rol_id (actors table saves roles id not roles names)
	QSqlQuery getOuId;     //QSqlQuery object that will map the organizational unit name in the ou combobox to a ou_id (actors table saves ou id not ou names)
	int roleId = 0;        // to save the role id number
	int ouId = 0;          // to save the ou id number
	QString queryString;   // to create the query that will map the ou and role name to their respectives ids
		
	//if ok is pressed in dlg (actor add edit dialog)
	if(dlg->exec() == QDialog::Accepted)
	{
		//get current role id
		queryString = QString("SELECT rol_id FROM Roles WHERE name = '%1'").arg(dlg->role());
		getRoleId.exec(queryString);
		while(getRoleId.next())
			roleId = getRoleId.value(0).toInt();
				
		// get current ou id
		queryString = QString("SELECT ou_id FROM OrganizationalUnits WHERE name ='%1'").arg(dlg->ou());
		getOuId.exec(queryString);
		while(getOuId.next())
			ouId = getOuId.value(0).toInt();
				
		/*inserts data to database*/
		//prepare the sql statment
		qry.prepare("INSERT INTO Actors(name, middleName, lastName, rol_id, ou_id ) VALUES (:name, :middleName, :lastName, :rol_id, :ou_id)");
		
		//gives each field it value
		qry.bindValue(":name", dlg->name());
		qry.bindValue(":middleName", dlg->middleName());
		qry.bindValue(":lastName", dlg->lastName());
		qry.bindValue(":rol_id", roleId);
		qry.bindValue(":ou_id", ouId);
		
		//if something went wrong with the querry print what was it
		if (!qry.exec()){
			qDebug()<<qry.lastError();
		}
		refreshActorTable();    //updata table data
	}
}

void Actor::editActor()
{
	int rowIndex = table->selectionModel()->currentIndex().row();    //takes the index of the clicked row
 	ActorAddEditDialog* dlg = new ActorAddEditDialog(this);          
	QString currentName, currentMiddleName, currentLastName, currentRole, currentOu;
	QSqlQuery getRoleId;   //QSqlQuery object that will map the rol name in the role combobox to a rol_id (actors table saves roles id not roles names)
	QSqlQuery getOuId;     //QSqlQuery object that will map the organizational unit name in the ou combobox to a ou_id (actors table saves ou id not ou names)
	QSqlQuery qry;         //this is the object that will hold the update query
	int roleId = 0;        // to save the role id number
	int ouId = 0;          // to save the ou id number
	QString queryString;   // to create the query that will map the ou and role name to their respectives ids	

		/*sets the text into the dialog controls*/
		dlg->setName(table->model()->index(rowIndex,1).data().toString());
		dlg->setMiddleName(table->model()->index(rowIndex,2).data().toString());
		dlg->setLastName(table->model()->index(rowIndex,3).data().toString()); 
		dlg->setRole(table->model()->index(rowIndex,4).data().toString());
		dlg->setOu(table->model()->index(rowIndex,5).data().toString());

		currentName = dlg->name();
		currentMiddleName = dlg->middleName();
		currentLastName = dlg->lastName();	
		currentRole = dlg->role();	
		currentOu = dlg->ou();
		
		dlg->exec();

		if(QDialog::Accepted){
						
			
			/*edit the database row*/
			//prepare the sql statment
			QString id = table->model()->index(rowIndex,0).data().toString();
			qry.prepare(QString("UPDATE Actors SET name = :name, middleName = :middleName, lastName = :lastName, rol_id = :rolId, ou_id = :ouId where actor_id = %1").arg(id));
			
			//does nothing if the data is not changed
			if((dlg->name()==currentName) 
			   && (dlg->middleName()==currentMiddleName) 
			   && (dlg->lastName()==currentLastName)
			   && (dlg->role()==currentRole)
			   && (dlg->ou()==currentOu))
				return;
			
			//get current role id
			queryString = QString("SELECT rol_id FROM Roles WHERE name = '%1'").arg(dlg->role());
			getRoleId.exec(queryString);
			while(getRoleId.next())
				roleId = getRoleId.value(0).toInt();
			
			// get current ou id
			queryString = QString("SELECT ou_id FROM OrganizationalUnits WHERE name ='%1'").arg(dlg->ou());
			getOuId.exec(queryString);
			while(getOuId.next())
				ouId = getOuId.value(0).toInt();
	

			//gives each field it value
			qry.bindValue(":name", dlg->name());
			qry.bindValue(":middleName", dlg->middleName());
			qry.bindValue(":lastName", dlg->lastName());
			qry.bindValue(":rolId", roleId);
			qry.bindValue(":ouId", ouId);
			
			//ifsomething went wrong with the querry print what was it
			if (!qry.exec()){
				qDebug()<<qry.lastError();
			}
			qDebug()<<"antes de actualizar la tabla";
			refreshActorTable();			//update table data
		}
}



