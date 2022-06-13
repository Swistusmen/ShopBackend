#include <iostream>
#include "REST/RestServer.h"
#include "Parser/Parser.h"
#include "SQLDriver/SQLDriver.h"

//TODO:
/*
1. check simple sql question
2. write json get-> sql action
*/

int main(int argc, char *argv[])
{
    const auto driver = Parser::processInputArguments(argc, argv);
    SQLDriver sql(driver.port,driver.sqlAddress);
    REST::Server server(driver.address,sql);
    server.run();

    return 0;
}