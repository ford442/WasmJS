#include <console.hpp>
#include <string.h>
#include <stdarg.h>

#ifdef WJS_DEBUG
    #include <stdlib.h>
#endif

enum {
    CONSOLE_STRING_BUFFER_SIZE = 512,
    CONSOLE_SPRINTF_BUFFER_SIZE = 512,
};

void console_c::clear() {
    this->js_object.call<void>("clear");
}

void console_c::table(const val js_object) {
    this->js_object.call<void>("table", js_object);
}

void console_print(const val js_object, const char * type, const char * string, va_list arg_list) {
    char string_buffer[CONSOLE_STRING_BUFFER_SIZE];
    char sprintf_buffer[CONSOLE_SPRINTF_BUFFER_SIZE];

    std::vector<val> console_js_val;
    std::vector<std::string> console_strings;

    strcpy(string_buffer, string);
    char * str_buf_ptr = string_buffer;

    for (char * str_buf_ptr_tmp = string_buffer; (str_buf_ptr_tmp = strstr(str_buf_ptr_tmp, "%js")) != NULL; str_buf_ptr = str_buf_ptr_tmp += 3) {
        str_buf_ptr_tmp[0] = 0;
        vsnprintf(sprintf_buffer, sizeof(sprintf_buffer), str_buf_ptr, arg_list);

        console_strings.push_back(std::string(sprintf_buffer));
        console_js_val.push_back(va_arg(arg_list, val *)[0]);
    }

    vsnprintf(sprintf_buffer, sizeof(sprintf_buffer), str_buf_ptr, arg_list);

    switch (console_js_val.size()) {
        case 0: {
            js_object.call<void>(type, std::string(sprintf_buffer));
        } break;
        case 1: {
            js_object.call<void>(type, console_strings[0], console_js_val[0], std::string(sprintf_buffer));
        } break;
        case 2: {
            js_object.call<void>(type, console_strings[0], console_js_val[0],
                console_strings[1], console_js_val[1], std::string(sprintf_buffer));
        } break;
        #ifdef WJS_DEBUG
            default: {
                snprintf(sprintf_buffer, sizeof(sprintf_buffer), "Console: Too many specifiers %%js in the string '%s'"
                                                                 "(max: 2, current: %lu)", string, console_js_val.size());
                js_object.call<void>("error", std::string(sprintf_buffer));
            } exit(0);
        #endif
    };
}

void console_c::log(const char * string, ...) {
    va_list arg_list;
    va_start(arg_list, string);

    console_print(this->js_object, "log", string, arg_list);
    va_end(arg_list);
}

void console_c::info(const char * string, ...) {
    va_list arg_list;
    va_start(arg_list, string);

    console_print(this->js_object, "info", string, arg_list);
    va_end(arg_list);
}

void console_c::warn(const char * string, ...) {
    va_list arg_list;
    va_start(arg_list, string);

    console_print(this->js_object, "warn", string, arg_list);
    va_end(arg_list);
}

void console_c::error(const char * string, ...) {
    va_list arg_list;
    va_start(arg_list, string);

    console_print(this->js_object, "error", string, arg_list);
    va_end(arg_list);
}

void console_call(const val js_object, const char * type, const char * label, va_list arg_list) {
    char sprintf_buffer[CONSOLE_SPRINTF_BUFFER_SIZE];

    vsnprintf(sprintf_buffer, sizeof(sprintf_buffer), label, arg_list);
    js_object.call<void>(type, std::string(sprintf_buffer));
}

void console_c::count(const char * label, ...) {
    va_list arg_list;
    va_start(arg_list, label);

    console_call(this->js_object, "count", label, arg_list);
    va_end(arg_list);
}

void console_c::countReset(const char * label, ...) {
    va_list arg_list;
    va_start(arg_list, label);

    console_call(this->js_object, "countReset", label, arg_list);
    va_end(arg_list);
}

void console_c::group(const char * label, ...) {
    va_list arg_list;
    va_start(arg_list, label);

    console_call(this->js_object, "group", label, arg_list);
    va_end(arg_list);
}

void console_c::groupCollapsed(const char * label, ...) {
    va_list arg_list;
    va_start(arg_list, label);

    console_call(this->js_object, "groupCollapsed", label, arg_list);
    va_end(arg_list);
}

void console_c::groupEnd() {
    this->js_object.call<void>("groupEnd");
}

void console_c::time(const char * label, ...) {
    va_list arg_list;
    va_start(arg_list, label);

    console_call(this->js_object, "time", label, arg_list);
    va_end(arg_list);
}

void console_c::timeLog(const char * label, ...) {
    va_list arg_list;
    va_start(arg_list, label);

    console_call(this->js_object, "timeLog", label, arg_list);
    va_end(arg_list);
}

void console_c::timeEnd(const char * label, ...) {
    va_list arg_list;
    va_start(arg_list, label);

    console_call(this->js_object, "timeEnd", label, arg_list);
    va_end(arg_list);
}
