#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED

#include <string>
#include <map>
#include <vector>
#include <regex>

#include <iostream>
#include <string>
#include <algorithm>

///token
#include "token.h"

class Lexer {
    private:
        ///palabras reservadas del lenguaje
        std::vector<std::string> keywords{
                                    "if", "else", "true", "false",
                                    "do", "while", "break", "int",
                                    "float", "string", "char", "boolean",
                                    "print", "return", "for"
                                };

        ///tokens encontrados
        std::vector<Token> tokens;

        ///texto a analizar
        std::string text;

        ///caracter analizado
        char peek;

        ///posicion leida
        int pos;

        ///linea actual
        int line;

    public:
        /// almacenar los tokens
        Lexer(const std::string&);

        char readCharacter();
        char readCharacterAt(const int&);

        std::vector<Token> scan();

        Token inKeywords(const std::string&);
};

#endif // LEXER_H_INCLUDED
