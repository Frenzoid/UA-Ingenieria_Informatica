FROM node:16.13.0

EXPOSE 3003

ENV APIPORT=3003
ENV DBNAME=parqueatracciones
ENV DBUSER=root
ENV DBPASS=root
ENV DBADDR=oldbox.cloud

WORKDIR /app

COPY ./ ./

RUN npm i

CMD ["npm", "start"]

# Para montar la image:
#   docker build -t sd:api_engine .

# Para exportar la imágen:
#   docker save -o api_engine.tar sd:api_engine

# Para importar la imágen:
#   docker load -i api_engine.tar

# Para arrancar el contenedor
#   docker run --name api_engine -it -e APIPORT="3003" -e DBNAME="pq" -e DBUSER="root" -e DBPASS="root" -e DBADDR="172.20.40.150" -p 3003:3003 sd:api_engine
