#include "SiviaNode.h"

ostream &operator<<(ostream &ostream, const Operator prev_operator) {
        switch (prev_operator) {
            case add:
                ostream << " + ";
                break;
            case sub:
                ostream << " - ";
                break;
            case mul:
                ostream << " * ";
                break;
            case dv:
                ostream << " / ";
                break;
            case pw:
                ostream << " ^ ";
                break;
        }
        return ostream;
}

ostream &operator<<(ostream &ostream, const SiviaNode &siviaNode) {

}
