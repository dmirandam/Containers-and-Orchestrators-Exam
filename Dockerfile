FROM ubuntu:latest
RUN apt-get update && apt-get install -y build-essential
WORKDIR /usr/src/app
COPY servidor.c /usr/src/app/
RUN gcc -o servidor servidor.c
EXPOSE 8080
CMD ["./servidor"]





#-----------Dockerfile usando la base de datos----------------
#FROM ubuntu:latest
#RUN apt-get update && apt-get install -y build-essential libpq-dev
#WORKDIR /usr/src/app
#COPY servidor.c /usr/src/app/
#COPY pg_config.h /usr/src/app/
#RUN gcc -o servidor servidor.c -lpq
#EXPOSE 8080
#CMD ["./servidor", "postgresql://myuser:mypassword@db:5432/mydatabase"]
