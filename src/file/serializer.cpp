#include <QString>
#include <QFile>

#include "drawable/fractalCurve.hpp"
#include "drawable/fractalLine.hpp"

#include "drawable/drawable.hpp"
#include "file/serializer.hpp"

namespace Lipuma{
	void SerializeCanvas(Canvas* canvas, QString* filename){
		QFile file(*filename);
		if (!file.open(QIODevice::WriteOnly)){
			qWarning("File failed!");
		}else{
			QDataStream stream(&file);
			for (auto i : canvas->scene()->items()){
				if (i->type() == Drawable::Type){
					dynamic_cast<Drawable*>(i)->write(stream);
				}
			}
			qWarning("File written.");
		}
	}

	Canvas* LoadCanvas(QString* filename){
		QFile file(*filename);
		Canvas* canvas = new Canvas(new QGraphicsScene());
		if (!file.open(QIODevice::ReadOnly)){
			qWarning("File failed!");
		}else{
			QDataStream stream(&file);
			while (!stream.atEnd()){
				qint8 type;
				stream >> type;
				switch(type){
					case (DrawableSerializeTypes::SerializeFractalCurve):
						canvas->scene()->addItem(new FractalCurve(stream));
						break;
					case (DrawableSerializeTypes::SerializeFractalLine):
						canvas->scene()->addItem(new FractalLine(stream));
						break;
				}
			}
		}
		return canvas;
	}
}