#include "RestServer.h"

namespace REST{

void display_json(
   json::value const & jvalue,
   utility::string_t const & prefix)
{
   std::cout << prefix << jvalue.serialize() << std::endl;
}

void handle_get(http_request request){
    std::wcout<<L"\nhandle GET\n";

   auto answer = json::value::object();
   auto a=request.relative_uri();

    /*
    TODO:
    -handle this:
    -just get returns whole list of products
    -get /product gets the information about the product
    -else / error
    */
   std::wstring o1=std::wstring(a.path().begin(),a.path().end());
   std::wcout<<o1<<std::endl;

    display_json(answer, "S: ");
   request.reply(status_codes::OK, answer);
}

void handle_post(http_request request){
    std::wcout<<L"\nhandle POST\n";

    auto answer=json::value::object();
    request.extract_json().then([&answer](pplx::task<json::value> task){

    }).wait();

    request.reply(status_codes::OK,answer);
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
         .then([this]() { std::wcout<<"Starting to listen\n";})
         .wait();

      while (true);
   }
   catch (std::exception const & e)
   {
      std::cout<< e.what() << std::endl;
   }
}
}