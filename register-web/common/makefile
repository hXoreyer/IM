CPPFILE = epollServer.cpp server.cpp test_server.cpp log.cpp sql_do.cpp ../mysql/sql.cpp
OFILE = epollServer.o server.o test_server.o log.o sql_do.o sql.o
MYSQL = `mysql_config --cflags --libs`
STAND = -std=c++11
CFLAGS = $(STAND) $(MYSQL)

test_server: $(OFILE)
	g++ $(CFLAGS) $(OFILE) -o test_server

$(OFILE): $(CPPFILE)
	g++ $(CFLAGS) -c $(CPPFILE)

clean:
	rm -rf *.o test_server