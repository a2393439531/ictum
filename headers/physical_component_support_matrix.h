#ifndef PHYSICAL_COMPONENT_SUPPORT_MATRIX_H
#define PHYSICAL_COMPONENT_SUPPORT_MATRIX_H

#include <QDialog>

class QListView;
class QTableView;
//class QStandardItemModel;

class PhysicalComponentSupportMatrix : public QDialog
{
 Q_OBJECT
 
 public:
	PhysicalComponentSupportMatrix(QWidget* parent = 0);
	private slots:
		void addSupportRelation();
		void delSupportRelationElement();
		void revealPhysicalComponents(const QModelIndex&);

 private:
	QListView* physicalComponentsList;
	QTableView* physicalComponentTable;
	//QStandardItemModel* ListModel;
};
#endif
