#include <indexed_db.hpp>
#include <console.hpp>

#define GET_FUNC_NAME_STR(func) #func

static indexed_db_request_c db_request = {
    .js_object = val::undefined()
};

static indexed_db_instance_c db_instance = {
    .js_object = val::undefined()
};

int main() {
    db_request = indexedDB.open("Local-DB", 2);

    db_request.onupgradeneeded(GET_FUNC_NAME_STR(idb_open_onupgradeneeded));
    db_request.onsuccess(GET_FUNC_NAME_STR(idb_open_succsess));
    db_request.onerror(GET_FUNC_NAME_STR(idb_open_error));

    return 0;
}

void idb_open_onupgradeneeded(val event) {
    db_instance = db_request.resultInstance();

    db_instance.createObjectStore("table1", "id", true);
    db_instance.createObjectStore("table2", "id", false);

    main();
}

void idb_open_succsess() {
    db_instance = db_request.resultInstance();

    auto transaction = db_instance.transaction({"table1", "table2"}, TRANSACTION_READWRITE);
}

void idb_open_error(val event) {
    console.error("IndexedDB: Can`t open database");
}

EMSCRIPTEN_BINDINGS() {
    function(GET_FUNC_NAME_STR(idb_open_onupgradeneeded), &idb_open_onupgradeneeded);
    function(GET_FUNC_NAME_STR(idb_open_succsess), &idb_open_succsess);
    function(GET_FUNC_NAME_STR(idb_open_error), &idb_open_error);
}
