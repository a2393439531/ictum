#include <../headers/function.h>
#include <../headers/function_add_edit_dialog.h>
#include <QTableView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QDebug>
#include <QtSql>

Function::Function(QWidget* parent) : QDialog(parent) 
{

	//QWidget* actorWidget = new QWidget;

	//initialize widgets
	QHBoxLayout* mainlayout = new QHBoxLayout();
	QVBoxLayout* buttonsLayout = new QVBoxLayout;

	QPushButton* addFunction = new QPushButton("Agregar Funcion");
	QPushButton* editFunction = new QPushButton("Editar Funcion");
	QPushButton* deleteFunction = new QPushButton("Eliminar Funcion");

	table = new QTableView;
	
	refreshFunctionTable();

	//add widgets to layout

	buttonsLayout->addWidget(addFunction);
	buttonsLayout->addWidget(editFunction);
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(deleteFunction);

	mainlayout->addWidget(table);
	mainlayout->addLayout(buttonsLayout);
	this->setLayout(mainlayout);

	connect(addFunction, SIGNAL(clicked()),
			this, SLOT(addFunction()));
	connect(editFunction, SIGNAL(clicked()),
			this, SLOT(editFunction()));
}

void Function::refreshFunctionTable()
{
	//sets query model to show data in the table view
	QSqlQueryModel* functionCatalogQueryModel = new QSqlQueryModel();
	functionCatalogQueryModel->setQuery("SELECT * FROM Functions");  //query the database

	table->setSelectionBehavior(QAbstractItemView::SelectRows); // select entire rows
	table->setSelectionMode(QAbstractItemView::SingleSelection); //select one item at time
	table->setModel(functionCatalogQueryModel); // sets functionCatalogQueryModel as the table model
}
void Function::addFunction()
{
	FunctionAddEditDialog* dlg = new FunctionAddEditDialog(this);
	QSqlQuery qry;         //QSqlQuery object that will save the data in to the database function table
	QSqlQuery qrx;         // will save the relation between roles and functions in the RolesFunction junction table
	int roleId = 0;
	int functionId = 0;
	QSqlQuery getRoleId;
	QSqlQuery getFunctionId;
	QString queryString;
	QList<QString> roles;

	//if ok is pressed in dlg (actor add edit dialog)
	if(dlg->exec() == QDialog::Accepted)
	{
		/*inserts data to database*/
		//prepare the sql statment
		qry.prepare("INSERT INTO Functions(name, description) VALUES (:name, :description)");
		
		//gives each field it value
		qry.bindValue(":name", dlg->name());
		qry.bindValue(":description", dlg->description());

		//if something went wrong with the querry print what was it
		if (!qry.exec()){
			qDebug()<<qry.lastError();
		}
				
		/*take all usedsByListView Elements and populate the table with the current function id and each of the roles id's*/ 
		roles = dlg->usedBy().split(";");
		foreach(QString rol, roles){
			qrx.prepare("INSERT INTO RolesFunctions(rol_id, function_id) VALUES (:aRolId, :aFunctionId)");	

			queryString = QString("SELECT rol_id FROM Roles WHERE name = '%1'").arg(rol);
			getRoleId.exec(queryString);
			while(getRoleId.next())
				roleId = getRoleId.value(0).toInt();
			
			getFunctionId.exec("SELECT function_id FROM Functions ORDER BY function_id DESC LIMIT 1;");
			while(getFunctionId.next())
				functionId = getFunctionId.value(0).toInt();

			qrx.bindValue(":aRolId", roleId);
			qrx.bindValue(":aFunctionId",functionId);

			if(!qrx.exec())
				qDebug()<<qrx.lastError();
		}
		refreshFunctionTable();    //updata table data
	}
}

void Function::editFunction()
{
	int rowIndex = table->selectionModel()->currentIndex().row();    //takes the index of the clicked row
 	FunctionAddEditDialog* dlg = new FunctionAddEditDialog(this);          
	QString currentName, currentDescription;
	QSqlQuery qry;         //this is the object that will hold the update query
	QSqlQuery qrx;
	int roleId = 0;
	int functionId = 0;
	QSqlQuery getRoleId;
	QSqlQuery getFunctionId;
	QString queryString;
	QList<QString> roles;
	//int funcId, rolId;
	
		
	/*sets the text into the dialog controls	*/
	dlg->setName(table->model()->index(rowIndex,1).data().toString());
	dlg->setDescription(table->model()->index(rowIndex,2).data().toString());
	dlg->setUsedBy();
	
	currentName = dlg->name();
	currentDescription = dlg->description();
	
	//dlg->exec();
	
	if(dlg->exec() == QDialog::Accepted){
	

		/*edit the database row*/
		//prepare the sql statment
		QString id = table->model()->index(rowIndex,0).data().toString();
		qry.prepare(QString("UPDATE Functions SET name = :name, description = :description WHERE function_id = %1").arg(id));
		
		//gives each field it value	
		qry.bindValue(":name", dlg->name());
		qry.bindValue(":description", dlg->description());
				
		//ifsomething went wrong with the querry print what was it
		if (!qry.exec()){
			qDebug()<<qry.lastError();
		}
		
		/*roles = dlg->usedBy().split(";");
		QString funcId = table->model()->index(rowIndex,1).data().toString();  //function id is in the second column of the RolesFunctions table

		foreach(QString rol, roles){
			qrx.prepare(QString("UPDATE RolesFunctions SET rol_id = :aRolId, function_id = :aFunctionId WHERE function_id = %1").arg(funcId));	
			
			queryString = QString("SELECT rol_id FROM Roles WHERE name = '%1'").arg(rol);
			getRoleId.exec(queryString);
			while(getRoleId.next())
				roleId = getRoleId.value(0).toInt();
			
			getFunctionId.exec("SELECT function_id FROM Functions ORDER BY function_id DESC LIMIT 1;");
			while(getFunctionId.next())
				functionId = getFunctionId.value(0).toInt();

			qrx.bindValue(":aRolId", roleId);
			qrx.bindValue(":aFunctionId",functionId);

			if(!qrx.exec())
				qDebug()<<qrx.lastError();
		}*/
		refreshFunctionTable();    //updata table data
	}
}
