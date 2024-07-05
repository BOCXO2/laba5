#pragma once

#include <regex>
#include <string>
class MyValidator {
public:
    MyValidator() {};

    bool validate_login(std::string& login) const
    {
        // ќпредел€ем регул€рное выражение дл€ проверки входных данных
        std::regex reg("^[a-z0-9_]{5,15}$");
        

        // ≈сли входные данные соответствуют регул€рному выражению, валидатор возвращает Acceptable
        return std::regex_match(login, reg);
            
        // ≈сли входные данные не соответствуют регул€рному выражению, валидатор возвращает Invalid
        
    }
    bool validate_pass(std::string& password) const
    {

        std::regex re("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[a-zA-Z\\d]{8}$$");
        return std::regex_match(password, re);
    }
        };

