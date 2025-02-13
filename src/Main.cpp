#include "App/InventoryManagementSystemApp.h"

void main() {
    try {
        InventoryManagementSystem{}.Run();
    }
    catch (const std::exception& ex) {
        std::cout << "We're sorry, but it seems that the program encountered an unexpected issue. " <<
            "The program will now close. Error: " << ex.what();
    }
}


