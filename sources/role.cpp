#include <../headers/role.h>
#include <../headers/role_add_edit_dialog.h>
#include <QTableView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDebug>
#include <QtSql>
#include <QHeaderView>

Role::Role(QWidget* parent) : QDialog(parent) 
{

	//QWidget* actorWidget = new QWidget;

	//initialize widgets
	QHBoxLayout* mainlayout = new QHBoxLayout();
	QVBoxLayout* buttonsLayout = new QVBoxLayout;

	QPushButton* addRole = new QPushButton("Agregar Rol");
	QPushButton* editRole = new QPushButton("Editar Rol");
	QPushButton* deleteRole = new QPushButton("Eliminar Rol");

	table = new QTableView;
    table->verticalHeader()->setVisible(false);
	refreshRoleTable();

	//add widgets to layout

	buttonsLayout->addWidget(addRole);
	buttonsLayout->addWidget(editRole);
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(deleteRole);

	mainlayout->addWidget(table);
	mainlayout->addLayout(buttonsLayout);
	this->setLayout(mainlayout);

	connect(addRole, SIGNAL(clicked()),
			this, SLOT(addRole()));
	connect(editRole, SIGNAL(clicked()),
			this, SLOT(editRole()));
}

void Role::refreshRoleTable()
{
	//sets query model to show data in the table view
	QSqlQueryModel* roleCatalogQueryModel = new QSqlQueryModel();
	roleCatalogQueryModel->setQuery("SELECT rol_id AS ID, name AS Nombre, objective AS Objetivo, tasks AS Tareas FROM Roles");  //query the database

	table->setSelectionBehavior(QAbstractItemView::SelectRows); // select entire rows
	table->setSelectionMode(QAbstractItemView::SingleSelection); //select one item at time
	table->setModel(roleCatalogQueryModel); // sets roleCatalogQueryModel as the table model
    qDebug()<<roleCatalogQueryModel->lastError();
}
void Role::addRole()
{
	RoleAddEditDialog* dlg = new RoleAddEditDialog(this); 
	QSqlQuery qry;         //QSqlQuery object that will save the data in to the database

	//if ok is pressed in dlg
	if(dlg->exec() == QDialog::Accepted)
	{
		/*inserts data to database*/
		//prepare the sql statment
		qry.prepare("INSERT INTO Roles(name, objective, tasks) VALUES (:name, :objective, :tasks)");
		
		//gives each field it value
		qry.bindValue(":name", dlg->name());
		qry.bindValue(":objective", dlg->objective());
		qry.bindValue(":tasks", dlg->tasks());
		
		//if something went wrong with the querry print what was it
		if (!qry.exec()){
			qDebug()<<qry.lastError();
		}
		refreshRoleTable();    //updata table data
	}
}

void Role::editRole()
{
	int rowIndex = table->selectionModel()->currentIndex().row();    //takes the index of the clicked row
 	RoleAddEditDialog* dlg = new RoleAddEditDialog(this);          
	QString currentName, currentObjective, currentTasks;
	QSqlQuery qry;         //this is the object that will hold the update query
	
	/*sets the text into the dialog controls*/
	dlg->setName(table->model()->index(rowIndex,1).data().toString());
	dlg->setObjective(table->model()->index(rowIndex,2).data().toString());
	dlg->setTasks(table->model()->index(rowIndex,3).data().toString()); 
		
	currentName = dlg->name();
	currentObjective = dlg->objective();
	currentTasks = dlg->tasks();	
	
	dlg->exec();
	
	if(QDialog::Accepted){
		/*edit the database row*/
		//prepare the sql statment
		QString id = table->model()->index(rowIndex,0).data().toString();
		qry.prepare(QString("UPDATE Roles SET name = :name, objective = :objective, tasks = :tasks where rol_id = %1").arg(id));
		
		//does nothing if the data is not changed
		if((dlg->name()==currentName) 
		   && (dlg->objective()==currentObjective) 
		   && (dlg->tasks()==currentTasks))
		   return;
		
		//gives each field it value	
		qry.bindValue(":name", dlg->name());
		qry.bindValue(":objective", dlg->objective());
		qry.bindValue(":tasks", dlg->tasks());
				
		//ifsomething went wrong with the querry print what was it
		if (!qry.exec()){
			qDebug()<<qry.lastError();
		}
		qDebug()<<"antes de actualizar la tabla";
		refreshRoleTable();			//update table data
	}
}
 
