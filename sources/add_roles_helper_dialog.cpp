#include "../headers/add_roles_helper_dialog.h"
#include <QListView>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QtSql>

AddRolesHelperDialog::AddRolesHelperDialog(QWidget* parent) : QDialog(parent)
{
	QHBoxLayout* mainlayout = new QHBoxLayout(this);
	//create dialog widgets
	rolesList = new QListView;
	QDialogButtonBox* roleshelperDialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
	roleshelperDialogButtonBox->setOrientation(Qt::Vertical);
 
	QSqlQueryModel* roleListQueryModel = new QSqlQueryModel();
	roleListQueryModel->setQuery("SELECT name FROM Roles");
	rolesList->setSelectionMode(QAbstractItemView::MultiSelection);
	rolesList->setSelectionBehavior(QAbstractItemView::SelectRows);
	rolesList->setModel(roleListQueryModel);
	
	mainlayout->addWidget(rolesList);
	mainlayout->addStretch();
	mainlayout->addWidget(roleshelperDialogButtonBox);

	connect(roleshelperDialogButtonBox, SIGNAL(accepted()),
			this, SLOT(accept()));
	connect(roleshelperDialogButtonBox, SIGNAL(rejected()),
			this, SLOT(reject()));
}
