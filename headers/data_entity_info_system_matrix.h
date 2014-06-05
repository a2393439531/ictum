#ifndef DATA_ENTITY_INFO_SYSTEM_MATRIX_H
#define DATA_ENTITY_INFO_SYSTEM_MATRIX_H

#include <QDialog>
								
class QTableView;

class DataEntityInfoSystemMatrix : public QDialog
{
 public:
	DataEntityInfoSystemMatrix(QWidget* parent = 0);
 private:
	QTableView* DataEntityInfoSystemMatrixTable;
};
#endif
