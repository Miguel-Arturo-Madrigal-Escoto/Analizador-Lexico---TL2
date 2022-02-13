#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

#include <string>

class Token{
    private:
        std::string type;
        std::string token;

    public:
        Token(const std::string&, const std::string&);

        std::string toString();

        std::string getType();
        void setType(const std::string &value);

        std::string getToken();
        void setToken(const std::string &value);
};

#endif // TOKEN_H_INCLUDED
