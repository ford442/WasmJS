#include <indexed_db.hpp>

#ifdef WJS_DEBUG
    #include <console.hpp>
    #include <stdlib.h>
#endif

indexed_db_request_c indexed_db_c::open(const char * name, unsigned version) {
    #ifdef WJS_DEBUG
        console.log("IndexedDB: Opening database '%s' (version: %u) ...", name, version);

        indexed_db_request_c request = {
            .js_object = this->js_object.call<val>("open", std::string(name), version),
        };

        if (request.js_object.isUndefined()) {
            console.error("IndexedDB: Can`t open database '%s' (version: %u)", name, version);
            exit(0);
        }

        return request;
    #else
        return { .js_object = this->js_object.call<val>("open", std::string(name), version) };
    #endif
}

indexed_db_request_c indexed_db_c::deleteDatabase(const char * name) {
    #ifdef WJS_DEBUG
        console.log("IndexedDB: Deleting database '%s' ...", name);

        indexed_db_request_c request = {
            .js_object = this->js_object.call<val>("deleteDatabase", std::string(name)),
        };

        if (request.js_object.isUndefined()) {
            console.error("IndexedDB: Can`t delete database '%s'", name);
            exit(0);
        }

        return request;
    #else
        return { .js_object = this->js_object.call<val>("deleteDatabase", std::string(name)) };
    #endif
}

void indexed_db_request_c::onsuccess(const char * callback_name) {
    #ifdef WJS_DEBUG
        console.log("IndexedDB: Setting request 'onsuccess' callback '%s' for %js request ...",
                    callback_name, &this->js_object);
    #endif

    this->js_object.set("onsuccess", val::module_property(callback_name));
}

void indexed_db_request_c::onerror(const char * callback_name) {
    #ifdef WJS_DEBUG
        console.log("IndexedDB: Setting request 'onerror' callback '%s' for %js request ...",
                    callback_name, &this->js_object);
    #endif

    this->js_object.set("onerror", val::module_property(callback_name));
}

void indexed_db_request_c::onupgradeneeded(const char * callback_name) {
    #ifdef WJS_DEBUG
        console.log("IndexedDB: Setting request 'onupgradeneeded' callback '%s' for %js",
                    callback_name, &this->js_object);
    #endif

    this->js_object.set("onupgradeneeded", val::module_property(callback_name));
}

indexed_db_instance_c indexed_db_instance_c::get_result(val event) {
    #ifdef WJS_DEBUG
        console.log("IndexedDB: Getting result instance from %js event ...", &event);

        indexed_db_instance_c db_instance = {
            .js_object = event["target"].as<val>()["result"].as<val>(),
        };

        if (db_instance.js_object.isUndefined()) {
            console.error("IndexedDB: Can`t get result from %js event ...", &event);
            exit(0);
        }

        return db_instance;
    #else
        return { .js_object = event["target"].as<val>()["result"].as<val>() };
    #endif
}

void indexed_db_instance_c::createObjectStore(const char * table_name) {
    #ifdef WJS_DEBUG
        console.log("IndexedDB: Creating object store '%s' from %js instance ...", table_name, &this->js_object);
    #endif

    this->js_object.call<void>("createObjectStore", std::string(table_name));
}

void indexed_db_instance_c::createObjectStore(const char * table_name, const char * key_name, bool auto_increment) {
    #ifdef WJS_DEBUG
        console.log("IndexedDB: Creating object store '%s' (keyPath: '%s', autoIncrement: %u) "
                    "from %js instance ...", table_name, key_name, auto_increment, &this->js_object);
    #endif

    val js_object = val::object();

    js_object.set("keyPath", std::string(key_name));
    js_object.set("autoIncrement", auto_increment);

    this->js_object.call<void>("createObjectStore", std::string(table_name), js_object);
}

indexed_db_transaction_c indexed_db_instance_c::transaction(std::vector<std::string> tables, transaction_type_t transaction_type) {
    val js_tables = val::array(tables);
    static const std::string transaction_types_str[] = { "readonly", "readwrite" };

    #ifdef WJS_DEBUG
        std::string tables_str;

        for (unsigned i = 0; i < tables.size(); i++) {
            tables_str += std::string(" ") + tables[i] + std::string(" ");
        }

        console.log("IndexedDB: Creating transaction (tables: {%s}, type: %s, db_instance: %js",
                    tables_str.c_str(), transaction_types_str[transaction_type].c_str(), &this->js_object);

        indexed_db_transaction_c db_transaction = {
            .js_object = this->js_object.call<val>("transaction", js_tables, transaction_types_str[transaction_type]),
        };

        if (db_transaction.js_object.isUndefined()) {
            console.error("IndexedDB: Can`t create transaction (tables: {%s}, type: %s, db_instance: %js",
                          tables_str.c_str(), transaction_types_str[transaction_type].c_str(), &this->js_object);
            exit(0);
        }

        return db_transaction;
    #else
        return { .js_object = this->js_object.call<val>("transaction", js_tables, transaction_types_str[transaction_type]) };
    #endif
}

indexed_db_object_store_c indexed_db_transaction_c::objectStore(const char * table_name) {
    #ifdef WJS_DEBUG
        console.log("IndexedDB: Getting object store '%s' from %js transaction ...", table_name, &this->js_object);

        indexed_db_object_store_c db_object_store = {
            .js_object = this->js_object.call<val>("objectStore", std::string(table_name)),
        };

        if (db_object_store.js_object.isUndefined()) {
            console.error("IndexedDB: Can`t get object store '%s' from %js transaction ...", table_name, &this->js_object);
            exit(0);
        }

        return db_object_store;
    #else
        return { .js_object = this->js_object.call<val>("objectStore", std::string(table_name)) };
    #endif
}

indexed_db_request_c indexed_db_object_store_c::add(val object) {
    #ifdef WJS_DEBUG
        console.log("IndexedDB: Adding object (%js) to store %js ...", &object, &this->js_object);

        indexed_db_request_c request = {
            .js_object = this->js_object.call<val>("add", object),
        };

        if (request.js_object.isUndefined()) {
            console.error("IndexedDB: Can`t add object (%js) to store %js ...", &object, &this->js_object);
            exit(0);
        }

        return request;
    #else
        return { .js_object = this->js_object.call<val>("add", object) };
    #endif
}

indexed_db_request_c indexed_db_object_store_c::add(val object, int key) {
    #ifdef WJS_DEBUG
        console.log("IndexedDB: Adding object (key: %d, object: %js) to store %js ...", key, &object, &this->js_object);

        indexed_db_request_c request = {
            .js_object = this->js_object.call<val>("add", object, key),
        };

        if (request.js_object.isUndefined()) {
            console.error("IndexedDB: Can`t add object (key: %d, object: %js) to store %js ...", key, &object, &this->js_object);
            exit(0);
        }

        return request;
    #else
        return { .js_object = this->js_object.call<val>("add", object, key) };
    #endif
}
