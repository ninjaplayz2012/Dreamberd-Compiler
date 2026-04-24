#include "Configs.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path>" << std::endl;
        return 1;
    }
    
    string InputPath = argv[1];
    std::filesystem::path FullPath;
    
    try {
        FullPath = std::filesystem::absolute(InputPath);
    } catch (const std::filesystem::filesystem_error& Error) {
        std::cerr << "Error processing path: " << Error.what() << "\n";
        return 1;
    }
    
    std::ifstream File67(FullPath);
    std::stringstream Buffer;
    Buffer << File67.rdbuf();
    
    string Data = Buffer.str();
    Lexer Like16(Data);
    
    vector<Token<string>> ReturnedTokens = Like16.Tokenize();
    
    for (auto& ReturnedToken : ReturnedTokens) {
        std::cout << ReturnedToken;
    }
    
    return 0;
}