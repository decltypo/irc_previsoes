//
// chat_client.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2013 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <deque>

#include <thread>
#include <vector>
#include <boost/asio.hpp>
#include <algorithm>

#include "irc_bot.hpp"

using boost::asio::ip::tcp;


int main(int argc, char* argv[])
{
  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: chat_client <host> <port>\n";
      return 1;
    }

    boost::asio::io_service io_service;

    irc_bot irc(io_service);
    irc.connect(argv[1],argv[2]);

    std::thread t([&io_service](){ io_service.run(); });

    std::string line;
    while (std::getline(std::cin,line))
    {
      irc.write(line + "\n");
    }

    irc.close();
    t.join();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
