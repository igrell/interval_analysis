#ifndef INTERVAL_ANALYSIS_DRAWPOLICY_H
#define INTERVAL_ANALYSIS_DRAWPOLICY_H

#include "fstream"
#include "iostream"
#include "IPoint.h"
#include "sstream"

using std::ofstream, std::ostringstream;

struct EmptyDrawPolicy {
    static void drawIPoint(const IPoint &iPoint) {}

};

struct MemoryDrawPolicy {
    static ostringstream file;

    static void drawIPoint(const IPoint &iPoint) {
        file << iPoint;
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
        file << iPoint;
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
        if (!file.is_open()) file.open("output.txt", std::ios::out | std::ios::app);
        file << iPoint;
        file.close();
        cout << iPoint;
    }
};

ofstream PrintAndFileDrawPolicy::file = ofstream("output.txt", std::ios::out);

#endif