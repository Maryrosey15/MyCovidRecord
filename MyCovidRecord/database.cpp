#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QFile>
#include "database.h"
#include <iostream>

database::database()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
}


void database::databaseConnect() {
    // sqlite database using qt
    // the database is stored in a local file "userRecords.db"
    // the database is created if it doesn't exist

    // create a database object
    

    // check if the file exists on the system
    // if the file exists, open the database
    // if the file doesn't exist, create the database
    if (QFile::exists("userRecords.db")) {

        db.setDatabaseName("userRecords.db");

        if (!db.open()) {
            std::cout << "Error: connection with database fail";
        }
        else {
            std::cout << "Database: connection ok";
        }
        return;
    }

    // if doesn't exist we setup database with tables and example data
    QSqlQuery query;

    db.setDatabaseName("userRecords.db");
    db.open();

    query.exec("CREATE TABLE IF NOT EXISTS user (id INTEGER PRIMARY KEY AUTOINCREMENT, firstName VARCHAR(20), lastName VARCHAR(20), email VARCHAR(60), password VARCHAR(20), dateOfBirth VARCHAR(20), NHI VARCHAR(20), admin INTEGER, status VARCHAR(20))");
    query.exec("CREATE TABLE IF NOT EXISTS vaccine (id INTEGER PRIMARY KEY AUTOINCREMENT, userID INTEGER, vaccineName VARCHAR(20), date VARCHAR(20))");
    query.exec("CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY AUTOINCREMENT, userID INTEGER, date VARCHAR(20), result VARCHAR(20))");
    query.exec("CREATE TABLE IF NOT EXISTS issues (id INTEGER PRIMARY KEY AUTOINCREMENT, issueReportText TEXT)");

    // insert test data
    query.exec("INSERT INTO user (firstName, lastName, email, password, dateOfBirth, NHI, admin, status) VALUES ('Admin', 'Smith', 'admin@website.com', 'password', '01/01/2000', '', 1, 'Completed')");
    
    query.exec("INSERT INTO user (firstName, lastName, email, password, dateOfBirth, NHI, admin, status) VALUES ('John', 'Smith', 'johnsmith@gmail.com', 'password', '01/01/2000', 'ABCD1234', 0, 'Partial')");
    query.exec("INSERT INTO vaccine (userID, vaccineName, date) VALUES (1, 'First Dose', '01/01/2021')");
    query.exec("INSERT INTO vaccine (userID, vaccineName, date) VALUES (1, 'Second Dose', '01/02/2021')");
    query.exec("INSERT INTO test (userID, date, result) VALUES (1, '01/01/2021', 'Positive')");
    query.exec("INSERT INTO test (userID, date, result) VALUES (1, '01/02/2021', 'Negative')");

    query.exec("INSERT INTO user (firstName, lastName, email, password, dateOfBirth, NHI, admin, status) VALUES ('Dylan', 'Smith', 'dsmith@gmail.com', 'password', '05/02/1988', 'ABCD1234', 0, 'Unvaccinated')");
    query.exec("INSERT INTO vaccine (userID, vaccineName, date) VALUES (2, 'First Dose', '06/01/2021')");
    query.exec("INSERT INTO vaccine (userID, vaccineName, date) VALUES (2, 'Second Dose', '05/02/2021')");
    query.exec("INSERT INTO vaccine (userID, vaccineName, date) VALUES (2, 'Booster 1', '16/04/2021')");
    query.exec("INSERT INTO vaccine (userID, vaccineName, date) VALUES (2, 'Booster 2', '16/05/2021')");
    query.exec("INSERT INTO test (userID, date, result) VALUES (2, '01/01/2021', 'Positive')");
    query.exec("INSERT INTO test (userID, date, result) VALUES (2, '01/02/2021', 'Negative')");

    query.exec("INSERT INTO issues (issueReportText) VALUES ('Button on main screen not working')");
}

void database::databaseDisconnect() {
    db.close();
}

void database::addUser(std::string firstName, std::string lastName, std::string email, std::string password, std::string dateOfBirth, std::string NHI, bool admin) {
    QSqlQuery query;
    query.prepare("INSERT INTO user (firstName, lastName, email, password, dateOfBirth, NHI, admin) VALUES (:firstName, :lastName, :email, :password, :dateOfBirth, :NHI, :admin)");
    query.bindValue(":firstName", QString::fromStdString(firstName));
    query.bindValue(":lastName", QString::fromStdString(lastName));
    query.bindValue(":email", QString::fromStdString(email));
    query.bindValue(":password", QString::fromStdString(password));
    query.bindValue(":dateOfBirth", QString::fromStdString(dateOfBirth));
    query.bindValue(":NHI", QString::fromStdString(NHI));
    query.bindValue(":admin", admin);
    query.exec();
}

