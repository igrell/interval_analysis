#ifndef INTERVAL_ANALYSIS_DRAWPOLICY_H
#define INTERVAL_ANALYSIS_DRAWPOLICY_H

#include "fstream"
#include "iostream"
#include "interval_arithmetic_tools/IPoint.h"
#include "sstream"

using std::ofstream, std::ostringstream;

struct EmptyDrawPolicy {
    static void drawIPoint(const IPoint &iPoint) {}

    static void emptyFile() {}
};

struct MemoryDrawPolicy {
    static ostringstream file;

    static void drawIPoint(const IPoint &iPoint) {
//        file.open("output.txt", std::ios::out | std::ios::app);
//        if (!file) {
//            cout << "No file!\n";
//            return;
//        }
        file << iPoint;
//        file.close();
    }

    static void emptyFile() {
    }

    static void saveToFile(std::string &filename) {
        ofstream file_out;
        file_out.open(filename);
        file_out << file.str();
        file_out.close();
    }
};

ostringstream MemoryDrawPolicy::file = ostringstream();

struct FileDrawPolicy {
    static ofstream file;

    static void drawIPoint(const IPoint &iPoint) {
        if (!file.is_open()) file.open("output.txt", std::ios::out | std::ios::app);
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

ofstream FileDrawPolicy::file = ofstream("output.txt", std::ios::out);

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