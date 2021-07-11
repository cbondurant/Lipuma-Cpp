#include <QString>
#include <QFile>

#include "drawable/fractalCurve.hpp"
#include "drawable/fractalLine.hpp"

#include "drawable/drawable.hpp"
#include "file/serializer.hpp"

const quint32 MAGIC = 0x4c504d41; // hex LPMA

namespace Lipuma{
	void SerializeScene(QGraphicsScene* scene, QString& filename){
		QFile file(filename);
		if (!file.open(QIODevice::WriteOnly)){
			qWarning("File failed!");
		}else{
			QDataStream stream(&file);
			stream << MAGIC;
			for (auto i : scene->items()){
				if (i->type() == Drawable::Type){
					dynamic_cast<Drawable*>(i)->write(stream);
				}
			}
			qWarning("File written.");
		}
	}

	QGraphicsScene* LoadScene(QString& filename){
		QFile file(filename);
		QGraphicsScene* scene = new QGraphicsScene();
		if (!file.open(QIODevice::ReadOnly)){
			qWarning("File failed!");
		}else{
			QDataStream stream(&file);
			qint32 magic;
			stream >> magic;
			if (magic != MAGIC){qWarning("File load failed: invalid magic number"); return nullptr;}
			while (!stream.atEnd()){
				qint8 type;
				stream >> type;
				switch(type){
					case (DrawableSerializeTypes::SerializeFractalCurve):
						scene->addItem(new FractalCurve(stream));
						break;
					case (DrawableSerializeTypes::SerializeFractalLine):
						scene->addItem(new FractalLine(stream));
						break;
				}
			}
		}
		return scene;
	}
}