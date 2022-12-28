#ifndef INTERVAL_ANALYSIS_DRAWPOLICY_H
#define INTERVAL_ANALYSIS_DRAWPOLICY_H

#include "fstream"
#include "iostream"
#include "interval_arithmetic_tools/IPoint.h"

using std::ofstream;

struct EmptyDrawPolicy {
    static void drawIPoint(const IPoint &iPoint) {}

    static void emptyFile() {}
};

struct FileDrawPolicy {
    static ofstream file;

    static void drawIPoint(const IPoint &iPoint) {
        file.open("output.txt", std::ios::out | std::ios::app);
//        if (!file) {
//            cout << "No file!\n";
//            return;
//        }

        file << iPoint;
        file.close();
    }

    static void emptyFile() {
        file.open("output.txt", std::ios::out);
        file.close();
    }
};

ofstream FileDrawPolicy::file = ofstream();

struct PrintDrawPolicy {
    static void drawIPoint(const IPoint &iPoint) {
        cout << iPoint;
    }
};

struct PrintAndFileDrawPolicy {
    static ofstream file;

    static void drawIPoint(const IPoint &iPoint) {
        file.open("output.txt", std::ios::out | std::ios::app);
        if (!file) {
            cout << "No file!\n";
            return;
        }
        file << iPoint;
        file.close();
        cout << iPoint;
    }

    static void emptyFile() {
        file.open("output.txt", std::ios::out);
        file.close();
    }
};

ofstream PrintAndFileDrawPolicy::file = ofstream();

#endif