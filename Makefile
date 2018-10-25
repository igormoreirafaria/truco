target: server.c
	gcc server.c -o server

client: cliente.c
	gcc cliente.c -o cliente

clean: server
	rm -rf server