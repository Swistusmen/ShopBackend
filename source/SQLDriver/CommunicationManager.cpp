#include "CommunicationManager.h"

std::optional<std::string> Request::getResponse()
{
    if (isFinished == false)
        return {};
    return response;
};

void Request::run()
{
    communication();
}

void Request::communication()
{
    try
    {
        boost::asio::io_context io_context;

        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints =
            resolver.resolve(ip, std::to_string(port));

        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        boost::array<char, 1024> buf;
        boost::system::error_code error;
        socket.write_some(boost::asio::buffer(request, request.length() * sizeof(char)));
        socket.read_some(boost::asio::buffer(buf), error);
        response = static_cast<std::string>(buf.data());
        isFinished = true;
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}

std::string Request::trimMessage(const std::string &msg)
{
    const int len = msg.size();
    std::string trimmedMessage{""};
    for (const auto &it : msg)
    {
        if (it > 47 && it < 90 || it > 96 && it < 123 || it == '*' || it == ',' || it == ' ')
        {
            trimmedMessage += it;
        }
    }
    return trimmedMessage;
}

CommunicationManager::~CommunicationManager()
{
    for (auto &it : threads)
    {
        if (it.joinable())
            it.join();
    }
}

Request &CommunicationManager::make_request(const std::string &_reuqest)
{
    requests.emplace_back(_reuqest, ipAddress, port);
    std::thread t(&Request::run, &requests.back());
    threads.push_back(std::move(t));
    return requests.back();
}

Request &CommunicationManager::make_request(const std::string &_reuqest, const std::string &_ip, const int _port)
{
    requests.emplace_back(_reuqest, _ip, _port);
    std::thread t(&Request::run, &requests.back());
    threads.push_back(std::move(t));

    return requests.back();
}