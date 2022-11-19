#ifndef USER_H
#define USER_H
#include <iostream>
#include <map>

class User
{
public:
    User();

    bool isLoggedIn;
    
    // user basic details
    
    std::string firstName;
    std::string lastName;
    std::string email;
    std::string dateOfBirth;
    std::string NHI;
    int userID;

    std::map<std::string, std::string> vaccineRecord;
    std::map<std::string, std::string> testResults;

    bool admin;

    void createUser(std::string firstName, std::string lastName, std::string email, std::string password, std::string dateOfBirth, std::string NHI, bool admin);
    bool loginUser(std::string email, std::string password, bool admin);

    void addVaccine(std::string vaccineName, std::string date);
    void addTestResult(std::string date, bool result);

    ~User();
    void logoutUser();

private:
    std::string password;

};

#endif // USER_H
