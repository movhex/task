#include "object.h"


Object::Object(char marker) : m_marker(marker) {}

char Object::getMarker(void) const
{
    return m_marker;
}
