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
    det.evaluate();

    det.setValue(1);
    det.contract();
    cout << "a " << a << "\n";
    cout << "b " << b << "\n";
    cout << "c " << c << "\n";
    cout << "d " << d << "\n"; // TODO should be [-3,-2]; maybe try to catch an error?

}