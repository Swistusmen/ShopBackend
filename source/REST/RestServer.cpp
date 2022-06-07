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


//Testing:
//curl -X POST http://127.0.0.1:8080 -H "Content: application/json" -d '{"product":"a","number":9}'
void handle_post(http_request request){
    std::wcout<<L"\nhandle POST\n";
    bool isSuccess{false};

    request.headers().set_content_type("application/json");

    auto answer=json::value::object();
    request.extract_json().then([&answer,&request,&isSuccess](pplx::task<json::value> task){
        try{
            auto a=task.get();
            auto b=a.serialize();
            std::wstring req=std::wstring(b.begin(),b.end());
            std::wcout<<req<<std::endl;

            auto number=a.at("number");
            auto c=number.serialize();
            std::wcout<<number.as_integer()<<std::endl;
            std::wstring res=std::wstring(c.begin(),c.end());
            std::wcout<<res<<std::endl;

            auto num=number.as_integer();
            if(num<10){
                answer["is_lower_than_ten"]=1;
                isSuccess=true;
            }else{
                answer["is_lower_than_ten"]=0;
                isSuccess=false;
            }

        }catch(const std::exception& e){
            std::wcout<<e.what()<<std::endl;
        }
    }).wait();

    request.reply(status_codes::OK,answer);
}

//SERVER
Server::Server(const std::string& _addrress):listener(_addrress){
    listener.support(methods::GET, handle_get);
    listener.support(methods::POST,handle_post);
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
 