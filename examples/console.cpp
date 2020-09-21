#include <console.hpp>

int main() {
    auto js_object = val::object();
    auto js_array = val::array(std::vector<int>({1, 2, 3}));

    js_object.set("int_field", 128);
    js_object.set("str_field", std::string("Some text"));

    console.log("Simple console log output");
    console.log("Printf style log output %u", 0);
    console.log("JS Array: %js, JS Object: %js", &js_array, &js_object);

    console.info("Simple console info output");
    console.info("Printf style info output %u", 0);
    console.info("JS Array: %js, JS Object: %js", &js_array, &js_object);

    console.warn("Console warning output");
    console.warn("Printf style warning output %u", 0);
    console.warn("JS Array: %js, JS Object: %js", &js_array, &js_object);

    console.error("Console error output");
    console.error("Printf style error output %u", 0);
    console.error("JS Array: %js, JS Object: %js", &js_array, &js_object);

    std::vector<val> js_objects_array;

    for (unsigned i = 0; i < 6; i++) {
        auto js_object = val::object();

        js_object.set("int_field", i * 33);
        js_object.set("str_field", std::string("Some text - ") + std::to_string(i));

        js_objects_array.push_back(js_object);
    }

    console.table(val::array(js_objects_array));

    console.group("Some Group Label");
    console.log("Output in 'Some Group Label' group");
    console.groupEnd();

    console.group("Group %u", 1);
    console.log("Output in 'Group %u'", 1);
    console.groupEnd();

    console.groupCollapsed("Some Group Label Collapsed");
    console.log("Output in 'Some Group Label Collapsed' group");
    console.groupEnd();

    console.groupCollapsed("Group %u collapsed", 1);
    console.log("Output in 'Group %u collapsed'", 1);
    console.groupEnd();

    console.time("Some Time Label");
    console.time("Time %u label", 1);

    console.timeLog("Some Time Label");
    console.timeLog("Time %u label", 1);

    console.timeEnd("Some Time Label");
    console.timeEnd("Time %u label", 1);

    for (unsigned i = 0; i < 10; i++) {
        console.count("Some Count Label");
        console.count("Count %u label", 1);
    }

    console.countReset("Some Count Label");
    console.countReset("Count %u label", 1);

    // console.clear();

    return 0;
}
