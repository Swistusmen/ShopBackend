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

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREAD ON)
find_package(Boost 1.74.0 REQUIRED system thread regex)
set(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})

include_directories(
    REST
    Parser
)

add_executable(${PROJECT_NAME}
    main.cpp 

    REST/RestServer.h 
    REST/RestServer.cpp
    SQLDriver/CommunicationManager.h 
    SQLDriver/CommunicationManager.cpp
    SQLDriver/SQLDriver.h 
    SQLDriver/SQLDriver.cpp
    Parser/Parser.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE cpprestsdk::cpprest)
target_link_libraries(${PROJECT_NAME} PRIVATE ${USED_LIBS})


