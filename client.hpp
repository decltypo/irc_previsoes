#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "everything.hpp"


using boost::asio::ip::tcp;
class client
{
public:
  client(boost::asio::io_service& io_service);
  void connect(const std::string &host, const std::string &address);
  void write(const std::string& msg);
  void close();

private:
  virtual void client_connected() {}
  virtual void client_error(boost::system::error_code& ec) {}
  virtual void client_received(std::string &s) {}

  void do_connect(tcp::resolver::iterator endpoint_iterator);
  void do_read_line();
  void do_write();

private:
  boost::asio::io_service& io_service_;
  tcp::socket socket_;
  boost::asio::streambuf readbuf_;
  std::deque<std::string> write_msgs_;
};

#endif
