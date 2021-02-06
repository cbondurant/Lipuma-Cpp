#include "drawable/editPoint.hpp"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>

namespace Lipuma {
	EditPoint::EditPoint() : _isTracking(false){ setFlag(ItemIgnoresTransformations); }
	
	void EditPoint::mousePressEvent(QGraphicsSceneMouseEvent */* e */){
		_isTracking = true;
	}

	void EditPoint::mouseMoveEvent(QGraphicsSceneMouseEvent *e){
		if (_isTracking){
			emit pointMoved(e->scenePos());
		}
	}

	void EditPoint::mouseReleaseEvent(QGraphicsSceneMouseEvent */* e */){
		_isTracking = false;
	}
	//*/
	QRectF EditPoint::boundingRect() const {
		return QRectF(-5,-5,10,10);
	}

	void EditPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem */* Option */, QWidget */* widget */){
		painter->setBrush(QBrush(Qt::white));
		painter->drawRect(-5,-5,10,10);
	}

}