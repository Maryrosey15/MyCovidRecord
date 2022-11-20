#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <QSqlDatabase>
#include <map>

class database
{
public:
    QSqlDatabase db;
    database();
    void databaseConnect();
    void databaseDisconnect();

    void addUser(std::string firstName, std::string lastName, std::string email, std::string password, std::string dateOfBirth, std::string NHI, bool admin);
    void addVaccine(int userID, std::string vaccineName, std::string date);
    void addTest(int userID, std::string date, std::string result);

    int checkUser(std::string email, std::string password);
    int checkAdmin(std::string email, std::string password);

    std::vector<std::string> getUserDetails(int userID);
    std::map<std::string, std::string> getVaccineRecord(int userID);
    std::map<std::string, std::string> getTestRecord(int userID);

    std::vector<std::string> adminSearchNHI(std::string NHI);
    void changeUserStatus(int userID, std::string status);

    std::vector<std::string> getIssueReports();
    void addIssueReport(std::string issueReport);
};

#endif // DATABASE_H
