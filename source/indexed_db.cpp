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
        return (indexed_db_request_c){ .js_object = this->js_object.call<val>("open", std::string(name), version) };
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
