#ifndef PHYSICAL_TECH_COMPONENT_H
#define PHYSICAL_TECH_COMPONENT_H

#include <QWidget>

class QPushButton;
class QGridLayout;
class QTableView;
class QListView;
class QTextEdit;
class QLineEdit;
class QPushButton;

class PhysicalTechComponentNavigation : public QWidget 
{
    Q_OBJECT

    public:
        PhysicalTechComponentNavigation(QWidget* parent = 0);

    private slots:
		void physicalTechComponents(const QModelIndex& index);     // Display informaytion about the related entities
		void showPhysicalTechComponentsElementInfo(const QModelIndex& index);  // shows information of a clicked element
        void physicalTechComponentSearch(const QString& text);           //Enable the search
    private:
        QGridLayout* dataViewLayout;
        QTableView* currentAnalyzedEntityTable; 
        QListView* releatedEntityInformationListView;    
		QListView* relatedEntitiesListView;
		QTextEdit* elementDescriptionTextEdit;
		QTextEdit* descriptionTextEdit;
};
#endif
