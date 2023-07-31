#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PUERTO 8080
#define TAM_BUFFER 1024

void responder(int cliente_fd, const char* mensaje) {
    char respuesta[TAM_BUFFER];
    sprintf(respuesta,
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: %ld\r\n"
            "\r\n"
            "%s",
            strlen(mensaje), mensaje);
    send(cliente_fd, respuesta, strlen(respuesta), 0);
}

int main() {
    int servidor_fd, cliente_fd;
    struct sockaddr_in direccion_servidor, direccion_cliente;
    socklen_t tam_direccion_cliente;
    char buffer[TAM_BUFFER];

    // Crear el socket
    if ((servidor_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }

    // Configurar la dirección del servidor
    direccion_servidor.sin_family = AF_INET;
    direccion_servidor.sin_port = htons(PUERTO);
    direccion_servidor.sin_addr.s_addr = INADDR_ANY;
    memset(direccion_servidor.sin_zero, '\0', sizeof(direccion_servidor.sin_zero));

    // Vincular el socket a la dirección del servidor
    if (bind(servidor_fd, (struct sockaddr *)&direccion_servidor, sizeof(direccion_servidor)) == -1) {
        perror("Error al vincular el socket");
        close(servidor_fd);
        exit(EXIT_FAILURE);
    }

    // Escuchar conexiones entrantes
    if (listen(servidor_fd, 10) == -1) {
        perror("Error al escuchar");
        close(servidor_fd);
        exit(EXIT_FAILURE);
    }

    printf("Servidor escuchando en el puerto %d...\n", PUERTO);

    while (1) {
        tam_direccion_cliente = sizeof(direccion_cliente);
        // Aceptar una conexión entrante
        if ((cliente_fd = accept(servidor_fd, (struct sockaddr *)&direccion_cliente, &tam_direccion_cliente)) == -1) {
            perror("Error al aceptar la conexión");
            continue;
        }

        printf("Cliente conectado\n");

        // Leer datos enviados por el cliente (ignoramos las solicitudes HTTP completas en esta versión)
        recv(cliente_fd, buffer, TAM_BUFFER, 0);

        // Responder al cliente con un mensaje básico
        const char* mensaje = "<h1>Mi primera pagina web. k emosion.</h1>";
        responder(cliente_fd, mensaje);

        // Cerrar la conexión con el cliente
        close(cliente_fd);
    }

    // Cerrar el socket del servidor
    close(servidor_fd);

    return 0;
}
