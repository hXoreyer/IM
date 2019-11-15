CPPFILE = epoll_udp.cpp chat.cpp ../common/log.cpp
OFILE = epoll_udp.o chat.o log.o
MYSQL = `mysql_config --cflags --libs`
STAND = -std=c++11
CFLAGS = $(STAND) $(MYSQL)

chat: $(OFILE)
	g++ $(CFLAGS) $(OFILE) -o chat

$(OFILE): $(CPPFILE)
	g++ $(CFLAGS) -c $(CPPFILE)

clean:
	rm -rf *.o chat