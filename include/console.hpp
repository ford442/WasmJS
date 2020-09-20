#pragma once

#include <emscripten/val.h>
using namespace emscripten;

class console_c {
    private:
        const val js_object = val::global("console");

    public:
        void log(const char * string);
        void warn(const char * string);
        void error(const char * string);

        void logf(const char * string, ...);
        void warnf(const char * string, ...);
        void errorf(const char * string, ...);
};

static console_c console;
