CPPFILE = ../common/epollServer.cpp server.cpp login.cpp ../common/log.cpp sql_do.cpp ../mysql/sql.cpp
OFILE = epollServer.o server.o login.o log.o sql_do.o sql.o
MYSQL = `mysql_config --cflags --libs`
STAND = -std=c++11
CFLAGS = $(STAND) $(MYSQL)

login: $(OFILE)
	g++ $(CFLAGS) $(OFILE) -o login

$(OFILE): $(CPPFILE)
	g++ $(CFLAGS) -c $(CPPFILE)

clean:
	rm -rf *.o login