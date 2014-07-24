#include "../headers/role_process_matrix.h"
#include "../headers/add_processes_helper_dialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListView>
#include <QTableView>
#include <QtSql>
#include <QPushButton>
#include <QStandardItemModel>
#include <QHeaderView>

RoleProcessMatrix::RoleProcessMatrix(QWidget* parent) : QDialog(parent)
{
	QVBoxLayout* mainlayout = new QVBoxLayout;
	QHBoxLayout* tableListLayout = new QHBoxLayout;
	QHBoxLayout* buttonsLayout = new QHBoxLayout;

	rolesTable = new QTableView;
	processesList = new QListView;
	QPushButton* add = new QPushButton("agregar");
	QPushButton* edit = new QPushButton("Editar");
	QPushButton* del = new QPushButton("Eliminar"); 
	processesListModel = new QStandardItemModel;
	
	//search for functions Names
	QSqlQueryModel* roleQueryModel = new QSqlQueryModel;
	roleQueryModel->setQuery("SELECT rol_id as ID, name as Nombre FROM Roles");

    rolesTable->verticalHeader()->setVisible(false);
	rolesTable->setSelectionBehavior(QAbstractItemView::SelectRows);   //selects entires rows	
	rolesTable->setSelectionMode(QAbstractItemView::SingleSelection);  //two rows can't be selected at the same time
	rolesTable->setModel(roleQueryModel);

	tableListLayout->addWidget(rolesTable);
	tableListLayout->addStretch();
	tableListLayout->addWidget(processesList);
	buttonsLayout->addWidget(add);
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(edit);
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(del);
	mainlayout->addLayout(tableListLayout);
	mainlayout->addStretch();
	mainlayout->addLayout(buttonsLayout);

	this->setLayout(mainlayout);

	connect(rolesTable, SIGNAL(clicked(const QModelIndex&)),
			this, SLOT(revealProcesses(const QModelIndex&)));
	connect(add, SIGNAL(clicked()),
			this, SLOT(addRoleProcessRelation()));
	connect(del, SIGNAL(clicked()),
			this, SLOT(delRoleProcessRelationElement()));


}

void RoleProcessMatrix::revealProcesses(const QModelIndex& index)
{
	QSqlQueryModel* processesListQuery = new QSqlQueryModel();
	QString currentRolId;

	currentRolId = rolesTable->model()->index(index.row(),0).data().toString();
	processesListQuery->setQuery(QString("SELECT name AS Process FROM RolesProcesses INNER JOIN Processes ON Processes.process_id = RolesProcesses.process_id WHERE RolesProcesses.rol_id = %1 GROUP BY name").arg(currentRolId));
		
	processesList->setModel(processesListQuery);
}

void RoleProcessMatrix::addRoleProcessRelation()
{
	AddProcessesHelperDialog* dlgHelper = new AddProcessesHelperDialog(this);
	QStandardItemModel* selectedProcessesModel = new QStandardItemModel;
	QSqlQuery qry;
	QSqlQuery getProcessId;
	QList<QString> currentElementsInTheList;
	QList<QString> newSelectedElements;
	QList<QString> newListElements;
	int currentElementsInTheListRow = 0;
	int row = 0;  // the row of the model
	int processId = 0;
	int roleId = 0;
	
	if (dlgHelper->exec()==QDialog::Accepted){

		// takes all the elements of the list view
		while(processesList->model()->index(currentElementsInTheListRow,0).isValid())
			currentElementsInTheList << processesList->model()->index(currentElementsInTheListRow++,0).data().toString();

		currentElementsInTheListRow = 0; //clean the processesList listview counter of latter use
		
		//takes all the new elemets selected from the dlgHelper Dialog 
		foreach(QModelIndex itemIndex, dlgHelper->processList->selectionModel()->selectedIndexes()){
			newSelectedElements << dlgHelper->processList->model()->index(itemIndex.row(), itemIndex.column()).data().toString();
		}

		
		//to not repeat elements in the list
		foreach(QString element, newSelectedElements){
			if (currentElementsInTheList.indexOf(element) == -1) //if indexOf Returns -1 the element was not in the list of current elements
				currentElementsInTheList << element;
		}
		
		//adds the elements in the list view model
		foreach(QString element, currentElementsInTheList){
			QStandardItem* i = new QStandardItem(element);
			selectedProcessesModel->setItem(row++,0,i);
		}
		processesList->setModel(selectedProcessesModel); //display the elements in the list 

		//adds the elements in the database
		foreach(QString element, currentElementsInTheList){
		qry.prepare("INSERT INTO RolesProcesses (rol_id, process_id) VALUES (:rol_id, :process_id)");
		
		getProcessId.exec(QString("SELECT process_id FROM Processes WHERE name = '%1'").arg(element));
		while(getProcessId.next())
			processId = getProcessId.value(0).toInt();

		//takes the role id form the rolesTable (the table in the dialog)
		roleId = rolesTable->model()->index(rolesTable->selectionModel()->currentIndex().row(),0).data().toInt();
		
		qry.bindValue(":rol_id", roleId);
		qry.bindValue(":process_id", processId);

		if (!qry.exec())
			qDebug()<<qry.lastError();
		}
		
	}
}

void RoleProcessMatrix::delRoleProcessRelationElement()
{
	QSqlQuery qry;
	QSqlQuery getProcessId;   //takes the processId of the element
	//takes the clicked element in the processList listview
	QString element = processesList->model()->index(processesList->selectionModel()->currentIndex().row(),0).data().toString();
	//takes the clicked rol_id of the rolesTable
	QString rolId = rolesTable->model()->index(rolesTable->selectionModel()->currentIndex().row(),0).data().toString();
	int processId = 0;
	QStandardItemModel* processesListModel = new QStandardItemModel;
	int row = 0;  // to count the processesListModel rows
	int newModelrows = 0; //to puts element in the right place in the processListModel
	QString currentListElement;

	qry.prepare("DELETE FROM RolesProcesses WHERE rol_id = :rol_id AND process_id = :process_id");

	//get the process_id value
	getProcessId.exec(QString("SELECT process_id FROM Processes WHERE name = '%1'").arg(element));
	while(getProcessId.next())
		processId = getProcessId.value(0).toInt();

	qry.bindValue(":rol_id",rolId);
	qry.bindValue(":process_id",processId);

	if(!qry.exec())
		qDebug()<<qry.lastError();
	
	//adds valid elements to the model
	while(processesList->model()->index(row,0).isValid()){
		currentListElement = processesList->model()->index(row++,0).data().toString();
		if(currentListElement != element){
			QStandardItem* i = new QStandardItem(currentListElement);
			processesListModel->setItem(newModelrows++,0,i);
		}
	}

	processesList->setModel(processesListModel);    //show modifications in the list view

}
