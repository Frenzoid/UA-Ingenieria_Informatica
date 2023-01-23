FROM node:16.13.0

EXPOSE 5001

ENV REACT_APP_APIENGINE=http://localhost:3003
ENV REACT_APP_REQUESTTIME=1

WORKDIR /app

COPY ./ ./

RUN npm install -g serve
RUN yarn install

CMD npm run build && serve -C -p 5001 -s build

# Para montar la image:
#   docker build -t sd:fwq_front .

# Para exportar la imágen:
#   docker save -o fwq_front.tar sd:fwq_front

# Para importar la imágen:
#   docker load -i fwq_front.tar

# Para arrancar el contenedor:
#   docker run --name fwq_front -it -e REACT_APP_APIENGINE="http://localhost:3003" -p 5001:5001 sd:fwq_front