#include "DisplayOptions.h"

void UserSelection::displayProductSearchOptions() {
    std::cout << "1) Search by Id" << '\n';
    std::cout << "2) Search by Name" << '\n';
    std::cout << "3) Search by Category" << '\n';
    std::cout << "4) Search by Price" << '\n';
    std::cout << "5) Search by Stock" << '\n';
    std::cout << "6) Search by Inventory Value" << '\n';
}

void UserSelection::displayProductUpdateOptions() {
    std::cout << "1) Update Name" << '\n';
    std::cout << "2) Update Category" << '\n';
    std::cout << "3) Update Price" << '\n';
    std::cout << "4) Update Stock" << '\n';
    std::cout << "5) Update All" << '\n';
}

void UserSelection::displayProductRemoveOptions() {
    std::cout << "Are you sure you want to remove this product?" << '\n';
    std::cout << "1) Yes" << '\n';
    std::cout << "2) No" << '\n';
}

void UserSelection::displaySaveModeOptions() {
    std::cout << "1) Save to New File" << '\n';
    std::cout << "2) Save To Internal File" << '\n';
}

void UserSelection::displayFileExtensionOptions() {
    std::cout << "1) Txt Extension" << '\n';
    std::cout << "2) Csv Extension" << '\n';
}