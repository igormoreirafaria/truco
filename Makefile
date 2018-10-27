target: serverthread.c
	gcc serverthread.c -pthread -o server

client: cliente.c
	gcc clientethread.c -pthread -o cliente

clean: server
	rm -rf server