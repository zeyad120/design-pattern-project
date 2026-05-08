#include "LibraryManager.h"

// Initialization of static members
LibraryManager* LibraryManager::instance = nullptr;
std::mutex LibraryManager::mutex;
