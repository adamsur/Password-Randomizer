#include <iostream>
#include <ctime>
#include <string>
#include <regex>

int setLength();
std::string createPassword(int, bool, bool);
bool checkPassword(const std::string&, bool, bool);

int main()
{
    int passwordLength;
    std::string password;
    char exit;
    bool numbers = true, symbols = true, isValidPassword = false;

    passwordLength = setLength();
    
    do
    {
        password = createPassword(passwordLength, symbols, numbers);
        isValidPassword = checkPassword(password, symbols, numbers);
    }
    while (isValidPassword == false);

    std::cout << std::endl << "Random Password: " << password;
    std::cout << "\n\nPress the enter key to exit: ";
    exit = std::getchar();
    
    return 0;
}

int setLength()
{
    int length;

    while (1)
    {
        std::cout << "How long should the password be?: ";
        std::cin >> length;

        if (length >= 8 && length <= 70)
        {
            std::cin.clear(); //Clears any error states on cin stream
            std::cin.ignore(256, '\n'); //Throws away any remaining input, incase user enter extra
            break;    
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(256, '\n');
            
            std::cout << "\n\nError validating length, please use an integer for a response!";
            std::cout << std::endl << std::endl;

            continue;
        }
    }

    return length;

}

std::string createPassword(int passwordLength, bool incSpecials, bool incNumbers)
{
    int selectionNum;
    std::string character, generatedPassword = "";

    std::string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string numbers = "1234567890";
    std::string symbols = "!@#$%^&*()[]{}<>,.?';:";

    if (incSpecials == true && incNumbers == true)
    {
        letters.append(numbers);
        letters.append(symbols);
        selectionNum = letters.length();
    }
    else if (incSpecials == true && incNumbers == false)
    {
        letters.append(symbols);
        selectionNum = letters.length();
    }
    else if (incSpecials == false && incNumbers == true)
    {
        letters.append(numbers);
        selectionNum = letters.length();
    }
    else
    {
        selectionNum = letters.length();
    }

    srand(time(0));

    for (int i = 0; i <= passwordLength; i++)
    {
        character = letters[rand() % selectionNum];
        generatedPassword.append(character);
    }

    return generatedPassword;
    
}

bool checkPassword(const std::string& password, bool incSpecials, bool incNumbers)
{

    const std::regex letterExpression("[A-Za-z]");
    const std::regex numberExpression("[0-9]");
    const std::regex symbolExpression ("[^A-Za-z0-9]");

    if (!(std::regex_search(password, letterExpression)))
    {
        return false;
    }
    
    if (incNumbers == true)
    {
        if (!(std::regex_search(password, numberExpression)))
        {
            return false;
        }
    }

    if (incSpecials == true)
    {
        if (!(std::regex_search(password, symbolExpression)))
        {
            return false;
        }
    }

    return true;
}