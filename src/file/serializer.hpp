#ifndef FILE_SERIALIZER_HPP
#define FILE_SERIALIZER_HPP

#include <QString>
#include <QGraphicsScene>

namespace Lipuma {
	void SerializeScene(QGraphicsScene*, QString&);
	QGraphicsScene* LoadScene(QString&);
}

#endif