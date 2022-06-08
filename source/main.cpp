#include <iostream>
#include "REST/RestServer.h"
#include "Parser/Parser.h"

int main(int argc, char *argv[])
{
    auto args = Parser::processInputArguments(argc, argv);
    REST::Server server(std::get<2>(args));
    server.run();
    return 0;
}