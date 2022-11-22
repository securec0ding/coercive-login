all: main

main: main.cpp
	g++ -g -o main main.cpp -std=c++0x

clean:
	rm main