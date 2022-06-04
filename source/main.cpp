#include <iostream>
#include "REST/RestServer.h"

int main(){
    REST::Server server("http://127.0.0.1:8080");
    server.run();
    return 0;
}