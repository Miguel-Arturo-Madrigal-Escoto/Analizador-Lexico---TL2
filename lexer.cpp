#include "lexer.h"

using namespace std;

Lexer::Lexer(const string& _text): text(_text + " "), peek(' '), pos(-1), line(0) {

}

char Lexer::readCharacter() {

    this->peek = text.at(++pos);
    return peek;

}

char Lexer::readCharacterAt(const int& i) {
    return text.at(i);
}

vector<Token> Lexer::scan() {
    try {
        /// 'desechar' los caracteres vacios
        while(true){

            while (true) {
                readCharacter();

                if (this->peek == ' ' || this->peek == '\n') {
                    ///continue: ignora los espacios
                } else if (this->peek == '\n') {
                    this->line++;
                } else {
                    break;
                }
            }

            switch(peek)
            {
                case '=':
                    if ((int)readCharacterAt(pos - 1) == (int)'!' && peek == '=') {
                        ///cout << "operador: !=" << endl;
                        this->tokens.push_back(Token("relacional", "!="));
                    }
                    else if ((int)readCharacterAt(pos - 1) == (int)'<' && peek == '=') {
                        ///cout << "operador: <=" << endl;
                        this->tokens.push_back(Token("relacional", "<="));
                    }
                    else if ((int)readCharacterAt(pos - 1) == (int)'>' && peek == '=') {
                        ///cout << "operador: >=" << endl;
                        this->tokens.push_back(Token("relacional", ">="));
                    }
                    else if ((int)readCharacterAt(pos - 1) == (int)'=' && peek == '=') {
                        ///cout << "operador: ==" << endl;
                        this->tokens.push_back(Token("relacional", "=="));
                    } else if ((int)readCharacterAt(pos + 1) != (int)'='){
                        ///cout << "operador: =" << endl;
                        this->tokens.push_back(Token("asignacion", "="));
                    }
                    break;

                case '<':
                    if ((int)readCharacterAt(pos + 1) != (int)'='){
                        ///cout << "operador: <" <<endl;
                        this->tokens.push_back(Token("relacional", "<"));
                    }
                    break;

                case '>':
                    if ((int)readCharacterAt(pos + 1) != (int)'='){
                        ///cout << "operador: >" <<endl;
                        this->tokens.push_back(Token("relacional", ">"));
                    }
                    break;

                case '&':
                    if ((int)readCharacterAt(pos - 1) == (int)'&' && peek == '&') {
                        ///cout << "operador: && " << endl;
                        this->tokens.push_back(Token("logico", "&&"));
                    }
                    break;

                case '|':
                    if ((int)readCharacterAt(pos - 1) == (int)'|' && peek == '|') {
                        ///cout << "operador: || " << endl;
                        this->tokens.push_back(Token("logico", "||"));
                    }
                    break;

                ///case de operadores aritmeticos
                case '+':
                    this->tokens.push_back(Token("suma", "+"));
                    break;

                case '-':
                    this->tokens.push_back(Token("resta", "-"));
                    break;

                case '*':
                    this->tokens.push_back(Token("multiplicacion", "*"));
                    break;

                case '/':
                    this->tokens.push_back(Token("division", "/"));
                    break;

                case '{':
                    this->tokens.push_back(Token("llave apertura", "{"));
                    break;

                case '}':
                    this->tokens.push_back(Token("llave cierre", "}"));
                    break;

                case '(':
                    this->tokens.push_back(Token("parentesis apertura", "("));
                    break;

                case ')':
                    this->tokens.push_back(Token("parentesis cierre", ")"));
                    break;

                case '\"':{
                        //this->tokens.push_back(Token("comillas dobles", " \" "));
                        string str = "";
                        str += peek;

                        do {
                            readCharacter();
                            str += peek;

                        } while(peek != '\"');
                        this->tokens.push_back(Token("cadena", str));

                        break;

                    }
                case '\'':{
                    //
                    string str = ""; str += peek;

                    readCharacter(); ///leer un caracter, char debe ser longitud == 1
                    str += peek;

                    ///leer de nuevo para saber si termina con comilla simple

                    if (readCharacter() == '\''){
                        str += peek;
                        this->tokens.push_back(Token("char", str));
                    }

                    break;

                }

                case ',':
                    this->tokens.push_back(Token("coma", ","));
                    break;

                case ':':
                    this->tokens.push_back(Token("dos puntos", ":"));
                    break;

                case '.':
                cout << "punto";
                    if ((int)readCharacterAt(pos - 1) != (int)'.' && (int)readCharacterAt(pos + 1) != (int)'.'
                            && peek == '.') {
                        this->tokens.push_back(Token("punto", "."));
                    }
                    break;

                ///separador de lenguaje: ;
                case ';':
                    this->tokens.push_back(Token("separador", ";"));
                    break;

            }

            ///comprobar si es digito el peek
            string strNumber = "";
            if(isdigit(peek)) {
                strNumber += peek;
                ///do - while para obtener todos los digitos
                do {
                    ///leer otro caracter
                    //cout << peek << endl;

                    readCharacter();
                    strNumber += peek;

                } while (isdigit(peek));

                /// si el peek NO quedo en . , entonces es entero
                if (peek != '.') {
                    string aux = "";
                    for(size_t i(0); i < strNumber.length() - 1; i++){
                        aux += strNumber.at(i);
                    }
                    this->tokens.push_back(Token("entero", aux));
                } else {

                    ///digitos de la derecha de la parte flotante

                    do {
                        readCharacter();
                        strNumber += peek;

                    } while (isdigit(peek));

                    ///cout << "real: " << strNumber << endl;


                    ///sanitizar data
                    string aux = "";
                    for(size_t i(0); i < strNumber.length(); i++) {
                        if (isdigit(strNumber.at(i)) || strNumber.at(i) == '.'){
                            aux += strNumber.at(i);
                        }
                    }

                    ///ver el correcto formato
                    if(regex_match(aux, regex("^[0-9]*.[0-9]+$"))) {
                        this->tokens.push_back(Token("real", aux));
                    }

                }
                ///regresar 1 por el que se salto
                this->pos--;
            }

            ///si es letra
            else if (isalpha(peek)){
                string str = "";
                do {
                    str += peek;
                    readCharacter();
                } while (isalpha(peek) || isdigit(peek));

                ///regresar 1 por el que se salto
                this->pos--;

                ///agregar a los tokens
                Token token = inKeywords(str);

                this->tokens.push_back(token);

            }

        }
    } catch(...){
        cout << "El analisis lexico ha terminado" << endl;
        cout << "Tokens: " << endl;
        for(size_t i(0); i < tokens.size(); i++) {
            cout << tokens.at(i).toString() << endl;

        }
    }

    return tokens;
}

Token Lexer::inKeywords(const string& value) {
    ///ver si value esta en las palabras reservadas
    if (find(keywords.begin(), keywords.end(), value) != keywords.end()){
        if (value == "if" || value == "else") {
            return Token("condicional", value);
        }
        else if (value == "true" || value == "false"){
            return Token("booleano", value);
        }
        else if (value == "do" || value == "while" || value == "break"
                 || value == "int" || value == "float" || value == "string"
                 || value == "char" || value == "boolean" || value == "print"
                 || value == "return" || value == "for") {
            return Token("reservada", value);
        }
    }
    else {
        return Token("Identificador", value);
    }
}







