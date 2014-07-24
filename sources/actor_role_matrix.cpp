#include "../headers/actor_role_matrix.h"
#include <QTableView>
#include <QVBoxLayout>
#include <QtSql>
#include <QDebug>
#include <QDialogButtonBox>
#include <QHeaderView>
ActorRoleMatrix::ActorRoleMatrix(QWidget* parent) : QDialog(parent)
{
	QVBoxLayout* mainlayout = new QVBoxLayout;
	ActorRoleMatrixTable = new QTableView;
	
	QSqlQueryModel* roleActorMatrixModel = new QSqlQueryModel();
	roleActorMatrixModel->setQuery("SELECT name as Nombre, lastName as Apellido, (SELECT name as Rol FROM Roles WHERE Roles.rol_id = Actors.rol_id) AS Role FROM Actors");
    ActorRoleMatrixTable->verticalHeader()->setVisible(false);
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
