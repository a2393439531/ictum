#include "../headers/actor_process_matrix.h"
#include "../headers/add_processes_helper_dialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListView>
#include <QTableView>
#include <QtSql>


ActorProcessMatrix::ActorProcessMatrix(QWidget* parent) : QDialog(parent)
{
	QVBoxLayout* mainlayout = new QVBoxLayout;
	QHBoxLayout* tableListLayout = new QHBoxLayout;

	actorsTable = new QTableView;
	processesList = new QListView;
	
	//search for functions Names
	QSqlQueryModel* actorsQueryModel = new QSqlQueryModel;
	actorsQueryModel->setQuery("SELECT rol_id As Id, name, lastName FROM Actors");

	actorsTable->setSelectionBehavior(QAbstractItemView::SelectRows);   //selects entires rows	
	actorsTable->setSelectionMode(QAbstractItemView::SingleSelection);  //two rows can't be selected at the same time
	actorsTable->setModel(actorsQueryModel);

	tableListLayout->addWidget(actorsTable);
	tableListLayout->addStretch();
	tableListLayout->addWidget(processesList);
	mainlayout->addLayout(tableListLayout);
	mainlayout->addStretch();

	this->setLayout(mainlayout);

	connect(actorsTable, SIGNAL(clicked(const QModelIndex&)),
			this, SLOT(revealProcesses(const QModelIndex&)));
}

void ActorProcessMatrix::revealProcesses(const QModelIndex& index)
{
	QSqlQueryModel* processesListQuery = new QSqlQueryModel();
	QString currentActorRolId;

	currentActorRolId = actorsTable->model()->index(index.row(),0).data().toString();
	processesListQuery->setQuery(QString("SELECT Processes.name FROM RolesProcesses JOIN Processes ON Processes.process_id = RolesProcesses.process_id JOIN Actors ON Actors.rol_id = RolesProcesses.rol_id WHERE RolesProcesses.rol_id = %1 GROUP BY Processes.name").arg(currentActorRolId));
		
	processesList->setModel(processesListQuery);
}
