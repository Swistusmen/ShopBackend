#pragma once

#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include "../SQLDriver/SQLDriver.h"
#include <tuple>

namespace REST
{
    using namespace web;
    using namespace web::http;
    using namespace web::http::experimental::listener;

    void handle_post(http_request request);
    void display_json(json::value const &jvalue, utility::string_t const &prefix);

    struct Order{
        Order(const std::string& _name,int _quantity):name(_name),quantity(_quantity){}
        std::string name{""};
        int quantity{0};
        bool succesfullyUpdated{false};
    };

    class Server
    {
    public:
        Server(const std::string &_addrress, SQLDriver& );

        void run();
        void a(http_request request);

    private:
        http_listener listener;
        SQLDriver& driver;
    };

}