FROM node:16.13.0

ENV WTSADDRESS=http://localhost:9222
ENV AFORO=10
ENV SECRET=ABRACADABRA
ENV SECRETAES="11122233344455566677788822244455555555555555555231231321313aaaff"
ENV DBNAME=parqueatracciones
ENV DBUSER=root
ENV DBPASS=root
ENV DBADDR=oldbox.cloud
ENV APIKEY="d9eee5d3d5d5a86c5868e8c61381983c"
ENV KAFKAADDRESS=oldbox.cloud:9092

WORKDIR /app

COPY ./ ./

RUN npm i

CMD ["npm", "start"]

# Para montar la image:
#   docker build -t sd:fwq_engine .

# Para exportar la imágen:
#   docker save -o fwq_engine.tar sd:fwq_engine

# Para importar la imágen:
#   docker load -i fwq_engine.tar

# Para arrancar el contenedor, si no se especifican las variables de entorno, se usan los valores por defecto.
#   docker run --name fwq_engine -it -e AFORO="10" -e WTSADDRESS="http://172.20.40.150:9222" -e KAFKAADDRESS="172.20.40.151:9092" -e DBNAME="pq" -e DBUSER="root" -e DBPASS="root" -e DBADDR="172.20.40.151" sd:fwq_engine
