CPP_FILE = sql.cpp exe.cpp
O_FILE = sql.o exe.o
MYSQL = `mysql_config --cflags --libs`
STAND = -std=c++11
CFLAGS = $(STAND) $(MYSQL)
exe: $(O_FILE)
	g++ $(CFLAGS) $(O_FILE) -o exe

$(O_FILE):
	g++ -c $(CPP_FILE)

clean:
	rm -rf *.o exe