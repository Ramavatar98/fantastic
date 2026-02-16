CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I./include
LDFLAGS = -lssl -lcrypto

SOURCES = src/main.cpp src/blockchain.cpp src/utxo.cpp src/mempool.cpp \
          src/signatures.cpp src/address.cpp src/p2p.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = bnc-node

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
	rm -rf data/

install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean install run