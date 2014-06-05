#include "../headers/info_system_service_support_matrix.h"
#include "../headers/add_iss_helper_dialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListView>
#include <QTableView>
#include <QtSql>
#include <QPushButton>
#include <QStandardItemModel>

InfoSystemServiceSupportMatrix::InfoSystemServiceSupportMatrix(QWidget* parent) : QDialog(parent)
{
	QVBoxLayout* mainlayout = new QVBoxLayout;
	QHBoxLayout* tableListLayout = new QHBoxLayout;
	QHBoxLayout* buttonsLayout = new QHBoxLayout;

	iSSTable = new QTableView;
	iSSList = new QListView;
	QPushButton* add = new QPushButton("agregar");
	QPushButton* edit = new QPushButton("Editar");
	QPushButton* del = new QPushButton("Eliminar"); 
	iSSListModel = new QStandardItemModel;
	
	//search for functions Names
	QSqlQueryModel* iSSQueryModel = new QSqlQueryModel;
	iSSQueryModel->setQuery("SELECT information_service_id, name FROM InformationSystemServices");

	iSSTable->setSelectionBehavior(QAbstractItemView::SelectRows);   //selects entires rows	
	iSSTable->setSelectionMode(QAbstractItemView::SingleSelection);  //two rows can't be selected at the same time
	iSSTable->setModel(iSSQueryModel);

	tableListLayout->addWidget(iSSTable);
	tableListLayout->addStretch();
	tableListLayout->addWidget(iSSList);
	buttonsLayout->addWidget(add);
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(edit);
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(del);
	mainlayout->addLayout(tableListLayout);
	mainlayout->addStretch();
	mainlayout->addLayout(buttonsLayout);

	this->setLayout(mainlayout);

	connect(iSSTable, SIGNAL(clicked(const QModelIndex&)),
			this, SLOT(revealISS(const QModelIndex&)));
	connect(add, SIGNAL(clicked()),
			this, SLOT(addSupportRelation()));
	connect(del, SIGNAL(clicked()),
			this, SLOT(delSupportRelationElement()));


}

void InfoSystemServiceSupportMatrix::revealISS(const QModelIndex& index)
{
	QSqlQueryModel* iSSListQuery = new QSqlQueryModel();
	QString currentISSId;

	currentISSId = iSSTable->model()->index(index.row(),0).data().toString();
	iSSListQuery->setQuery(QString("SELECT name AS ISS FROM IssSupport INNER JOIN InformationSystemServices ON InformationSystemServices.information_service_id = IssSupport.support WHERE IssSupport.information_service_id = %1 GROUP BY name").arg(currentISSId));
		
	iSSList->setModel(iSSListQuery);
}

void InfoSystemServiceSupportMatrix::addSupportRelation()
{
	AddISSHelperDialog* dlgHelper = new AddISSHelperDialog(this);
	QStandardItemModel* selectedISSModel = new QStandardItemModel;
	QSqlQuery qry;
	QSqlQuery getISSId;
	QList<QString> currentElementsInTheList;
	QList<QString> newSelectedElements;
	QList<QString> newListElements;
	int currentElementsInTheListRow = 0;
	int row = 0;  // the row of the model
	int iSSId = 0;
	int iSSInTableId = 0;  
	
	if (dlgHelper->exec()==QDialog::Accepted){

		// takes all the elements of the list view
		while(iSSList->model()->index(currentElementsInTheListRow,0).isValid())
			currentElementsInTheList << iSSList->model()->index(currentElementsInTheListRow++,0).data().toString();
		
		currentElementsInTheListRow = 0; //clean the iSSList listview counter of latter use
		
		//takes all the new elemets selected from the dlgHelper Dialog 
		foreach(QModelIndex itemIndex, dlgHelper->iSSList->selectionModel()->selectedIndexes()){
			newSelectedElements << dlgHelper->iSSList->model()->index(itemIndex.row(), itemIndex.column()).data().toString();
		}

		//to not repeat elements in the list
		foreach(QString element, newSelectedElements){
			if (currentElementsInTheList.indexOf(element) == -1) //if indexOf Returns -1 the element was not in the list of current elements
				currentElementsInTheList << element;
		}
		
		//adds the elements in the list view model
		foreach(QString element, currentElementsInTheList){
			QStandardItem* i = new QStandardItem(element);
			selectedISSModel->setItem(row++,0,i);
		}
		iSSList->setModel(selectedISSModel); //display the elements in the list 

		//adds the elements in the database
		foreach(QString element, currentElementsInTheList){
		qry.prepare("INSERT INTO IssSupport (information_service_id, support) VALUES (:information_service_id, :support)");
		
		getISSId.exec(QString("SELECT information_service_id FROM InformationSystemServices WHERE name = '%1'").arg(element));
		while(getISSId.next())
			iSSId = getISSId.value(0).toInt();

		qDebug()<<iSSId;
		//takes the role id form the iSSTable (the table in the dialog)
		iSSInTableId = iSSTable->model()->index(iSSTable->selectionModel()->currentIndex().row(),0).data().toInt();
		qry.bindValue(":information_service_id", iSSInTableId);
		qry.bindValue(":support", iSSId);

		if (!qry.exec())
			qDebug()<<qry.lastError();
		}	
		
	}
}


void InfoSystemServiceSupportMatrix::delSupportRelationElement()
{
	QSqlQuery qry;
	QSqlQuery getISSId;   //takes the processId of the element
	//takes the clicked element in the iSSList listview
	QString element = iSSList->model()->index(iSSList->selectionModel()->currentIndex().row(),0).data().toString();
	//takes the clicked rol_id of the iSSTable
	QString iSSInTableId = iSSTable->model()->index(iSSTable->selectionModel()->currentIndex().row(),0).data().toString();
	int iSSId = 0;
	QStandardItemModel* iSSListModel = new QStandardItemModel;
	int row = 0;  // to count the iSSListModel rows
	int newModelrows = 0; //to puts element in the right place in the iSSListModel
	QString currentListElement;

	qry.prepare("DELETE FROM IssSupport WHERE information_service_id = :information_service_id AND support = :support");

	//get the process_id value
	getISSId.exec(QString("SELECT information_service_id FROM InformationSystemServices WHERE name = '%1'").arg(element));
	while(getISSId.next())
		iSSId = getISSId.value(0).toInt();

	qry.bindValue(":information_service_id", iSSInTableId);
	qry.bindValue(":support", iSSId);

	if(!qry.exec())
	  qDebug()<<qry.lastError();
	
	//adds valid elements to the model
	while(iSSList->model()->index(row,0).isValid()){
		currentListElement = iSSList->model()->index(row++,0).data().toString();
		if(currentListElement != element){
			QStandardItem* i = new QStandardItem(currentListElement);
			iSSListModel->setItem(newModelrows++,0,i);
		}
	}
	iSSList->setModel(iSSListModel);    //show modifications in the list view
}
