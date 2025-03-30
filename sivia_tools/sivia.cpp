#include "SiviaNode.h"
#include "EmptyIntersectionException.h"
#include "vector"

using std::pair, std::vector, std::cin;

int main() {

     SiviaNode &a = *new SiviaNode();
     SiviaNode &b = *new SiviaNode();
     SiviaNode &c = *new SiviaNode();
     SiviaNode &d = *new SiviaNode();
     double a_lo, a_hi, b_lo, b_hi, c_lo, c_hi, d_lo, d_hi, det_val;
     cin >> a_lo >> a_hi >> b_lo >> b_hi >> c_lo >> c_hi >> d_lo >> d_hi;
     a.setValue(a_lo, a_hi);
     b.setValue(b_lo, b_hi);
     c.setValue(c_lo, c_hi);
     d.setValue(d_lo, d_hi);
     SiviaNode &det = (a * d) - (b * c); // computation path
     cout << "Graph evaluation: " << det.evaluate() << "\n";
     cin >> det_val;
     det.setValue(det_val);
     try { det.contract(); } catch (EmptyIntersectionException &warning) {}

     cout << "Constrains: \n";
     cout << "a " << a << "\n";
     cout << "b " << b << "\n";
     cout << "c " << c << "\n";
     cout << "d " << d << "\n";
     det.free();
}