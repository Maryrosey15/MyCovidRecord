#include "user.h"
//#include "mainwindow.h"
#include <iostream>
#include <QMessageBox>

User::User()
{
    isLoggedIn = false;
    db = new database();
}

// method to create a new user
void User::createUser(std::string firstName, std::string lastName, std::string email, std::string password, std::string dateOfBirth, std::string NHI, bool admin) {

//    this->firstName = firstName;
//    this->lastName = lastName;
//    this->email = email;
//    this->password = password;
//    this->dateOfBirth = dateOfBirth;
//    this->NHI = NHI;
//    this->admin = admin;

    // store user details in database
    
    db->databaseConnect();
    db->addUser(firstName, lastName, email, password, dateOfBirth, NHI, admin);
    
    this->isLoggedIn = true;
    db->databaseDisconnect();

    loginUser(email, password, admin);

}

bool User::loginUser(std::string email, std::string password, bool admin) {
    db->databaseConnect();
    if (admin) {
        userID = db->checkAdmin(email, password);
    } else {
        userID = db->checkUser(email, password);
    }

    if (userID != -1) {
        this->isLoggedIn = true;
        this->email = email;
        std::vector<std::string> userDetails = db->getUserDetails(userID);
        this->firstName = userDetails[1];
        this->lastName = userDetails[2];
        this->dateOfBirth = userDetails[5];
        this->NHI = userDetails[6];
        this->admin = userDetails[7] == "1" ? true : false;
        this->status = userDetails[8];

        this->vaccineRecord = db->getVaccineRecord(userID);
        this->testResults = db->getTestRecord(userID);

        return true;
    } else {
        QMessageBox::warning(nullptr, "Login Failed", "Incorrect email or password");
        this->isLoggedIn = false;
        return false;
    }

    db->databaseDisconnect();
    
}

void User::addVaccine(std::string vaccineName, std::string date) {
    vaccineRecord[vaccineName] = date;
}

void User::addTestResult(std::string date, bool result) {
    testResults[date] = result;
}

void User::logoutUser() {
//    this->isLoggedIn = false;
}

User::~User()
{
}
