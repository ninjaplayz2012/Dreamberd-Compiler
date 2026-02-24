#pragma once

#include <string>
#include <vector>
#include <array>
#include "Tokens.h"


class Lexer {
    Token TextToToken(std::string Text);
};

class Token {
    Tokens Id;
    double Value;
    std::string Name;
};

