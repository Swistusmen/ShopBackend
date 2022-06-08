#include "SQLDriver.h"


SQLDriver::SQLDriver(const int _port, const std::string& _address):communicationManager(_address,_port){}

//{"products":["apples":1,"bananas":10]}
web::json::value SQLDriver::getAllProductsInformation()
{
    auto response=communicationManager.make_request("select * from products");
    while(response.finished()){
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    //wait till response is ready
}

//{"product":"apple","quantity":9,"price":2.99}
web::json::value SQLDriver::getProductData(const int _id)
{
    auto response=communicationManager.make_request("select * from products where id = "+std::to_string(_id));
    while(response.finished()){
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

bool SQLDriver::updateData(std::vector<std::array<std::string,2>>& args, const int _id)
{
    return false;
}

