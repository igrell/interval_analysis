#include "SiviaNode.h"
#include "EmptyIntersectionException.h"

using std::pair;

int main() {
//    SiviaNode &a = *new SiviaNode();
//    SiviaNode &b = *new SiviaNode();
//    SiviaNode &c = *new SiviaNode();
//    SiviaNode &d = *new SiviaNode();
//    a.setValue(0, 4);
//    b.setValue(-1, 1);
//    c.setValue(-1, -0.5);
//    d.setValue(-3, -2);
//
//    SiviaNode &det = (a * d) - (b * c); // computation path
//    cout << "Graph evaluation: " << det.evaluate() << "\n";
//    det.setValue(1);
//    try { det.contract(); } catch (EmptyIntersectionException &warning) {}
//
//    cout << "Constrains: \n";
//    cout << "a " << a << "\n";
//    cout << "b " << b << "\n";
//    cout << "c " << c << "\n";
//    cout << "d " << d << "\n";
//    det.free();

    // TODO coś nie tak tutaj
    SiviaNode &x1 = *new SiviaNode();
    SiviaNode &y1 = *new SiviaNode();
    SiviaNode &x2 = *new SiviaNode();
    SiviaNode &y2 = *new SiviaNode();
    SiviaNode &cons = *new SiviaNode();
    x1.setValue(-100, 100);
    y1.setValue(-300, 300);
    x2.setValue(-5,5);
    y2.setValue(-2,6);
    pair<SiviaNode &, SiviaNode &> f = {x1 * x2, y1 * y2};
    cout << f.first.evaluate() << " , " << f.second.evaluate() << "\n";
    f.first.setValue(1);
    f.second.setValue(1);
    try { f.first.contract(); } catch (EmptyIntersectionException &warning) {} // TODO program się zatrzymuje przez divisionByZeroException
    try { f.second.contract(); } catch (EmptyIntersectionException &warning) {}
    cout << x1 << "\n" << y1 << "\n" << x2 << "\n" << y2 << "\n";
    f.first.free();
    f.second.free();
}