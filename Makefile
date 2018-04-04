CC = g++
FLAGS = -std=c++17 -Wall -O3
DEPS = -lstdc++fs -lpqxx -lpq -lzip -lpthread
# -lzlib
#pgHelpers.cpp zipHelpers.cpp
main.out: main.cpp  pgHelpers.cpp
	$(CC) $(FLAGS) -o a.out main.cpp pgHelpers.cpp $(DEPS)