#ifndef INFO_SYSTEM_SERVICES_NAVIGATION_H
#define INFO_SYSTEM_SERVICES_NAVIGATION_H

#include <QWidget>

class QPushButton;
class QGridLayout;
class QTableView;
class QListView;
class QTextEdit;
class QLineEdit;
class QPushButton;

class InformationSystemServicesNavigation : public QWidget 
{
    Q_OBJECT

    public:
        InformationSystemServicesNavigation(QWidget* parent = 0);

    private slots:
		void informationSystemService(const QModelIndex& index);     // Display informaytion about the related entities
		void showInformationSystemServiceElementInfo(const QModelIndex& index);  // shows information of a clicked element
        void informationSystemServiceSearch(const QString& text);           //Enable the search by Data Entities
    private:
        QGridLayout* dataViewLayout;
        QTableView* currentAnalyzedEntityTable; 
        QListView* releatedEntityInformationListView;    
		QListView* relatedEntitiesListView;
		QTextEdit* elementDescriptionTextEdit;
		QTextEdit* descriptionTextEdit;
};

#endif
