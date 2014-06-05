#ifndef ACTOR_OU_MATRIX_H
#define ACTOR_OU_MATRIX_H

#include <QDialog>

class QTableView;

class ActorOuMatrix : public QDialog
{
 public:
	ActorOuMatrix(QWidget* parent = 0);
 private:
	QTableView* ActorOuMatrixTable;
};
#endif
