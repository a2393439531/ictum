#ifndef CHECKBOX_DELEGTE_H
#define CHECKBOX_DELEGTE_H

#include <QAbstractItemDelegate>
#include<QObject>

class CheckBoxDelegate : public QAbstractItemDelegate
{
 public:
	CheckBoxDelegate(QObject* parent=0);
	void paint(QPainter* painter, const QStyleOptionViewItem &option,
			   const QModelIndex &index) const;
	bool editorEvent(QEvent* event, QAbstractItemModel *model,
					 const QStyleOptionViewItem &option,
					 const QModelIndex &index);
	QSize sizeHint(const QStyleOptionViewItem &option,
				   const QModelIndex &index) const;
};
#endif
