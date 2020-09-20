#pragma once

#include <emscripten/val.h>
#include <emscripten/bind.h>
using namespace emscripten;

class indexed_db_request_c {
    public:
        val js_object;

    public:
        void onerror(const char * callback_name);
        void onsuccess(const char * callback_name);
};

class indexed_db_c {
    private:
        const val js_object = val::global("indexedDB");

    public:
        indexed_db_request_c open(const char * name, unsigned version);
};

static indexed_db_c indexedDB;
