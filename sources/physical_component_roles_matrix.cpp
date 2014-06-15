#include "../headers/physical_component_roles_matrix.h"
#include "../headers/add_roles_helper_dialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListView>
#include <QTableView>
#include <QtSql>
#include <QPushButton>
#include <QStandardItemModel>

PhysicalComponentRolesMatrix::PhysicalComponentRolesMatrix(QWidget* parent) : QDialog(parent)
{
	QVBoxLayout* mainlayout = new QVBoxLayout;
	QHBoxLayout* tableListLayout = new QHBoxLayout;
	QHBoxLayout* buttonsLayout = new QHBoxLayout;

	physicalComponentsTable= new QTableView;
	rolesList = new QListView;
	QPushButton* add = new QPushButton("agregar");
	QPushButton* edit = new QPushButton("Editar");
	QPushButton* del = new QPushButton("Eliminar"); 
	rolesListModel = new QStandardItemModel;
	
	//search for functions Names
	QSqlQueryModel* functionQueryModel = new QSqlQueryModel;
	functionQueryModel->setQuery("SELECT physical_technology_component_id, name FROM PhysicalTechnologiesComponents");

	physicalComponentsTable->setSelectionBehavior(QAbstractItemView::SelectRows);   //selects entires rows	
	physicalComponentsTable->setSelectionMode(QAbstractItemView::SingleSelection);  //two rows can't be selected at the same time
	physicalComponentsTable->setModel(functionQueryModel);

	tableListLayout->addWidget(physicalComponentsTable);
	tableListLayout->addStretch();
	tableListLayout->addWidget(rolesList);
	buttonsLayout->addWidget(add);
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(edit);
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(del);
	mainlayout->addLayout(tableListLayout);
	mainlayout->addStretch();
	mainlayout->addLayout(buttonsLayout);

	this->setLayout(mainlayout);

	connect(physicalComponentsTable, SIGNAL(clicked(const QModelIndex&)),
            this, SLOT(revealRoles(const QModelIndex&)));
	connect(add, SIGNAL(clicked()),
			this, SLOT(addPhysicalComponentRolesRelation()));
	connect(del, SIGNAL(clicked()),
			this, SLOT(delPhysicalComponentRolesRelation()));
}

void PhysicalComponentRolesMatrix::revealRoles(const QModelIndex& index)
{
	QSqlQueryModel* physicalComponentListQuery = new QSqlQueryModel();
	QString currentPhysicalComponentId;

	currentPhysicalComponentId = physicalComponentsTable->model()->index(index.row(),0).data().toString();
	physicalComponentListQuery->setQuery(QString("SELECT name FROM PhysicalComponentsRoles INNER JOIN Roles ON Roles.rol_id = PhysicalComponentsRoles.rol_id WHERE PhysicalComponentsRoles.physical_technology_component_id = %1 GROUP BY name").arg(currentPhysicalComponentId));
		
	rolesList->setModel(physicalComponentListQuery);
    qDebug()<<physicalComponentListQuery->lastError();
}

void PhysicalComponentRolesMatrix::addPhysicalComponentRolesRelation()
{
	AddRolesHelperDialog* dlgHelper = new AddRolesHelperDialog(this);
	QStandardItemModel* rolesListModel = new QStandardItemModel;
	QSqlQuery qry;
	QSqlQuery getRoleId;
	int rolId = 0;
	int physicalComponentId = 0;
	int row=0; //keeps track of the rows when the returning selected items from dlgHelpet
	int modelRow = 0;
	int column = 0; 
	QList<QString> currentElementsInTheList;
	QList<QString> newSelectedElements;
		
	if (dlgHelper->exec()==QDialog::Accepted){
		
		// takes all the current elements in the listview
		while(rolesList->model()->index(row, column).isValid())
			currentElementsInTheList << rolesList->model()->index(row++,column).data().toString();

		//takes the selected elements of the dlgHelper Dialog
		foreach(QModelIndex itemIndex, dlgHelper->rolesList->selectionModel()->selectedIndexes()){
			newSelectedElements << dlgHelper->rolesList->model()->index(itemIndex.row(), itemIndex.column()).data().toString();
		}
		// to no repeat any elements in the list
		foreach(QString element, newSelectedElements){
			if(currentElementsInTheList.indexOf(element) == -1) // if the element is not found the indexOf method returns -1
				currentElementsInTheList << element;
		}
		//adding elements to the model in order to desplay then in the list
		foreach(QString elements, currentElementsInTheList){
			QStandardItem* i = new QStandardItem(elements);
			rolesListModel->setItem(modelRow++, 0, i); //add an item to the usedBy model(which is selectedRolesModel)
		}
		rolesList->setModel(rolesListModel);   		//displays the elements in the list
	}

    foreach(QString element, currentElementsInTheList){
		qry.prepare("INSERT INTO PhysicalComponentsRoles(physical_technology_component_id, rol_id) VALUES (:physical_technology_component_id, :rol_id)");

		getRoleId.exec(QString("SELECT rol_id FROM Roles WHERE name = '%1'").arg(element));
		while(getRoleId.next())
			rolId = getRoleId.value(0).toInt();
        
		physicalComponentId = physicalComponentsTable->model()->index(physicalComponentsTable->selectionModel()->currentIndex().row(),0).data().toInt();

		qry.bindValue(":rol_id", rolId);
		qry.bindValue(":physical_technology_component_id", physicalComponentId);

		if (!qry.exec())
			qDebug()<<qry.lastError();
	} 
}


void PhysicalComponentRolesMatrix::delPhysicalComponentRolesRelation()
{
	
	QSqlQuery qry;
	QSqlQuery getRoleId;   //takes the processId of the element
	//takes the clicked element in the rolesList listview
	QString element = rolesList->model()->index(rolesList->selectionModel()->currentIndex().row(),0).data().toString();
	//takes the clicked function_id of the rolesTable
	QString physicalComponentId = physicalComponentsTable->model()->index(physicalComponentsTable->selectionModel()->currentIndex().row(),0).data().toString();
	int rolId = 0;
	QStandardItemModel* rolesListModel = new QStandardItemModel;
	int row = 0;  // to count the processesListModel rows
	int newModelrows = 0; //to puts element in the right place in the processListModel
	QString currentListElement;

	qry.prepare("DELETE FROM PhysicalComponentsRoles WHERE rol_id = :rol_id AND physical_technology_component_id = :physical_technology_component_id");

	//get the role_id value
	getRoleId.exec(QString("SELECT rol_id FROM Roles WHERE name = '%1'").arg(element));
	while(getRoleId.next())
		rolId = getRoleId.value(0).toInt();
	
	qry.bindValue(":rol_id", rolId);
	qry.bindValue(":physical_technology_component_id", physicalComponentId);
	
	qDebug()<<rolId;
	qDebug()<<physicalComponentId;
		
	if(!qry.exec())
	  qDebug()<<qry.lastError();
	
	//adds valid elements to the model
	while(rolesList->model()->index(row,0).isValid()){
		currentListElement = rolesList->model()->index(row++,0).data().toString();
		if(currentListElement != element){
			QStandardItem* i = new QStandardItem(currentListElement);
			rolesListModel->setItem(newModelrows++,0,i);
		}
	}
	rolesList->setModel(rolesListModel);    //show modifications in the list view
}
