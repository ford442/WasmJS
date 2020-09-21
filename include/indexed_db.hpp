#pragma once

#include <vector>
#include <emscripten/val.h>
#include <emscripten/bind.h>
using namespace emscripten;

typedef enum {
    TRANSACTION_READONLY,
    TRANSACTION_READWRITE,
} transaction_type_t;

class indexed_db_transaction_c {
    public:
        val js_object;
};

class indexed_db_instance_c {
    public:
        val js_object = val::undefined();

    public:
        void createObjectStore(const char * table_name, const char * key_name, bool auto_increment);
        indexed_db_transaction_c transaction(std::vector<std::string>, transaction_type_t transaction_type);
};

class indexed_db_request_c {
    public:
        val js_object;

    public:
        indexed_db_instance_c resultInstance();
        void onerror(const char * callback_name);
        void onsuccess(const char * callback_name);
        void onupgradeneeded(const char * callback_name);
};

class indexed_db_c {
    private:
        const val js_object = val::global("indexedDB");

    public:
        indexed_db_request_c open(const char * name, unsigned version);
};

static indexed_db_c indexedDB;
