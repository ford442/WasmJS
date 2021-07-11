#include <indexed_db.hpp>

#define GET_FUNC_NAME_STR(func) #func
#define DATABASE_NAME "Local-DB"
#define TABLE1_NAME "table1"
#define TABLE2_NAME "table2"

static indexed_db_instance_c db_instance = {
    .js_object = val::undefined()
};

int main() {
    auto db_request = indexedDB.open(DATABASE_NAME, 1);

    db_request.onupgradeneeded(GET_FUNC_NAME_STR(idb_open_onupgradeneeded));
    db_request.onsuccess(GET_FUNC_NAME_STR(idb_open_success));

    #ifdef WJS_DEBUG
        db_request.onerror(GET_FUNC_NAME_STR(idb_error));
    #endif

    return 0;
}

void idb_open_onupgradeneeded(val event) {
    db_instance = db_instance.get_result(event);
    db_instance.createObjectStore(TABLE1_NAME, "id", true);
    db_instance.createObjectStore(TABLE2_NAME);

    main();
}

void idb_open_success(val event) {
    db_instance = db_instance.get_result(event);
    auto transaction = db_instance.transaction({TABLE1_NAME, TABLE2_NAME}, TRANSACTION_READWRITE);

    auto table1_store = transaction.objectStore(TABLE1_NAME);
    auto table2_store = transaction.objectStore(TABLE2_NAME);

    val js_object = val::object();
    js_object.set("data", 30);
    js_object.set("test", std::string("str"));

    auto db_request = table1_store.add(js_object);

    #ifdef WJS_DEBUG
        db_request.onsuccess(GET_FUNC_NAME_STR(idb_add_success));
        db_request.onerror(GET_FUNC_NAME_STR(idb_error));
    #endif
}

#ifdef WJS_DEBUG
    #include <console.hpp>

    void idb_add_success(val event) {
        console.info("IndexedDB Example: The object was successfully added %js", &event);
    }

    void idb_error(val event) {
        console.error("IndexedDB Example Error: %js", &event);
    }
#endif

EMSCRIPTEN_BINDINGS() {
    function(GET_FUNC_NAME_STR(idb_open_onupgradeneeded), &idb_open_onupgradeneeded);
    function(GET_FUNC_NAME_STR(idb_open_success), &idb_open_success);
    function(GET_FUNC_NAME_STR(idb_add_success), &idb_add_success);

    #ifdef WJS_DEBUG
        function(GET_FUNC_NAME_STR(idb_error), &idb_error);
    #endif
}
