#pragma once
#include "CommunicationManager.h"

class SQLDriver{
public:
    SQLDriver(const int _port, const std::string& _address);

    void getAllProductsInformation();
    void getProductData(const int _id);
    void updateData(std::vector<std::array<std::string,2>>& args, const int _id);
private:
    CommunicationManager CommunicationManager;
};