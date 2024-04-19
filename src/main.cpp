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
                                                              std::stringstream responseStream;
                                                              responseStream << "Received value: " << command.value << "\n";
                                                              command.client->send(responseStream.str());
                                                          },
                                                          [](Command &command) {
                                                              std::cout << "GET Test processed" << std::endl;
                                                              command.client->send("Hello world from GET\n");
                                                          },
                                                          [](Command &command) {
                                                              std::string payload(command.data.begin(),
                                                                                  command.data.end());
                                                              std::cout << "SET-DATA Test processed with payload: "
                                                                        << payload << std::endl;
                                                              std::stringstream responseStream;
                                                              responseStream << "Received payload: " << payload << "\n";
                                                              command.client->send(responseStream.str());
                                                          },
                                                          [](Command &command) {
                                                              std::cout << "GET-DATA Test processed" << std::endl;
                                                              command.client->send("Hello world from GET-DATA\n");
                                                          }
                                                  }
    };

    CommandHandler commandHandler{execIf};
    TcpServer server{33344, commandHandler};

    return 0;
}
