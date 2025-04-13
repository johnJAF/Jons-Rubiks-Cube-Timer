#include "DataManager.h"


// time_t timestamp = time(NULL);
//   struct tm datetime = *localtime(&timestamp);

//   char output[50];

// strftime(output, 50, "%m/%d/%y", &datetime);
// cout << output << "\n";

void DataManager::createDataDirectories() {
    // Base data directory
    fs::path base = "../Data";

    // Define all necessary subdirectories
    fs::path algorithms = base / "Algorithms";
    fs::path oll = algorithms / "OLL";
    fs::path pll = algorithms / "PLL";
    fs::path sessions = base / "Sessions";

    // Create directories if they do not exist
    try {
        if (!fs::exists(base)) {
            fs::create_directory(base);
            std::cout << "Created: " << base << std::endl;
        }
        if (!fs::exists(algorithms)) {
            fs::create_directory(algorithms);
            std::cout << "Created: " << algorithms << std::endl;
        }
        if (!fs::exists(oll)) {
            fs::create_directory(oll);
            std::cout << "Created: " << oll << std::endl;
        }
        if (!fs::exists(pll)) {
            fs::create_directory(pll);
            std::cout << "Created: " << pll << std::endl;
        }
        if (!fs::exists(sessions)) {
            fs::create_directory(sessions);
            std::cout << "Created: " << sessions << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }
}