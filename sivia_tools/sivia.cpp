#include "SiviaGraph.h"

int main() {
    Interval a_val(0, 4);
    Interval b_val(-1, 1);
    Interval c_val(-1, -0.5);
    Interval d_val(-3, -2);
    SiviaNode a(a_val);
    SiviaNode b(b_val);
    SiviaNode c(c_val);
    SiviaNode d(d_val);
    SiviaNode a_times_d(&a,&d,mul);
    SiviaNode b_times_c(&b,&c,mul);
    SiviaNode det(&a_times_d,&b_times_c,sub);
}