#pragma once

#include <emscripten/val.h>
using namespace emscripten;

class console_c {
    private:
        const val js_object = val::global("console");

    public:
        void clear();
        void table(const val js_object);
        void count(const char * label, ...);
        void countReset(const char * label, ...);

        void log(const char * string, ...);
        void info(const char * string, ...);
        void warn(const char * string, ...);
        void error(const char * string, ...);

        void group(const char * label, ...);
        void groupCollapsed(const char * label, ...);
        void groupEnd();

        void time(const char * label, ...);
        void timeLog(const char * label, ...);
        void timeEnd(const char * label, ...);
};

static console_c console;
