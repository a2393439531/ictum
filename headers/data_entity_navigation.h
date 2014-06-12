#ifndef DATA_ENTITY_NAVIGATION_H
#define DATA_ENTITY_NAVIGATION_H

#include <QWidget>

class QPushButton;
class QGridLayout;
class QTableView;
class QListView;
class QTextEdit;
class QLineEdit;
class QPushButton;

class DataEntityNavigation : public QWidget 
{
    Q_OBJECT

    public:
        DataEntityNavigation(QWidget* parent = 0);

    private slots:
		void dataEntities(const QModelIndex& index);     // Display informaytion about the related entities
		void showDataEntitiesElementInfo(const QModelIndex& index);  // shows information of a clicked element
        void dataEntitySearch(const QString& text);           //Enable the search by Data Entities
    private:
        QGridLayout* dataViewLayout;
        QTableView* currentAnalyzedEntityTable; 
        QListView* releatedEntityInformationListView;    
		QListView* relatedEntitiesListView;
		QTextEdit* elementDescriptionTextEdit;
		QTextEdit* descriptionTextEdit;
};
#endif

