FROM node:16.13.0

ENV IDATTR=0
ENV X=14
ENV Y=3
# ENV IMAGEN= ( Optativo )
ENV KAFKAADDRESS=oldbox.cloud:9092

WORKDIR /app

COPY ./ ./

RUN npm i

CMD ["npm", "start"]

# Para montar la image:
#   docker build -t sd:fwq_sensor .

# Para exportar la imágen:
#   docker save -o fwq_sensor.tar sd:fwq_sensor

# Para importar la imágen:
#   docker load -i fwq_sensor.tar

# Para arrancar el contenedor, si no se especifican las variables de entorno, se usan los valores por defecto.
#   docker run --name fwq_sensor -it -e IDATTR="0" -e X="2" -e Y="6" -e KAFKAADDRESS="172.20.40.150:9092" -e ATTRPERSONTIMEINTER="3" -e IMAGEN="https://i.imgur.com/Ff7SEP6.png" sd:fwq_sensor

# Imagenes:
#   https://i.imgur.com/Ff7SEP6.png
#   https://cdn-icons-png.flaticon.com/128/1761/1761560.png
#   https://cdn-icons-png.flaticon.com/128/2060/2060024.png
#   https://i.imgur.com/WPSPxoT.png
