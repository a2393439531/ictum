#ifndef OU_NAVIGATION_H
#define OU_NAVIGATION_H

#include <QWidget>

class QVBoxLayout;
class QPushButton;
class QGridLayout;
class QTableView;
class QListView;
class QTextEdit;
class QLineEdit;
class QPushButton;
class QString;

class OuNavigation : public QWidget 
{
    Q_OBJECT

    public:
        OuNavigation(QWidget* parent = 0);

    private slots:
		void oUEntities(const QModelIndex& index);     // Display informaytion about the roles related entities
		void showOuEntitiesElementInfo(const QModelIndex& index);  // shows information of a clicked element
        void oUSearch(const QString& text);           //Enable the search by roles
    private:
        QGridLayout* dataViewLayout;
        QTableView* currentAnalyzedEntityTable; 
        QListView* releatedEntityInformationListView;    
		QListView* relatedEntitiesListView;
		QTextEdit* elementDescriptionTextEdit;
		QTextEdit* descriptionTextEdit;
};
#endif
