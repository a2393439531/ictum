#ifndef PHYSICAL_COMPONENT_ROLES_MATRIX_H
#define PHYSICAL_COMPONENT_ROLES_MATRIX_H

#include <QDialog>

class QListView;
class QTableView;
class QStandardItemModel;

class PhysicalComponentRolesMatrix : public QDialog
{
    Q_OBJECT

    public:
        PhysicalComponentRolesMatrix(QWidget* parent = 0);

    public slots:
        void addPhysicalComponentRolesRelation();
        void delPhysicalComponentRolesRelation();
        void revealRoles(const QModelIndex& index);

     private:
	    QListView* rolesList;
	    QTableView* physicalComponentsTable;
	    QStandardItemModel* rolesListModel;
};
#endif
