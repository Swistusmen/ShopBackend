#pragma once

#include <cpprest/http_listener.h>
#include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

namespace REST{

void handle_get(http_request request);
void handle_post(http_request request);
void display_json(json::value const & jvalue,utility::string_t const & prefix);

class Server{
    public:
        Server(const std::string& _addrress);

        void run();
    private:
        http_listener listener;
};

}