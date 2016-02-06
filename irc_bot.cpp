#include "irc_bot.hpp"

irc_bot::irc_bot(boost::asio::io_service& io_service) : irc_client(io_service) {};

void irc_bot::on_error(boost::system::error_code& ec)
{
  on_disconnect();
}


void irc_bot::irc_connected()
{
  writeln("NICK previsoes");
  writeln("USER previsoes previsoes irc.rizon.net :previsoes");
  writeln("JOIN #safe-space");
};

void irc_bot::on_disconnect() {}

void irc_bot::on_channel_message(const std::string& from, const std::string& message) {}
void irc_bot::on_private_message(const std::string& from, const std::string& message) {}
