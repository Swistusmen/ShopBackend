project("shop")
cmake_minimum_required(VERSION "3.9")

set(CMAKE_CXX_COMPILER)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(cpprestsdk REQUIRED)

set_target_properties(cpprestsdk::cpprestsdk_openssl_internal PROPERTIES
  INTERFACE_COMPILE_DEFINITIONS "CPPREST_NO_SSL_LEAK_SUPPRESS"
  INTERFACE_LINK_LIBRARIES "OpenSSL::SSL"
)

include_directories(
    REST
    Parser
)

add_executable(${PROJECT_NAME}
    main.cpp 

    REST/RestServer.h 
    REST/RestServer.cpp
    Parser/Parser.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE cpprestsdk::cpprest)