void database::addVaccine(int userID, std::string vaccineName, std::string date) {
    QSqlQuery query;
    query.prepare("INSERT INTO vaccine (userID, vaccineName, date) VALUES (:userID, :vaccineName, :date)");
    query.bindValue(":userID", userID);
    query.bindValue(":vaccineName", QString::fromStdString(vaccineName));
    query.bindValue(":date", QString::fromStdString(date));
    query.exec();
}

void database::addTest(int userID, std::string date, std::string result) {
    QSqlQuery query;
    query.prepare("INSERT INTO test (userID, date, result) VALUES (:userID, :date, :result)");
    query.bindValue(":userID", userID);
    query.bindValue(":date", QString::fromStdString(date));
    query.bindValue(":result", QString::fromStdString(result));
    query.exec();
}

std::vector<std::string> database::adminSearchNHI(std::string NHI) {
    QSqlQuery query;
    query.prepare("SELECT id FROM user WHERE NHI = :NHI");
    query.bindValue(":NHI", QString::fromStdString(NHI));
    query.exec();
    query.next();
    
    // if no user found
    if (query.value(0).isNull()) {
        std::vector<std::string> empty;
        return empty;
    }

    return getUserDetails(query.value(0).toInt());
}

void database::changeUserStatus(int userID, std::string status) {
    QSqlQuery query;
    query.prepare("UPDATE user SET status = :status WHERE id = :userID");
    query.bindValue(":status", QString::fromStdString(status));
    query.bindValue(":userID", userID);
    query.exec();
}

int database::checkUser(std::string email, std::string password) {
    // returns userID if user exists else returns -1
    QSqlQuery query;
    query.prepare("SELECT * FROM user WHERE email = :email AND password = :password");
    query.bindValue(":email", QString::fromStdString(email));
    query.bindValue(":password", QString::fromStdString(password));
    query.exec();
    if (query.next()) {
        // user exists
        return query.value(0).toInt();
    }
    else {
        // user does not exist
        return -1;
    }
}

int database::checkAdmin(std::string email, std::string password) {
    // returns adminId if admin exists else returns -1
    QSqlQuery query;
    query.prepare("SELECT * FROM user WHERE email = :email AND password = :password AND admin = 1");
    query.bindValue(":email", QString::fromStdString(email));
    query.bindValue(":password", QString::fromStdString(password));
    query.exec();
    if (query.next()) {
        // admin exists
        return query.value(0).toInt();
    }
    else {
        // admin does not exist
        return -1;
    }
}


std::vector<std::string> database::getUserDetails(int userID) {
    QSqlQuery query;
    query.prepare("SELECT * FROM user WHERE id = :userID");
    query.bindValue(":userID", userID);
    query.exec();

    // return user data
    std::vector<std::string> user;
    if (query.next()) {
        for (int i = 0; i < query.record().count(); i++) {
            user.push_back(query.value(i).toString().toStdString());
        }

    }
    return user;
}

std::map<std::string, std::string> database::getVaccineRecord(int userID) {
    QSqlQuery query;
    query.prepare("SELECT * FROM vaccine WHERE userID = :userID");
    query.bindValue(":userID", userID);
    query.exec();

    // return vaccine data
    std::map<std::string, std::string> vaccineRecord;
    while (query.next()) {
        vaccineRecord[query.value(2).toString().toStdString()] = query.value(3).toString().toStdString();
    }
    return vaccineRecord;
}

std::map<std::string, std::string> database::getTestRecord(int userID) {
    QSqlQuery query;
    query.prepare("SELECT * FROM test WHERE userID = :userID");
    query.bindValue(":userID", userID);
    query.exec();

    // return test data
    std::map<std::string, std::string> testRecord;
    while (query.next()) {
        testRecord[query.value(2).toString().toStdString()] = query.value(3).toString().toStdString();
    }
    return testRecord;
}

std::vector<std::string> database::getIssueReports() {
    QSqlQuery query;
    query.prepare("SELECT * FROM issues");
    query.exec();

    // return issue reports
    std::vector<std::string> issueReports;
    while (query.next()) {
        issueReports.push_back(query.value(1).toString().toStdString());
    }
    return issueReports;
}

void database::addIssueReport(std::string issue) {
    QSqlQuery query;
    query.prepare("INSERT INTO issues (issueReportText) VALUES (:issue)");
    query.bindValue(":issue", QString::fromStdString(issue));
    query.exec();
}
