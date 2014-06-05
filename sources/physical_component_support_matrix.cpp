#include "../headers/physical_component_support_matrix.h"
#include "../headers/add_physical_component_helper_dialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListView>
#include <QTableView>
#include <QtSql>
#include <QPushButton>
#include <QStandardItemModel>

PhysicalComponentSupportMatrix::PhysicalComponentSupportMatrix(QWidget* parent) : QDialog(parent)
{
	QVBoxLayout* mainlayout = new QVBoxLayout;
	QHBoxLayout* tableListLayout = new QHBoxLayout;
	QHBoxLayout* buttonsLayout = new QHBoxLayout;

	physicalComponentTable = new QTableView;
	physicalComponentsList = new QListView;
	QPushButton* add = new QPushButton("agregar");
	QPushButton* edit = new QPushButton("Editar");
	QPushButton* del = new QPushButton("Eliminar"); 
	//iSSListModel = new QStandardItemModel;
	
	//search for functions Names
	QSqlQueryModel* physicalComponentQueryModel = new QSqlQueryModel;
	physicalComponentQueryModel->setQuery("SELECT physical_technology_component_id, name FROM PhysicalTechnologiesComponents");

	physicalComponentTable->setSelectionBehavior(QAbstractItemView::SelectRows);   //selects entires rows	
	physicalComponentTable->setSelectionMode(QAbstractItemView::SingleSelection);  //two rows can't be selected at the same time
	physicalComponentTable->setModel(physicalComponentQueryModel);

	tableListLayout->addWidget(physicalComponentTable);
	tableListLayout->addStretch();
	tableListLayout->addWidget(physicalComponentsList);
	buttonsLayout->addWidget(add);
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(edit);
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(del);
	mainlayout->addLayout(tableListLayout);
	mainlayout->addStretch();
	mainlayout->addLayout(buttonsLayout);

	this->setLayout(mainlayout);

	connect(physicalComponentTable, SIGNAL(clicked(const QModelIndex&)),
			this, SLOT(revealPhysicalComponents(const QModelIndex&)));
	connect(add, SIGNAL(clicked()),
			this, SLOT(addSupportRelation()));
	connect(del, SIGNAL(clicked()),
			this, SLOT(delSupportRelationElement()));


}

void PhysicalComponentSupportMatrix::revealPhysicalComponents(const QModelIndex& index)
{
	QSqlQueryModel* physicalComponentListQuery = new QSqlQueryModel();
	QString currentPhysicalComponentId;

	currentPhysicalComponentId = physicalComponentTable->model()->index(index.row(),0).data().toString();
	physicalComponentListQuery->setQuery(QString("SELECT name AS Tech FROM PhysicalComponentsSupport INNER JOIN PhysicalTechnologiesComponents ON PhysicalTechnologiesComponents.physical_technology_component_id = PhysicalComponentsSupport.support WHERE PhysicalComponentsSupport.physical_technology_component_id = %1 GROUP BY name").arg(currentPhysicalComponentId));
		
	physicalComponentsList->setModel(physicalComponentListQuery);
}

