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
    /*REST::Server server(driver.address);
    server.run();*/

    SQLDriver sql(driver.port,driver.sqlAddress);
    sql.getAllProductsInformation();
    return 0;
}