#include <dom.hpp>

#include <stdarg.h>
#include <stdio.h>

#ifdef WJS_DEBUG
    #include <console.hpp>
    #include <stdlib.h>
#endif

enum {
    DOM_ID_BUFFER_SIZE = 32,
    DOM_CLASS_NAME_BUFFER_SIZE = 64,
    DOM_INNER_HTML_BUFFER_SIZE = 2048,
    DOM_QUERY_SELECTOR_BUFFER_SIZE = 64,
};

dom_object_c common_query_selector(val * js_object, const char * selector_string) {
    #ifdef WJS_DEBUG
        dom_object_c dom_object = {
            .js_object = js_object->call<val>("querySelector", std::string(selector_string)),
        };

        console.logf("DOM: Geting element by selector '%s' ...", selector_string);

        if (dom_object.js_object.isUndefined()) {
            console.errorf("DOM: Can`t get element by selector '%s'", selector_string);
            exit(0);
        }

        return dom_object;
    #else
        return (dom_object_c){ .js_object = js_object->call<val>("querySelector", std::string(selector_string)) };
    #endif
}

std::vector<dom_object_c> common_query_selector_all(val * js_object, const char * selector_string) {
    #ifdef WJS_DEBUG
        val dom_objects_array = js_object->call<val>("querySelectorAll", std::string(selector_string));

        console.logf("DOM: Geting elements by selector '%s' ...", selector_string);

        if (dom_objects_array.isUndefined()) {
            console.errorf("DOM: Can`t get elements by selector '%s'", selector_string);
            exit(0);
        }

        std::vector<dom_object_c> html_objects;

        for (unsigned i = 0, length = dom_objects_array["length"].as<unsigned>(); i < length; i++) {
            html_objects.push_back((dom_object_c){
                .js_object = dom_objects_array[i].as<val>(),
            });
        }

        return html_objects;
    #else
        return (dom_object_c){ .js_object = js_object->call<val>("querySelector", std::string(selector_string)) };
    #endif
}

/* dom_object_c */

void dom_object_c::innerHTML(const char * string) {
    #ifdef WJS_DEBUG
        console.logf("DOM: Setting element innerHTML: '%s' ...", string);
        this->js_object.set("innerHTML", std::string(string));
    #else
        this->js_object.set("innerHTML", std::string(string));
    #endif
}

void dom_object_c::innerHTMLf(const char * string, ...) {
    va_list arg_list;
    va_start(arg_list, string);

    char inner_html_buffer[DOM_INNER_HTML_BUFFER_SIZE];
    vsnprintf(inner_html_buffer, sizeof(inner_html_buffer), string, arg_list);

    innerHTML(inner_html_buffer);
    va_end(arg_list);
}

void dom_object_c::className(const char * class_string) {
    #ifdef WJS_DEBUG
        console.logf("DOM: Setting element className: '%s' ...", class_string);
        this->js_object.set("className", std::string(class_string));
    #else
        this->js_object.set("className", std::string(class_string));
    #endif
}

void dom_object_c::classNamef(const char * class_string, ...) {
    va_list arg_list;
    va_start(arg_list, class_string);

    char class_name_buffer[DOM_CLASS_NAME_BUFFER_SIZE];
    vsnprintf(class_name_buffer, sizeof(class_name_buffer), class_string, arg_list);

    className(class_name_buffer);
    va_end(arg_list);
}

dom_object_c dom_object_c::querySelector(const char * selector_string) {
    return common_query_selector(&this->js_object, selector_string);
}

dom_object_c dom_object_c::querySelectorf(const char * selector_string, ...) {
    va_list arg_list;
    va_start(arg_list, selector_string);

    char query_selector_buffer[DOM_INNER_HTML_BUFFER_SIZE];
    vsnprintf(query_selector_buffer, sizeof(query_selector_buffer), selector_string, arg_list);

    return common_query_selector(&this->js_object, query_selector_buffer);
}

std::vector<dom_object_c> dom_object_c::querySelectorAll(const char * selector_string) {
    return common_query_selector_all(&this->js_object, selector_string);
}

std::vector<dom_object_c> dom_object_c::querySelectorAllf(const char * selector_string, ...) {
    va_list arg_list;
    va_start(arg_list, selector_string);

    char query_selector_buffer[DOM_INNER_HTML_BUFFER_SIZE];
    vsnprintf(query_selector_buffer, sizeof(query_selector_buffer), selector_string, arg_list);

    return common_query_selector_all(&this->js_object, query_selector_buffer);
}

/* dom_document_c */

dom_object_c dom_document_c::querySelector(const char * selector_string) {
    return common_query_selector(&this->js_object, selector_string);
}

dom_object_c dom_document_c::querySelectorf(const char * selector_string, ...) {
    va_list arg_list;
    va_start(arg_list, selector_string);

    char query_selector_buffer[DOM_INNER_HTML_BUFFER_SIZE];
    vsnprintf(query_selector_buffer, sizeof(query_selector_buffer), selector_string, arg_list);

    return common_query_selector(&this->js_object, query_selector_buffer);
}

std::vector<dom_object_c> dom_document_c::querySelectorAll(const char * selector_string) {
    return common_query_selector_all(&this->js_object, selector_string);
}

std::vector<dom_object_c> dom_document_c::querySelectorAllf(const char * selector_string, ...) {
    va_list arg_list;
    va_start(arg_list, selector_string);

    char query_selector_buffer[DOM_INNER_HTML_BUFFER_SIZE];
    vsnprintf(query_selector_buffer, sizeof(query_selector_buffer), selector_string, arg_list);

    return common_query_selector_all(&this->js_object, query_selector_buffer);
}
