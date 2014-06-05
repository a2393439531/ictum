#ifndef ACTOR_FUNCTION_MATRIX_H
#define ACTOR_FUNCTION_MATRIX_H

#include <QDialog>

class QListView;
class QTableView;
class QStandardItemModel;

class ActorFunctionMatrix : public QDialog
{
 Q_OBJECT
 
 public:
	ActorFunctionMatrix(QWidget* parent = 0);
	private slots:
	void revealFunctions(const QModelIndex&);

 private:
	QListView* functionsList;
	QTableView* actorsTable;
	QStandardItemModel* functionListModel;
};
#endif
