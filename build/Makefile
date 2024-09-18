CXX = g++
CXXFLAGS = -std=c++20 -I/opt/homebrew/opt/botan/include/botan-3 -I../src -I../src/Encryptor
LDFLAGS = -L/opt/homebrew/opt/botan/lib
LIBS = -lbotan-3

TARGET = main
SRC_DIR = ../src
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/Encryptor/Encryptor.cpp

all: check-files $(TARGET)

check-files:
	@if [ ! -f $(SRCS) ]; then \
		echo "Error: $(SRCS) not found."; \
		echo "Please ensure $(SRCS) exists."; \
		exit 1; \
	fi

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) $(LDFLAGS) $(LIBS) -o $@

clean:
	rm -f $(TARGET)

.PHONY: all clean check-files