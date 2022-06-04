#include "RestServer.h"

namespace REST{

void display_json(
   json::value const & jvalue,
   utility::string_t const & prefix)
{
   std::cout << prefix << jvalue.serialize() << std::endl;
}

void handle_get(http_request request){
    std::cout<<L"\nhandle GET\n";

   auto answer = json::value::object();

/*
   for (auto const & p : dictionary)
   {
      answer[p.first] = json::value::string(p.second);
   }

   display_json(json::value::null(), L"R: ");
   display_json(answer, L"S: ");
   */
  
  display_json(answer, "S: ");
   request.reply(status_codes::OK, answer);
}

//SERVER
Server::Server(const std::string& _addrress):listener(_addrress){
    listener.support(methods::GET, handle_get);
}

void Server::run(){
    try
   {
      listener
         .open()
         .then([this]() { std::cout<<"Starting to listen\n";})
         .wait();

      while (true);
   }
   catch (std::exception const & e)
   {
      std::cout<< e.what() << std::endl;
   }
}
}