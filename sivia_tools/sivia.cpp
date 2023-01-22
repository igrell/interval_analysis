#include "SiviaNode.h"
#include "EmptyIntersectionException.h"

int main() {
    SiviaNode &a = *new SiviaNode();
    SiviaNode &b = *new SiviaNode();
    SiviaNode &c = *new SiviaNode();
    SiviaNode &d = *new SiviaNode();
    a.setValue(0, 4);
    b.setValue(-1, 1);
    c.setValue(-1, -0.5);
    d.setValue(-3, -2);

    SiviaNode &det = (a * d) - (b * c); // computation path
    cout << "Graph evaluation: " << det.evaluate() << "\n";
    det.setValue(1);
    try { det.contract(); } catch (EmptyIntersectionException &warning) {}

    cout << "Constrains: \n";
    cout << "a " << a << "\n";
    cout << "b " << b << "\n";
    cout << "c " << c << "\n";
    cout << "d " << d << "\n";
    det.free();

//    SiviaNode &x = *new SiviaNode();
////    SiviaNode &y = *new SiviaNode();
//    x.setValue(-20, 0);
////    y.setValue(-5, 5);
//
//    SiviaNode &det = (x * x); // computation path
//    cout << "Graph evaluation: " << det.evaluate() << "\n";
//    det.setValue(1);
//    try { det.contract(); } catch (EmptyIntersectionException &warning) {}
//
//    cout << "Constrains: \n";
//    cout << "a " << x << "\n";
////    cout << "b " << y << "\n";
//    det.free();

}