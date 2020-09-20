#include <dom.hpp>

int main() {
    /* Part 1 */
    auto part1_div = document.querySelector("#part1");
    part1_div.querySelector("h1").innerHTMLf("div1 -> h1");

    auto part1_div_p_vec = part1_div.querySelectorAll("p");
    for (unsigned i = 0; i < part1_div_p_vec.size(); i++) {
        // printf() style function
        part1_div_p_vec[i].innerHTMLf("div%u -> p -> %u", i, i + 1);
    }

    /* Part 2 */
    auto part2_span_vec = document.querySelectorAll("span");
    for (unsigned i = 0; i < part2_span_vec.size(); i++) {
        part2_span_vec[i].innerHTMLf("span -> %u", i + 1);

        if (i & 1) {
            part2_span_vec[i].classNamef("%s", "text-red");
        }
    }

    return 0;
}
