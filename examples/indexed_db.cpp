#include <indexed_db.hpp>

int main() {
    auto request = indexedDB.open("Local-DB", 1);
    return 0;
}
