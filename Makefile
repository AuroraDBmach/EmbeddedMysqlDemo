CC = gcc 
CXX = g++ 
LINK = gcc 
ECHO = echo

####################################
CFLAGS = -Wall -O2 -I./include -I/usr/local/mysql/include/mysql -I/usr/local/mysql/include/mysql/..
CXXFLAGS = -Wall -O2 -I./include -I/usr/local/mysql/include/mysql -I/usr/local/mysql/include/mysql/..


LIBS = -L/usr/local/mysql/lib -lmysqld -lpthread -lm -ldl

# 
# cf. /usr/local/mysql/bin/mysql_config –-cflags 
# cf. /usr/local/mysql/bin/mysql_config -–libs 
# 
#################################

# Source File List 
# 
SOURCES = ./src/demo.c \
				./src/dummy.c

OBJECTS = ./obj/demo.o \
                 ./obj/dummy.o
				 
TARGET = ./bin/demo

# Build rule
all: $(TARGET)
$(TARGET): $(OBJECTS)
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS) # 앞에 들여쓰기는 탭 문자임! 이하 녹색표기

run:
	LD_LIBRARY_PATH=/home/mach/Test/mariadb-10.1.7/embedded/lib ./bin/demo
	
hint:
	$(ECHO) "to exec. type ";\
	$(ECHO) "$ LD_LIBRARY_PATH=/home/mach/Test/mariadb-10.1.7/embedded/lib ./bin/demo"
	
clean:
	rm -f $(OBJECTS) $(TARGET) core
	
#-----------------------------------------
./obj/demo.o : ./src/demo.c 
	$(CC) -c $(CFLAGS) -o $@ $<
	
./obj/dummy.o : ./src/dummy.c 
	$(CC) -c $(CFLAGS) -o $@ $<
