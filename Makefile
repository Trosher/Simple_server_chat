all: clean server client

server:
	g++ server.cc -o server -w

client:
	g++ client.cc -o client -w

clean: clean_server clean_client

clean_server:
	rm -rf server

clean_client:
	rm -rf client