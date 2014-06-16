#ifndef INFO_SYTEM_SERVICES_ROLES_MATRIX_H
#define INFO_SYTEM_SERVICES_ROLES_MATRIX_H

#include <QDialog>

class QListView;
class QTableView;
class QStandardItemModel;

class InfoSystemServicesRolesMatrix : public QDialog
{
    Q_OBJECT

    public:
        InfoSystemServicesRolesMatrix(QWidget* parent = 0);

    public slots:
        void addInfoSystemServicesRolesRelation();
        void delInfoSystemServicesRolesRelation();
        void revealRoles(const QModelIndex& index);

     private:
	    QListView* rolesList;
	    QTableView* infoSystemServicesTable;
	    QStandardItemModel* rolesListModel;
};
#endif

