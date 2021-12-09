#ifndef OBJECT_H
#define OBJECT_H


class Object {
public:
    Object(char marker = 'r');
    char getMarker(void) const;
    // operator char(void) { return m_marker; }
private:
    char m_marker;
}; // End of class


#endif // OBJECT_H
