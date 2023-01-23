FROM node:16.13.0

ENV WTSPORT=9222
ENV SECRET=ABRACADABRA
ENV KAFKAADDRESS=oldbox.cloud:9092

WORKDIR /app

COPY ./ ./

RUN npm i

CMD ["npm", "start"]

# Para montar la image:
#   docker build -t sd:fwq_waitingtimeserver .

# Para exportar la imágen:
#   docker save -o fwq_waitingtimeserver.tar sd:fwq_waitingtimeserver

# Para importar la imágen:
#   docker load -i fwq_waitingtimeserver.tar

# Para arrancar el contenedor, si no se especifican las variables de entorno, se usan los valores por defecto.
#   docker run --name fwq_waitingtimeserver -it -e WTSPORT="9222" -e KAFKAADDRESS="oldbox.cloud:9092" -p 9222:9222 sd:fwq_waitingtimeserver