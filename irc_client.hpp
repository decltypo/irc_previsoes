#ifndef IRC_CLIENT_HPP
#define IRC_CLIENT_HPP

#include "everything.hpp"
#include "client.hpp"

using namespace std;

class irc_client : public client
{

public:
  irc_client(boost::asio::io_service& io_service);
  void writeln(const std::string &line);

private:



  void client_received(string &line);

  void on_ping(const string& ping_id);


  virtual void on_error(boost::system::error_code& ec) {}
  virtual void irc_connected() {}
  virtual void irc_disconnected() {}

  void client_connected() {irc_connected();}

};

#endif
