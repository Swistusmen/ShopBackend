#include "SQLDriver.h"


SQLDriver::SQLDriver(const int _port, const std::string& _address):communicationManager(_address,_port){}

//{"products":["apples":1,"bananas":10]}
web::json::value SQLDriver::getAllProductsInformation()
{
    auto response=communicationManager.make_request("select id, name, quantitiy from products");
    while(response.finished()){
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    const auto table=decodeSQLMessage(response.getResponse().value(),2);
   return createJSONTableOfProducts(table);
}

//{"product":"apple","quantity":9,"price":2.99}
web::json::value SQLDriver::getProductData(const int _id)
{
    auto response=communicationManager.make_request("select name, quantity, price from products where id = "+std::to_string(_id));
    while(response.finished()){
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    const auto table=decodeSQLMessage(response.getResponse().value(),3);
    return mapTableToJSON(table,{"product","quantity","price"});
}

bool SQLDriver::updateData(std::vector<std::array<std::string,2>>& args, const int _id)
{
    return false;
}

std::vector<std::vector<std::string>> SQLDriver::decodeSQLMessage(const std::string& message,const int rowSize)
{
    const auto words=splitString(message,' ');
    std::vector<std::vector<std::string>>table;
    if(words.size()%productTableEntitySize!=0){
        const int noEntities{words.size()/rowSize};
        for(int i=0;i<noEntities;i++){
            table.push_back({});
            table.back().insert(table.back().end(),words.begin()+i*rowSize,words.begin()+(i+1)*rowSize);
        }
    }
    return table;
}

std::vector<std::string> SQLDriver::splitString(const std::string& arg,char splitter){
    std::vector<std::string> result;
    result.push_back("");
    for(const auto& it: arg){
        if(it!=splitter){
            result.back()+=it;
        }else{
            result.push_back("");
        }
    }
    if(result.back()==""){
        result.pop_back();
    }
    return result;
}

web::json::value SQLDriver::mapTableToJSON(const std::vector<std::vector<std::string>>& table,const std::vector<std::string>& labels)
{
    auto myJson=web::json::value::object();
    if(!table.empty()&&table.at(0).size()==labels.size()){
        for(int i=0;i<table[0].size();i++){
            std::string val=table[0][i];
            myJson[labels[i].c_str()]=web::json::value::string(val);
        }
    }
    return myJson;
}

web::json::value SQLDriver::createJSONTableOfProducts(const std::vector<std::vector<std::string>>& table)
{
    auto myJson=web::json::value::object();
    std::vector<web::json::value> products;
    if(!table.empty()){
        for(int i=0;i<table.size();i++){
        auto buffer=web::json::value::object();
        buffer[table[i][0]]=web::json::value::string(table[i][1]);
        products.push_back(buffer);
        }
        myJson["products"]=web::json::value::array(products);
    }
    return myJson;
}


