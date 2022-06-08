#pragma once
#include "CommunicationManager.h"
#include <cpprest/json.h>
#include <thread>

class SQLDriver{
public:
    SQLDriver(const int _port, const std::string& _address);

    web::json::value getAllProductsInformation();
    //{"products":["apples":1,"bananas":10]}
    web::json::value getProductData(const int _id);
    //{"product":"apple","quantity":9,"price":2.99}
    bool updateData(std::vector<std::array<std::string,2>>& args, const int _id);
private:
    CommunicationManager communicationManager;
};