#include "ServerDemo.h"
#include "Command.h"
#include "CommandHandler.h"
#include "CommandExecutionInterface.h"
#include "TcpServer.h"

#include <iostream>

ServerDemo::ServerDemo(unsigned short port) {
    _execIf << (CommandExecutionInterface(this) << Endpoint{"test"} << &ServerDemo::setTest << &ServerDemo::getTest
                                                << &ServerDemo::setDataTest << &ServerDemo::getDataTest)
            << (CommandExecutionInterface(this) << Endpoint{"test2"} << &ServerDemo::setTest << NO_RESPONSE::GET
                                                << &ServerDemo::setDataTest << &ServerDemo::getDataTest)
            << (CommandExecutionInterface(this) << Endpoint{"test3"} << NO_RESPONSE::SET << NO_RESPONSE::GET
                                                << NO_RESPONSE::SET_DATA << &ServerDemo::getDataTest);

    CommandHandler commandHandler{_execIf};
    _server = std::make_unique<TcpServer>(port, commandHandler);
}

void ServerDemo::setTest(Command &command) {
    std::cout << "SET Test processed with value: "
              << command.value << std::endl;
    command.sendOk();
}

void ServerDemo::setDataTest(Command &command) {
    std::string payload(command.data.begin(),
                        command.data.end());
    std::cout
            << "SET-DATA Test processed with payload: "
            << payload << std::endl;
    command.sendOk();
}

void ServerDemo::getTest(Command &command) {
    std::cout << "GET Test processed" << std::endl;
    command.sendValue("4711");
}

void ServerDemo::getDataTest(Command &command) {
    std::cout << "GET-DATA Test processed"
              << std::endl;
    command.sendData("blubb\n123");
}