void PhysicalComponentSupportMatrix::addSupportRelation()
{
	AddPhysicalComponentHelperDialog* dlgHelper = new AddPhysicalComponentHelperDialog(this);
	QStandardItemModel* selectedPhysicalComponentModel = new QStandardItemModel;
	QSqlQuery qry;
	QSqlQuery getPhysicalComponentId;
	QList<QString> currentElementsInTheList;
	QList<QString> newSelectedElements;
	QList<QString> newListElements;
	int currentElementsInTheListRow = 0;
	int row = 0;  // the row of the model
	int physicalComponentId = 0;
	int physicalComponentInTableId = 0;  
	
	if (dlgHelper->exec()==QDialog::Accepted){

		// takes all the elements of the list view
		while(physicalComponentsList->model()->index(currentElementsInTheListRow,0).isValid())
			currentElementsInTheList << physicalComponentsList->model()->index(currentElementsInTheListRow++,0).data().toString();
		
		currentElementsInTheListRow = 0; //clean the physicalComponentsList listview counter of latter use
		
		//takes all the new elemets selected from the dlgHelper Dialog 
		foreach(QModelIndex itemIndex, dlgHelper->physicalComponentsList->selectionModel()->selectedIndexes()){
			newSelectedElements << dlgHelper->physicalComponentsList->model()->index(itemIndex.row(), itemIndex.column()).data().toString();
		}

		//to not repeat elements in the list
		foreach(QString element, newSelectedElements){
			if (currentElementsInTheList.indexOf(element) == -1) //if indexOf Returns -1 the element was not in the list of current elements
				currentElementsInTheList << element;
		}
		
		//adds the elements in the list view model
		foreach(QString element, currentElementsInTheList){
			QStandardItem* i = new QStandardItem(element);
			selectedPhysicalComponentModel->setItem(row++,0,i);
		}
		physicalComponentsList->setModel(selectedPhysicalComponentModel); //display the elements in the list 

		//adds the elements in the database
		foreach(QString element, currentElementsInTheList){
		qry.prepare("INSERT INTO PhysicalComponentsSupport (physical_technology_component_id, support) VALUES (:physical_technology_component_id, :support)");
		
		getPhysicalComponentId.exec(QString("SELECT physical_technology_component_id FROM PhysicalTechnologiesComponents WHERE name = '%1'").arg(element));
		while(getPhysicalComponentId.next())
			physicalComponentId = getPhysicalComponentId.value(0).toInt();

		qDebug()<<physicalComponentId;
		//takes the role id form the physicalComponentTable (the table in the dialog)
		physicalComponentInTableId = physicalComponentTable->model()->index(physicalComponentTable->selectionModel()->currentIndex().row(),0).data().toInt();
		qry.bindValue(":physical_technology_component_id", physicalComponentInTableId);
		qry.bindValue(":support", physicalComponentId);

		if (!qry.exec())
			qDebug()<<qry.lastError();
		}	
		
	}
}


void PhysicalComponentSupportMatrix::delSupportRelationElement()
{
	QSqlQuery qry;
	QSqlQuery getPhysicalComponentId;   //takes the processId of the element
	//takes the clicked element in the iSSList listview
	QString element = physicalComponentsList->model()->index(physicalComponentsList->selectionModel()->currentIndex().row(),0).data().toString();
	//takes the clicked rol_id of the physicalComponentTable
	QString physicalComponentInTableId = physicalComponentTable->model()->index(physicalComponentTable->selectionModel()->currentIndex().row(),0).data().toString();
	int physicalComponentId = 0;
	QStandardItemModel* physicalComponentListModel = new QStandardItemModel;
	int row = 0;  // to count the iSSListModel rows
	int newModelrows = 0; //to puts element in the right place in the iSSListModel
	QString currentListElement;

	qry.prepare("DELETE FROM PhysicalComponentsSupport WHERE physical_technology_component_id = :physical_technology_component_id AND support = :support");

	//get the process_id value
	getPhysicalComponentId.exec(QString("SELECT physical_technology_component_id FROM PhysicalTechnologiesComponents WHERE name = '%1'").arg(element));
	while(getPhysicalComponentId.next())
		physicalComponentId = getPhysicalComponentId.value(0).toInt();

	qry.bindValue(":physical_technology_component_id", physicalComponentInTableId);
	qry.bindValue(":support", physicalComponentId);

	if(!qry.exec())
		qDebug()<<qry.lastError();
	
	//adds valid elements to the model
	while(physicalComponentsList->model()->index(row,0).isValid()){
		currentListElement = physicalComponentsList->model()->index(row++,0).data().toString();
		if(currentListElement != element){
			QStandardItem* i = new QStandardItem(currentListElement);
			physicalComponentListModel->setItem(newModelrows++,0,i);
		}
	}
	physicalComponentsList->setModel(physicalComponentListModel);    //show modifications in the list view
}
