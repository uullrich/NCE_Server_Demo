#include <vector>
#include <iostream>
#include <string>

#include "TcpServer.h"
#include "CommandHandler.h"
#include "CommandExecutionInterface.h"
#include "Command.h"
#include "ServerDemo.h"

int main() {
    //Execution interface with lambdas and brace initialization
    std::vector<CommandExecutionInterface> execIfLambdas{{
                                                          {"test"},
                                                          [](Command &command) {
                                                              std::cout << "SET Test processed with value: "
                                                                        << command.value << std::endl;
                                                              command.sendOk();
                                                              //command.client->send("SET-RESPONSE test\n");
                                                              //command.sendError("Some error occured");
                                                          },
                                                          [](Command &command) {
                                                              std::cout << "GET Test processed" << std::endl;
                                                              command.sendValue("4711");
                                                          },
                                                          [](Command &command) {
                                                              std::string payload(command.data.begin(),
                                                                                  command.data.end());
                                                              std::cout << "SET-DATA Test processed with payload: "
                                                                        << payload << std::endl;
                                                              command.sendOk();
                                                          },
                                                          [](Command &command) {
                                                              std::cout << "GET-DATA Test processed" << std::endl;
                                                              command.sendData("blubb\n123");
                                                          }
                                                  }
    };

    //CommandHandler commandHandler{execIfLambdas};
    //TcpServer server{33344, commandHandler};

    //Execution interface with instance methods as handlers in ServerDemo
    ServerDemo serverDemo{33344};

    return 0;
}
