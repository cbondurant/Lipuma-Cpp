#include <iostream>

#include <QPointF>

// This file exists to define print overrides for catch error types
// Qt does not natively support writing outputs to ostream.
// This file should only be used for debug test strings, do not use 
// this in production code. 

inline std::ostream &operator<<(std::ostream &os, const QPointF &value)
{
    return os << '(' << value.x() << ',' << value.y() << ')';
}