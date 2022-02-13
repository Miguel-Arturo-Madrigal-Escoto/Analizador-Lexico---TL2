#include "token.h"

using namespace std;

std::string Token::getType()
{
    return type;
}

void Token::setType(const std::string &value)
{
    type = value;
}

std::string Token::getToken()
{
    return token;
}

void Token::setToken(const std::string &value)
{
    token = value;
}

Token::Token(const string& type, const string& value){
    this->type = type;
    this->token = value;
}

string Token::toString(){
    return ("tipo: " + type + ", valor: " + token);

}
