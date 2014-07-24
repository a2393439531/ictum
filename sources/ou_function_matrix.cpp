#include "../headers/ou_function_matrix.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListView>
#include <QTableView>
#include <QtSql>
#include <QStandardItemModel>
#include <QDialogButtonBox>
#include <QHeaderView>
OuFunctionMatrix::OuFunctionMatrix(QWidget* parent) : QDialog(parent)
{
	QVBoxLayout* mainlayout = new QVBoxLayout;
	QHBoxLayout* tableListLayout = new QHBoxLayout;

	ouTable = new QTableView;
	functionsList = new QListView;
	functionListModel = new QStandardItemModel;
	
	//search for functions Names
	QSqlQueryModel* ouQueryModel = new QSqlQueryModel;
	ouQueryModel->setQuery("SELECT ou_id as ID, name as Nombre FROM OrganizationalUnits");

    ouTable->verticalHeader()->setVisible(false);
	ouTable->setSelectionBehavior(QAbstractItemView::SelectRows);   //selects entires rows	
	ouTable->setSelectionMode(QAbstractItemView::SingleSelection);  //two rows can't be selected at the same time
	ouTable->setModel(ouQueryModel);

	QDialogButtonBox* ouFunctionMatrixButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox:: Cancel);

	tableListLayout->addWidget(ouTable);
	tableListLayout->addStretch();
	tableListLayout->addWidget(functionsList);
	tableListLayout->addStretch();
	mainlayout->addLayout(tableListLayout);
	mainlayout->addStretch();
	mainlayout->addWidget(ouFunctionMatrixButtonBox);
	
	this->setLayout(mainlayout);

	connect(ouTable, SIGNAL(clicked(const QModelIndex&)),
			this, SLOT(revealFunctions(const QModelIndex&)));
	connect(ouFunctionMatrixButtonBox, SIGNAL(accepted()),
			this,SLOT(accept()));
	connect(ouFunctionMatrixButtonBox, SIGNAL(rejected()),
			this,SLOT(reject()));


}

void OuFunctionMatrix::revealFunctions(const QModelIndex& index)
{
	QSqlQueryModel* functionListQuery = new QSqlQueryModel();
	QString currentOuId;

	currentOuId = ouTable->model()->index(index.row(),0).data().toString();
	functionListQuery->setQuery(QString("SELECT Functions.name FROM OrganizationalUnits JOIN Actors ON OrganizationalUnits.ou_id = Actors.ou_id JOIN RolesFunctions ON Actors.rol_id = RolesFunctions.rol_id JOIN Functions ON RolesFunctions.function_id = Functions.function_id WHERE OrganizationalUnits.ou_id = %1 GROUP BY Functions.name").arg(currentOuId));
		
	functionsList->setModel(functionListQuery);
}
