#pragma once

#include <regex>
#include <string>
class MyValidator {
public:
    MyValidator() {};

    bool validate_login(std::string& login) const
    {
        // ���������� ���������� ��������� ��� �������� ������� ������
        std::regex reg("^[a-z0-9_]{5,15}$");
        

        // ���� ������� ������ ������������� ����������� ���������, ��������� ���������� Acceptable
        return std::regex_match(login, reg);
            
        // ���� ������� ������ �� ������������� ����������� ���������, ��������� ���������� Invalid
        
    }
    bool validate_pass(std::string& password) const
    {

        std::regex re("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[a-zA-Z\\d]{8}$$");
        return std::regex_match(password, re);
    }
        };

