#include "RestServer.h"

namespace REST
{

    void display_json(
        json::value const &jvalue,
        utility::string_t const &prefix)
    {
        std::cout << prefix << jvalue.serialize() << std::endl;
    }

    // Testing:
    // curl -X POST http://127.0.0.1:8080 -H "Content: application/json" -d '{"product":"a","number":9}'
    //curl -X POST http://127.0.0.1:8080 -H "Content: application/json" -d '{"items":[{"product":"a","number":9},{"product":"a","number":9}]}'
    void handle_post(http_request request)
    {
        std::wcout << L"\nhandle POST\n";
        bool isSuccess{false};

        request.headers().set_content_type("application/json");

        auto answer = json::value::object();
        request.extract_json().then([&answer, &request, &isSuccess](pplx::task<json::value> task)
                                    {
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
        } })
            .wait();

        request.reply(status_codes::OK, answer);
    }

    // SERVER
    Server::Server(const std::string &_addrress, SQLDriver& _driver) : listener(_addrress),driver(_driver)
    {
        auto post=[this](http_request request){
            std::wcout << L"\nhandle POST\n";
        request.headers().set_content_type("application/json");

        auto answer = json::value::object();
        request.extract_json().then([&answer, &request](pplx::task<json::value> task)
                                    {
        try{
            auto a=task.get();
            auto myArray=a.at("items").as_array();
            std::vector<std::pair<std::string,int>> itemsToBuy;
            for(const auto& it: myArray){
                auto key=it.at("product").as_string();
                auto val=it.at("number").as_integer();
                std::string skey{key};
                //itemsToBuy.push_back{std::make_pair<std::string,int>(skey,val)};
                std::wstring temp=std::wstring(key.begin(),key.end());
                std::wcout<<temp<<" "<<val<<std::endl;
            }
            

        }catch(const std::exception& e){
            std::wcout<<e.what()<<std::endl;
        } }).wait();

        request.reply(status_codes::OK, answer);
        };

        auto get=[this](http_request request){
            std::wcout << L"\nhandle GET\n";

        auto a = request.relative_uri();
        std::wstring path = std::wstring(a.path().begin(), a.path().end());
        std::string arg{a.to_string()};
        if(arg=="\""){
        auto answer=driver.getAllProductsInformation();
        display_json(answer, "S: ");
        request.reply(status_codes::OK, answer);
        }else{
            auto answer=driver.getProductData(arg);
            display_json(answer, "S: ");
        request.reply(status_codes::OK, answer);
        }
        };

        listener.support(methods::POST, post);
        listener.support(methods::GET, get);
    }

    void Server::run()
    {
        try
        {
            listener
                .open()
                .then([this]()
                      { std::wcout << "Starting to listen\n"; })
                .wait();

            while (true)
                ;
        }
        catch (std::exception const &e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}
