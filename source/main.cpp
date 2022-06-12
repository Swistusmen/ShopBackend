#include <iostream>
#include "REST/RestServer.h"
#include "Parser/Parser.h"
#include "SQLDriver/SQLDriver.h"

int main(int argc, char *argv[])
{
    const auto driver = Parser::processInputArguments(argc, argv);
    REST::Server server(driver.address);
    server.run();
    return 0;
}