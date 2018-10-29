target: serverthread.c truco.c
	gcc serverthread.c truco.c -pthread -o servidor

client: cliente.c
	gcc clientethread.c -pthread -o cliente

clean: server
	rm -rf server