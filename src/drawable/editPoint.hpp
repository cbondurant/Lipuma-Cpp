#ifndef DRAWABLE_EDIT_POINT_HPP
#define DRAWABLE_EDIT_POINT_HPP

#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>

namespace Lipuma
{
	class EditPoint : public QGraphicsObject
	{

		Q_OBJECT

	public:
		EditPoint();
		void mousePressEvent(QGraphicsSceneMouseEvent *e) override;
		void mouseMoveEvent(QGraphicsSceneMouseEvent *e) override;
		void mouseReleaseEvent(QGraphicsSceneMouseEvent *e) override;

		QRectF boundingRect() const override;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

	signals:
		// Emits when the point is selected and dragged
		void pointMoved(QPointF);

	private:
		bool _isTracking;
	};
}

#endif