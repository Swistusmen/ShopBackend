#pragma once
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>

using boost::asio::ip::tcp;

class CommunicationManager;

class Request
{
public:
    Request(const std::string &_request, const std::string &ipAddress, const int _port) : request(_request), port(_port), ip(ipAddress)
    {
    }

    std::optional<std::string> getResponse();

    void run();

    bool finished() const { return isFinished; }

    const std::string &getRequest() const { return request; }

private:
    std::string request{""};
    std::string response{""};
    std::string ip{""};
    bool isFinished{false};
    int port;

private:
    void communication();
    std::string trimMessage(const std::string& msg);
};

class CommunicationManager
{
public:
    CommunicationManager(const std::string &_ipAddress, const int _port) : port(_port), ipAddress(_ipAddress){};

    ~CommunicationManager();

    Request &make_request(const std::string &_reuqest);

    Request &make_request(const std::string &_reuqest, const std::string &_ip, const int _port);

private:
    std::vector<Request> requests;
    std::vector<std::thread> threads;
    std::string ipAddress;
    int port;
};
