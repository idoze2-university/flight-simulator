#include "parser.h"
double Parser::parseValue(string expression)
{
    try
    {
        return stoi(expression);
    }
    catch (const std::exception &e)
    {
        cout << "Cannot evaluate \'" << expression << "\'" << endl;
        return 0;
    }
}