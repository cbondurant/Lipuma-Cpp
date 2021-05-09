#ifndef FILE_SERIALIZER_HPP
#define FILE_SERIALIZER_HPP

#include <QString>
#include "widget/canvas.hpp"

namespace Lipuma {
	void SerializeCanvas(Canvas*, QString*);
	Canvas* LoadCanvas(QString*);
}

#endif