#include "../headers/actor_role_matrix.h"
#include <QTableView>
#include <QVBoxLayout>
#include <QtSql>
#include <QDebug>
#include <QDialogButtonBox>

ActorRoleMatrix::ActorRoleMatrix(QWidget* parent) : QDialog(parent)
{
	QVBoxLayout* mainlayout = new QVBoxLayout;
	ActorRoleMatrixTable = new QTableView;
	
	QSqlQueryModel* roleActorMatrixModel = new QSqlQueryModel();
	roleActorMatrixModel->setQuery("SELECT name, lastName, (SELECT name FROM Roles WHERE Roles.rol_id = Actors.rol_id) AS Role FROM Actors");
	ActorRoleMatrixTable->setModel(roleActorMatrixModel);
	
	QDialogButtonBox* actorRoleMatrixButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
	

	mainlayout->addWidget(ActorRoleMatrixTable);
	mainlayout->addWidget(actorRoleMatrixButtonBox);
	this->setLayout(mainlayout);

	connect(actorRoleMatrixButtonBox, SIGNAL(accepted()),
			this,SLOT(accept()));
	connect(actorRoleMatrixButtonBox, SIGNAL(rejected()),
			this,SLOT(reject()));

	
}
