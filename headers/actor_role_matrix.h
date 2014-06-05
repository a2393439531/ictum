#ifndef ACTOR_ROLE_MATRIX_H
#define ACTOR_ROLE_MATRIX_H

#include <QDialog>

class QTableView;

class ActorRoleMatrix : public QDialog
{
 public:
	ActorRoleMatrix(QWidget* parent = 0);
 private:
	QTableView* ActorRoleMatrixTable;
};
#endif
