target: server.c
	gcc server.c -o server

clean: server
	rm -rf server