#pragma once

#include <vector>
#include <emscripten/val.h>
#include <emscripten/bind.h>
using namespace emscripten;

class dom_object_c {
    public:
        val js_object;

    public:
        void innerHTML(const char * string);
        void className(const char * class_string);
        dom_object_c querySelector(const char * selector_string);
        std::vector<dom_object_c> querySelectorAll(const char * selector_string);

        void innerHTMLf(const char * string, ...);
        void classNamef(const char * class_string, ...);
        dom_object_c querySelectorf(const char * selector_string, ...);
        std::vector<dom_object_c> querySelectorAllf(const char * selector_string, ...);
};

class dom_document_c {
    private:
        val js_object = val::global("document");

    public:
        dom_object_c querySelector(const char * selector_string);
        std::vector<dom_object_c> querySelectorAll(const char * selector_string);

        dom_object_c querySelectorf(const char * selector_string, ...);
        std::vector<dom_object_c> querySelectorAllf(const char * selector_string, ...);
};

static dom_document_c document;
