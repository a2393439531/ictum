#ifndef OU_FUNCTION_MATRIX_H
#define OU_FUNCTION_MATRIX_H

#include <QDialog>

class QListView;
class QTableView;
class QStandardItemModel;

class OuFunctionMatrix : public QDialog
{
 Q_OBJECT
 
 public:
	OuFunctionMatrix(QWidget* parent = 0);
	private slots:
	void revealFunctions(const QModelIndex&);

 private:
	QListView* functionsList;
	QTableView* ouTable;
	QStandardItemModel* functionListModel;
};
#endif
