#include "../headers/actor_function_matrix.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListView>
#include <QTableView>
#include <QtSql>
#include <QStandardItemModel>
#include <QDialogButtonBox>

ActorFunctionMatrix::ActorFunctionMatrix(QWidget* parent) : QDialog(parent)
{
	QVBoxLayout* mainlayout = new QVBoxLayout;
	QHBoxLayout* tableListLayout = new QHBoxLayout;

	actorsTable = new QTableView;
	functionsList = new QListView;
	functionListModel = new QStandardItemModel;
	
	//search for functions Names
	QSqlQueryModel* actorQueryModel = new QSqlQueryModel;
	actorQueryModel->setQuery("SELECT rol_id, name, lastName FROM Actors");

	actorsTable->setSelectionBehavior(QAbstractItemView::SelectRows);   //selects entires rows	
	actorsTable->setSelectionMode(QAbstractItemView::SingleSelection);  //two rows can't be selected at the same time
	actorsTable->setModel(actorQueryModel);

	QDialogButtonBox* actorFunctionMatrixButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox:: Cancel);

	tableListLayout->addWidget(actorsTable);
	tableListLayout->addStretch();
	tableListLayout->addWidget(functionsList);
	tableListLayout->addStretch();
	mainlayout->addLayout(tableListLayout);
	mainlayout->addStretch();
	mainlayout->addWidget(actorFunctionMatrixButtonBox);
	
	this->setLayout(mainlayout);

	connect(actorsTable, SIGNAL(clicked(const QModelIndex&)),
			this, SLOT(revealFunctions(const QModelIndex&)));
	connect(actorFunctionMatrixButtonBox, SIGNAL(accepted()),
			this,SLOT(accept()));
	connect(actorFunctionMatrixButtonBox, SIGNAL(rejected()),
			this,SLOT(reject()));


}

void ActorFunctionMatrix::revealFunctions(const QModelIndex& index)
{
	QSqlQueryModel* functionListQuery = new QSqlQueryModel();
	QString currentRolId;

	currentRolId = actorsTable->model()->index(index.row(),0).data().toString();
	functionListQuery->setQuery(QString("SELECT Functions.name AS Function FROM RolesFunctions INNER JOIN Functions ON Functions.function_id = RolesFunctions.function_id INNER JOIN Actors WHERE RolesFunctions.rol_id = %1 GROUP BY Function;").arg(currentRolId));
		
	functionsList->setModel(functionListQuery);
}
