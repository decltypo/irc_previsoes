TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    aux.cpp \
    client.cpp \
    irc_bot.cpp \
    irc_client.cpp \
    main.cpp

DISTFILES +=

HEADERS += \
    aux.hpp \
    client.hpp \
    everything.hpp \
    irc_bot.hpp \
    irc_client.hpp

CONFIG += c++11


LIBS += -lboost_system
LIBS += -pthread
