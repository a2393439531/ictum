#ifndef ROLES_DATA_ENTITY_H
#define ROLES_DATA_ENTITY_H

#include <QDialog>

class QListView;
class QTableView;
class QStandardItemModel;

class DataEntityRolesMatrix : public QDialog
{
    Q_OBJECT

    public:
        DataEntityRolesMatrix(QWidget* parent = 0);

    public slots:
        void addDataEntityRolesRelation();
        void delDataEntityRolesRelation();
        void revealRoles(const QModelIndex& index);

     private:
	    QListView* rolesList;
	    QTableView* dataEntityTable;
	    QStandardItemModel* rolesListModel;
};
#endif
