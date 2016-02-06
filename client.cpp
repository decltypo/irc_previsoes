#include "client.hpp"

client::client(boost::asio::io_service& io_service) : io_service_(io_service), socket_(io_service) {}

void client::connect(const std::string &host, const std::string &address)
{
  tcp::resolver resolver(io_service_);
  auto endpoint_iterator = resolver.resolve({ host, address});
  do_connect(endpoint_iterator);
}

void client::write(const std::string& msg)
{
  io_service_.post(
      [this, msg]()
      {
        bool write_in_progress = !write_msgs_.empty();
        write_msgs_.push_back(msg);
        if (!write_in_progress)
        {
          do_write();
        }
      });
}

void client::close()
{
  io_service_.post([this]() { socket_.close(); });
}


void client::do_connect(tcp::resolver::iterator endpoint_iterator)
{
  boost::asio::async_connect(socket_, endpoint_iterator,
      [this](boost::system::error_code ec, tcp::resolver::iterator)
      {
        if (!ec)
        {
          client_connected();
          do_read_line();
        }
        else
        {
          client_error(ec);
        }
      });
}

void client::do_read_line()
{
  boost::asio::async_read_until(socket_,
      readbuf_,
      '\n',
      [this](boost::system::error_code ec, std::size_t /*length*/)
      {
        if (!ec)
        {
          std::istream is(&readbuf_);
          std::string line;
          std::getline(is,line);
          client_received(line);
          do_read_line();
        }
        else
        {
          socket_.close();
          client_error(ec);
        }
      });
}


void client::do_write()
{
  boost::asio::async_write(socket_,
      boost::asio::buffer(write_msgs_.front().data(),
        write_msgs_.front().length()),
      [this](boost::system::error_code ec, std::size_t /*length*/)
      {
        if (!ec)
        {
          write_msgs_.pop_front();
          if (!write_msgs_.empty())
          {
            do_write();
          }
        }
        else
        {
          socket_.close();
        }
      });
}
