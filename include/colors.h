#pragma once
#include <string>

// =============================================================
// ANSI Color Code Constants for Console Output
// =============================================================
// Use these constants instead of raw escape sequences.
// Example: cout << COLOR_GREEN << "Success!" << COLOR_RESET;
// =============================================================

const std::string COLOR_RESET     = "\033[0m";       // Reset all attributes
const std::string COLOR_RED       = "\033[31m";      // Error / not available
const std::string COLOR_GREEN     = "\033[32m";      // Success / available
const std::string COLOR_YELLOW    = "\033[33m";      // Prompt / input labels
const std::string COLOR_BOLD_RED  = "\033[1;31m";    // Critical error / invalid choice
