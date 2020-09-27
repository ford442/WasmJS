#pragma once

#include <vector>
#include <emscripten/val.h>
#include <emscripten/bind.h>
using namespace emscripten;

typedef enum {
    TRANSACTION_READONLY,
    TRANSACTION_READWRITE,
} transaction_type_t;

class indexed_db_request_c {
    public:
        val js_object;

    public:
        void onerror(const char * callback_name);
        void onsuccess(const char * callback_name);
        void onupgradeneeded(const char * callback_name);
};

class indexed_db_object_store_c {
    public:
        val js_object;

    public:
        indexed_db_request_c add(val object);
        indexed_db_request_c add(val object, int key);
};

class indexed_db_transaction_c {
    public:
        val js_object;

    public:
        indexed_db_object_store_c objectStore(const char * table_name);
};

class indexed_db_instance_c {
    public:
        val js_object;

    public:
        indexed_db_instance_c get_result(val event);
        void createObjectStore(const char * table_name);
        void createObjectStore(const char * table_name, const char * key_name, bool auto_increment);
        indexed_db_transaction_c transaction(std::vector<std::string>, transaction_type_t transaction_type);
};

class indexed_db_c {
    private:
        const val js_object = val::global("indexedDB");

    public:
        indexed_db_request_c open(const char * name, unsigned version);
        indexed_db_request_c deleteDatabase(const char * name);
};

static indexed_db_c indexedDB;
