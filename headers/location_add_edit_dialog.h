#ifndef LOCATION_ADD_EDIT_DIALOG_H
#define LOCATION_ADD_EDIT_DIALOG_H

#include <QDialog>

class QTextEdit;

class LocationAddEditDialog : public QDialog
{
 public:
	LocationAddEditDialog(QWidget* parent = 0);	
	const QString location() const;
	void setLocation(const QString&);
 private:
	QTextEdit* locationTextEdit;
};
#endif
