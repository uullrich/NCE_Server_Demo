#include <vector>
#include <iostream>
#include <string>

#include "TcpServer.h"
#include "CommandHandler.h"
#include "CommandExecutionInterface.h"
#include "Command.h"

int main() {
    std::vector<CommandExecutionInterface> execIf{{
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

    CommandHandler commandHandler{execIf};
    TcpServer server{33344, commandHandler};

    return 0;
}
