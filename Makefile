target: serverthread.c
	gcc serverthread.c -pthread -o server

client: cliente.c
	gcc cliente.c -o cliente

clean: server
	rm -rf server