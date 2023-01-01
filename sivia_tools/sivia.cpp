#include "SiviaGraph.h"

// TODO Czy da sie lepiej zrobic printowanie constant

int main() {
    auto *a = new SiviaNode(); // wartość nie ma znaczenia, zapamiętujemy tylko ścieżkę obliczeń

    auto *b = new SiviaNode();

    auto *c = new SiviaNode();

    auto *d = new SiviaNode();

//    SiviaNode *det = (a * d) + (c * d);
    auto *det = new SiviaNode(((*a) * (*d)) - ((*b) * (*c)));
    a->setValue(0, 4);
    b->setValue(-1, 1);
    c->setValue(-1, -0.5);
    d->setValue(-3, -2);

    det->evaluate();
    det->setValue(1);
//    Interval a_val(0, 4);
//    Interval b_val(-1, 1);
//    Interval c_val(-1, -0.5);
//    Interval d_val(-3, -2);
//    SiviaNode a(a_val);
//    SiviaNode b(b_val);
//    SiviaNode c(c_val);
//    SiviaNode d(d_val);
//    SiviaNode a_times_d(&a, &d, mul);
//    SiviaNode b_times_c(&b, &c, mul);
//    SiviaNode pre_det(&a_times_d, &b_times_c, sub);
//    SiviaNode det(&pre_det, 1, sub);
//    cout << a;
//    cout << a_times_d;
//    cout << b_times_c;
//    cout << pre_det;
//    cout << det;
//    SiviaGraph graph(det,eq);
}