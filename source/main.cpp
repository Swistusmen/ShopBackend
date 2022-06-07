#include <iostream>
#include "REST/RestServer.h"
#include "Parser/Parser.h"

int main(int argc,char*argv[]){
    auto args=Parser::processInputArguments(argc,argv);
    REST::Server server("http://127.0.0.1:8080");
    server.run();
    return 0;
}