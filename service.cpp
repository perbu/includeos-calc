#include <os>
#include <sstream>
#include <net/inet>
#include <net/interfaces>

#include "Calculator.h"

double handle_line(net::tcp::Connection_ptr conn, net::tcp::buffer_t buffer ) 
{
    double x = 0.0;
    double y = 0.0;
    double result = 0.0;
    char oper = '+';

    Calculator calc;

    // make a fancy string from the buffer vector
    std::string input_string((char*) buffer->data(),buffer->size());
    // and make a stream of it.
    std::stringstream input_stream(input_string);

    input_stream >> x >> oper >> y;
    result = calc.Calculate(x, oper, y);

    return(result);
}

void Service::start()
{
  auto& inet = net::Interfaces::get(0);
  auto& server = inet.tcp().listen(2000); 

  server.on_connect([] (auto conn) {
    std::cout << "Connection " << conn->to_string() << " established\n";
    conn->write("Welcome to the serverless calculator\n");
    conn->write("Please enter the operation to perform. Format: a+b | a-b | a*b | a/b\n>");

    conn->on_read(1024, [conn] (auto buf) {
      float f = 0;
      f = handle_line(conn,buf);
      conn->write(std::to_string(f).append("\n"));
      conn->close(); // close the connection. We're so serverless.
      std::cout << "Connection " << conn->to_string() << " closed\n";
    });
  });
}

