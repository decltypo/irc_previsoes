#ifndef IRC_BOT_HPP
#define IRC_BOT_HPP

#include "everything.hpp"
#include "irc_client.hpp"

class irc_bot : public irc_client
{
public:
  irc_bot(boost::asio::io_service& io_service);

  void on_error(boost::system::error_code& ec);

  void irc_connected();
  void on_disconnect();
  void on_channel_message(const std::string& from, const std::string& message);
  void on_private_message(const std::string& from, const std::string& message);




};

#endif
