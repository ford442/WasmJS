#include <indexed_db.hpp>

#ifdef WJS_DEBUG
    #include <console.hpp>
    #include <stdlib.h>
#endif

indexed_db_request_c indexed_db_c::open(const char * name, unsigned version) {
    #ifdef WJS_DEBUG
        indexed_db_request_c request = {
            .js_object = this->js_object.call<val>("open", std::string(name), version),
        };

        console.logf("IndexedDB: Opening database '%s' (varsion: %u) ...", name, version);

        if (request.js_object.isUndefined()) {
            console.errorf("IndexedDB: Can`t open database '%s' (varsion: %u) ...", name, version);
            exit(0);
        }

        return request;
    #else
        return { .js_object = this->js_object.call<val>("open", std::string(name), version) };
    #endif
}

void indexed_db_request_c::onsuccess(const char * callback_name) {
    #ifdef WJS_DEBUG
        console.logf("IndexedDB: Setting request 'onsuccess' callback '%s'...", callback_name);
        this->js_object.set("onsuccess", val::module_property(callback_name));
    #else
        this->js_object.set("onsuccess", val::module_property(callback_name));
    #endif
}

void indexed_db_request_c::onerror(const char * callback_name) {
    #ifdef WJS_DEBUG
        console.logf("IndexedDB: Setting request 'onerror' callback '%s'...", callback_name);
        this->js_object.set("onerror", val::module_property(callback_name));
    #else
        this->js_object.set("onerror", val::module_property(callback_name));
    #endif
}

void indexed_db_request_c::onupgradeneeded(const char * callback_name) {
    #ifdef WJS_DEBUG
        console.logf("IndexedDB: Setting request 'onupgradeneeded' callback '%s'...", callback_name);
        this->js_object.set("onupgradeneeded", val::module_property(callback_name));
    #else
        this->js_object.set("onupgradeneeded", val::module_property(callback_name));
    #endif
}

indexed_db_instance_c indexed_db_request_c::resultInstance() {
    return { .js_object = this->js_object["result"].as<val>() };
}

void indexed_db_instance_c::createObjectStore(const char * table_name, const char * key_name, bool auto_increment) {
    if (key_name != NULL) {
        val js_object = val::object();

        js_object.set("keyPath", std::string(key_name));
        js_object.set("autoIncrement", auto_increment);

        this->js_object.call<void>("createObjectStore", std::string(table_name), js_object);
    } else {
        this->js_object.call<void>("createObjectStore", std::string(table_name));
    }
}

indexed_db_transaction_c indexed_db_instance_c::transaction(std::vector<std::string> tables,
                                                            transaction_type_t transaction_type) {
    val js_tables = val::array(tables);
    static const std::string transaction_types_str[] = { "readonly", "readwrite" };

    return { .js_object = this->js_object.call<val>("transaction", js_tables, transaction_types_str[transaction_type]) };
}
