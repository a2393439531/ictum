#include "../headers/info_system_services_roles_matrix.h"
#include "../headers/add_roles_helper_dialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListView>
#include <QTableView>
#include <QtSql>
#include <QPushButton>
#include <QStandardItemModel>
#include <QHeaderView>

InfoSystemServicesRolesMatrix::InfoSystemServicesRolesMatrix(QWidget* parent) : QDialog(parent)
{
	QVBoxLayout* mainlayout = new QVBoxLayout;
	QHBoxLayout* tableListLayout = new QHBoxLayout;
	QHBoxLayout* buttonsLayout = new QHBoxLayout;

	infoSystemServicesTable= new QTableView;
	rolesList = new QListView;
	QPushButton* add = new QPushButton("agregar");
	QPushButton* edit = new QPushButton("Editar");
	QPushButton* del = new QPushButton("Eliminar"); 
	rolesListModel = new QStandardItemModel;
	
	//search for functions Names
	QSqlQueryModel* functionQueryModel = new QSqlQueryModel;
	functionQueryModel->setQuery("SELECT information_service_id as ID, name as Name FROM InformationSystemServices");

    infoSystemServicesTable->verticalHeader()->setVisible(false);
	infoSystemServicesTable->setSelectionBehavior(QAbstractItemView::SelectRows);   //selects entires rows	
	infoSystemServicesTable->setSelectionMode(QAbstractItemView::SingleSelection);  //two rows can't be selected at the same time
	infoSystemServicesTable->setModel(functionQueryModel);

	tableListLayout->addWidget(infoSystemServicesTable);
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

	connect(infoSystemServicesTable, SIGNAL(clicked(const QModelIndex&)),
            this, SLOT(revealRoles(const QModelIndex&)));
	connect(add, SIGNAL(clicked()),
			this, SLOT(addInfoSystemServicesRolesRelation()));
	connect(del, SIGNAL(clicked()),
			this, SLOT(delInfoSystemServicesRolesRelation()));
}

void InfoSystemServicesRolesMatrix::revealRoles(const QModelIndex& index)
{
	QSqlQueryModel* infoSystemServiceListQuery = new QSqlQueryModel();
	QString currentInfoSystemServiceId;

	currentInfoSystemServiceId = infoSystemServicesTable->model()->index(index.row(),0).data().toString();
	infoSystemServiceListQuery->setQuery(QString("SELECT name FROM InfoSystemServicesRoles INNER JOIN Roles ON Roles.rol_id = InfoSystemServicesRoles.rol_id WHERE InfoSystemServicesRoles.information_service_id = %1 GROUP BY name").arg(currentInfoSystemServiceId));
		
	rolesList->setModel(infoSystemServiceListQuery);
    qDebug()<<infoSystemServiceListQuery->lastError();
}

void InfoSystemServicesRolesMatrix::addInfoSystemServicesRolesRelation()
{
	AddRolesHelperDialog* dlgHelper = new AddRolesHelperDialog(this);
	QStandardItemModel* rolesListModel = new QStandardItemModel;
	QSqlQuery qry;
	QSqlQuery getRoleId;
	int rolId = 0;
	int infoSystemServiceId = 0;
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
		qry.prepare("INSERT INTO InfoSystemServicesRoles(information_service_id, rol_id) VALUES (:information_service_id, :rol_id)");

		getRoleId.exec(QString("SELECT rol_id FROM Roles WHERE name = '%1'").arg(element));
		while(getRoleId.next())
			rolId = getRoleId.value(0).toInt();
        
		infoSystemServiceId = infoSystemServicesTable->model()->index(infoSystemServicesTable->selectionModel()->currentIndex().row(),0).data().toInt();

		qry.bindValue(":rol_id", rolId);
		qry.bindValue(":information_service_id", infoSystemServiceId);

		if (!qry.exec())
			qDebug()<<qry.lastError();
	} 
}


void InfoSystemServicesRolesMatrix::delInfoSystemServicesRolesRelation()
{
	
	QSqlQuery qry;
	QSqlQuery getRoleId;   //takes the processId of the element
	//takes the clicked element in the rolesList listview
	QString element = rolesList->model()->index(rolesList->selectionModel()->currentIndex().row(),0).data().toString();
	//takes the clicked function_id of the rolesTable
	QString infoSystemServiceId = infoSystemServicesTable->model()->index(infoSystemServicesTable->selectionModel()->currentIndex().row(),0).data().toString();
	int rolId = 0;
	QStandardItemModel* rolesListModel = new QStandardItemModel;
	int row = 0;  // to count the processesListModel rows
	int newModelrows = 0; //to puts element in the right place in the processListModel
	QString currentListElement;

	qry.prepare("DELETE FROM InfoSystemServicesRoles WHERE rol_id = :rol_id AND information_service_id = :information_service_id");

	//get the role_id value
	getRoleId.exec(QString("SELECT rol_id FROM Roles WHERE name = '%1'").arg(element));
	while(getRoleId.next())
		rolId = getRoleId.value(0).toInt();
	
	qry.bindValue(":rol_id", rolId);
	qry.bindValue(":information_service_id", infoSystemServiceId);
	
	qDebug()<<rolId;
	qDebug()<<infoSystemServiceId;
		
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
