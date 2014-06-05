#ifndef ACTOR_PROCESS_MATRIX_H
#define ACTOR_ROLE_MATRIX_H

#include <QDialog>

class QListView;
class QTableView;

class ActorProcessMatrix : public QDialog
{
 Q_OBJECT
 
 public:
	ActorProcessMatrix(QWidget* parent = 0);
	private slots:
		void revealProcesses(const QModelIndex&);

 private:
	QListView* processesList;
	QTableView* actorsTable;
};
#endif
