#pragma once
#include "CommunicationManager.h"
#include <cpprest/json.h>
#include <thread>
#include <string>

/*
Assumptions:
    1.Program knows the size of entity in sql row- I use my own implementation of SQL DB,so that i know what the size is
*/

class SQLDriver{
public:
    SQLDriver(const int _port, const std::string& _address);

    web::json::value getAllProductsInformation();
    //{"products":["apples":1,"bananas":10]}
    web::json::value getProductData(const std::string& _id);
    //{"product":"apple","quantity":9,"price":2.99}
    bool updateData(std::vector<std::array<std::string,2>>& args, const int _id);
private:
    CommunicationManager communicationManager;
    static constexpr int productTableEntitySize{4};

private:
    std::vector<std::vector<std::string>> decodeSQLMessage(const std::string& ,const int);
    std::vector<std::string> splitString(const std::string& arg,char splitter);
    web::json::value mapTableToJSON(const std::vector<std::vector<std::string>>&,const std::vector<std::string>&);
    web::json::value createJSONTableOfProducts(const std::vector<std::vector<std::string>>&);
};