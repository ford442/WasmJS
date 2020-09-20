#include <console.hpp>
#include <stdarg.h>

enum {
    CONSOLE_DEBUG_BUFFER_SIZE = 512,
};

void console_call(const val * js_object, const char * type, const char * string) {
    js_object->call<void>(type, std::string(string));
}

void console_c::log(const char * string) {
    console_call(&this->js_object, "log", string);
}

void console_c::warn(const char * string) {
    console_call(&this->js_object, "warn", string);
}

void console_c::error(const char * string) {
    console_call(&this->js_object, "error", string);
}

void console_callf(const val * js_object, const char * type, const char * string, va_list arg_list) {
    char console_buffer[CONSOLE_DEBUG_BUFFER_SIZE];
    vsnprintf(console_buffer, sizeof(console_buffer), string, arg_list);

    js_object->call<void>(type, std::string(console_buffer));
}

void console_c::logf(const char * string, ...) {
    va_list arg_list;
    va_start(arg_list, string);

    console_callf(&this->js_object, "log", string, arg_list);
    va_end(arg_list);
}

void console_c::warnf(const char * string, ...) {
    va_list arg_list;
    va_start(arg_list, string);

    console_callf(&this->js_object, "warn", string, arg_list);
    va_end(arg_list);
}

void console_c::errorf(const char * string, ...) {
    va_list arg_list;
    va_start(arg_list, string);

    console_callf(&this->js_object, "error", string, arg_list);
    va_end(arg_list);
}
