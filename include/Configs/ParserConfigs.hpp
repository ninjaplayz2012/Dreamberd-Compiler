#pragma once

#include <memory>
#include <vector>
#include <string>
#include <stdexcept>
#include <variant>
#include "Headers/Tokens.h"

using std::vector;
using std::string;
using std::unique_ptr;
using std::make_unique;
using VariableValue = std::variant<int, double, string, bool>;