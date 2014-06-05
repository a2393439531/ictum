#ifndef ACTOR_H
#define ACTOR_H

#include <QDialog>

class QStandardItemModel;
class QTableView;

class Actor : public QDialog
{
	Q_OBJECT
 public:
	Actor(QWidget* parent = 0);
	void refreshActorTable();
	
	private slots:
		void addActor();
		void editActor();

 private:
		QTableView* table;
};
#endif
