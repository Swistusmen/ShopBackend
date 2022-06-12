#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <tuple>

namespace Parser{
static constexpr int defaultPortNumber{3306};
static const std::string defaultAddress{"http://127.0.0.1:8080"};
static const std::string defaultSQLServerAddress{"http://127.0.0.1"};

enum class ParserResult{
    RUN,
    EXIT,
};

struct ProgramDriver{
    int port{defaultPortNumber};
    std::string address{defaultAddress};
    std::string sqlAddress{defaultSQLServerAddress};
    ParserResult result{ParserResult::EXIT};
};

static void parseArguments(const int argc,char* argv[],std::vector<std::array<std::string,2>>& args)
{
    for(int i=1;i<argc;i+=2){
        
        const std::string key(argv[i]);
        std::string value{""};
        if(i+1<argc){
            value=argv[i+1];
        }
        args.emplace_back(std::array<std::string,2>{key,value});
    }
}

static ProgramDriver processInputArguments(int argc,char* argv[]){
    ProgramDriver driver;
    if (argc==1){
        printf("Using 3306\n");
        return driver;
    }
    std::vector<std::array<std::string,2>> arguments;
    
    parseArguments(argc,argv,arguments);

    auto findKey=[&arguments](const auto& keyValue){
        auto founded=std::find_if(arguments.begin(),arguments.end(),[&keyValue](const auto& pair){
            return pair[0]==keyValue;
        });
        if(founded!=arguments.end()){
            return static_cast<int>(founded-arguments.begin());
        }
        return -1;
    };

    int key{-1};
    if((key=findKey("--h"))!=-1){
        printf("--h help /n --a http address together with port.You can reach this app under this address /n --p port to hit to get to db \n");
        return driver;
    }

    if((key=findKey("--p"))!=-1){
        if(arguments.at(key).size()!=2){
            printf("--p bad argument error\n");
            return driver;
        }
        try{
        driver.port=std::stoi(arguments.at(key).at(1));
        }catch(const std::exception& e){
            printf("Error, bad port given\n");
            return driver;
        }
    }
    if((key=findKey("--a"))!=-1){
        if(arguments.at(key).size()!=2){
            printf("--a bad argument error\n");
            return driver;
        }
        driver.address=arguments.at(key).at(1);
    }
    if((key=findKey("--sql"))!=-1){
        if(arguments.at(key).size()!=2){
            printf("--sql bad argument error\n");
            return driver;
        }
        driver.sqlAddress=arguments.at(key).at(1);
    }
    
    printf("Running on: %s | database connection on port %d \n",driver.address.c_str(),driver.port);
    driver.result=ParserResult::RUN;
    return driver;
}
}