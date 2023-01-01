#include "SiviaGraph.h"

// TODO Czy da sie lepiej zrobic printowanie constant

int main() {

    SiviaNode &a = *new SiviaNode(); // wartość nie ma znaczenia, zapamiętujemy tylko ścieżkę obliczeń
    SiviaNode &b = *new SiviaNode();
    SiviaNode &c = *new SiviaNode();
    SiviaNode &d = *new SiviaNode();
    a.setValue(0, 4);
    b.setValue(-1, 1);
    c.setValue(-1, -0.5);
    d.setValue(-3, -2);

    SiviaNode &det = (a * d) - (b * c);
    cout << det.getValue() << "\n";
    cout << det.evaluate() << "\n";
    cout << det.getValue() << "\n";

//    det.evaluate();
//    det.setValue(1);
}