FROM node:16.13.0

EXPOSE 9090

ENV FWQRPORT=9090
ENV DBNAME=parqueatracciones
ENV DBUSER=root
ENV DBPASS=root
ENV DBADDR=oldbox.cloud
ENV SECRET=ABRACADABRA

WORKDIR /app

COPY ./ ./

RUN npm i

CMD ["npm", "start"]

# Para montar la image:
#   docker build -t sd:fwq_registry .

# Para exportar la imágen:
#   docker save -o fwq_registry.tar sd:fwq_registry

# Para importar la imágen:
#   docker load -i fwq_registry.tar

# Para arrancar el contenedor
#   docker run --name fwq_registry -it -v certs/:/app/certs:ro -e FWQRPORT="9090" -e DBNAME="pq" -e DBUSER="root" -e DBPASS="root" -e DBADDR="172.20.40.150" -p 9090:9090 sd:fwq_registry
