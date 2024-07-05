#ifndef VALIDATOR_H
#define VALIDATOR_H
#include <QValidator>
#include <QRegularExpression>

class MyValidator {
public:
    MyValidator() {};

    QValidator::State validate(QString& input) const
    {
        // Определяем регулярное выражение для проверки входных данных
        QRegularExpression regex("^[a-z0-9_]{5,15}$");
        QRegularExpressionMatch match = regex.match(input);

        // Если входные данные соответствуют регулярному выражению, валидатор возвращает Acceptable
        if (match.hasMatch()) {
            return QValidator::Acceptable;
        }
        // Если входные данные не соответствуют регулярному выражению, валидатор возвращает Invalid
        else {

            return QValidator::Invalid;
        }
    }
    QValidator::State validate_pass(QString& input) const
    {
        // Определяем регулярное выражение для проверки входных данных
        QRegularExpression regex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[a-zA-Z\\d]{8}$$");
        QRegularExpressionMatch match = regex.match(input);

        // Если входные данные соответствуют регулярному выражению, валидатор возвращает Acceptable
        if (match.hasMatch()) {
            return QValidator::Acceptable;
        }
        // Если входные данные не соответствуют регулярному выражению, валидатор возвращает Invalid
        else {

            return QValidator::Invalid;
        }
    }

};
#endif // VALIDATOR_H
