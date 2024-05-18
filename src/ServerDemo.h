#ifndef SERVER_DEMO_H
#define SERVER_DEMO_H
#include <memory>
#include <vector>

class TcpServer;
class CommandExecutionInterface;
class Command;

class ServerDemo {
public:
    explicit ServerDemo(unsigned short port);
private:
    void setTest(Command & command);
    void setDataTest(Command & command);
    void getTest(Command & command);
    void getDataTest(Command & command);

    std::vector<CommandExecutionInterface> _execIf;
    std::unique_ptr<TcpServer> _server;
};

#endif
