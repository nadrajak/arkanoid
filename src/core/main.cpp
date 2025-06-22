#include "core/CApplication.h"

#include <iostream>


int main()
{
    try {
        return CApplication(16, "assets/scoreboard").Run();
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
}
