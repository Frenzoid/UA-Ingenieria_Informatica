FROM node:16.13.0

EXPOSE 9111
EXPOSE 5000

ENV REACT_APP_REGISTRYADDRESS=http://localhost:9090
ENV REACT_APP_KAFKACONTROLLER=http://localhost:9111
ENV REACT_APP_KAFKAADDRESS=oldbox.cloud:9092
ENV REACT_APP_SECRET=ABRACADABRA
ENV REACT_APP_VISITORINTERVAL=0.75
ENV REACT_APP_SENSORCHECKINTERVAL=5
ENV REACT_APP_SECRETAES="11122233344455566677788822244455555555555555555231231321313aaaff"
ENV NODE_TLS_REJECT_UNAUTHORIZED="0"

WORKDIR /app

COPY ./ ./

RUN npm install -g serve concurrently
RUN yarn install

CMD npm run build && concurrently "serve -C -p 5000 -s build" "node kafkaController.js"

# Para montar la image:
#   docker build -t sd:fwq_visitor .

# Para exportar la imágen:
#   docker save -o fwq_visitor.tar sd:fwq_visitor

# Para importar la imágen:
#   docker load -i fwq_visitor.tar

# Para arrancar el contenedor
#   docker run --name fwq_visitor -it -e REACT_APP_REGISTRYADDRESS="http://172.20.40.151:9090" -e REACT_APP_KAFKACONTROLLER="http://172.20.40.150:9111" -e REACT_APP_KAFKAADDRESS="172.20.40.150:9092" -p 5000:5000 -p 9111:9111 sd:fwq_visitor
