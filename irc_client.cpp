#include "irc_client.hpp"

irc_client::irc_client(boost::asio::io_service& io_service) : client(io_service) {}

void irc_client::writeln(const std::string &line)
{
    write(line + '\n');
    std::cout << ">>>>>" << line << std::endl;
}


void irc_client::client_received(std::string &line)
{
  auto v=split(line," ");
  if(v.size()==0) return;
  if(v.size()>=2)
  {

  }

  auto cmd=lcase(v[0]);

  if(cmd=="ping" && v.size()==2)
    on_ping(v[1]);


  std::cout << line << std::endl;

}

void irc_client::on_ping(const std::string& ping_id)
{
  writeln("PONG " + ping_id);

}
