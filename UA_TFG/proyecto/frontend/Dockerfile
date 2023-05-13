# Imagen base de nodejs
FROM node:latest

# Directorio de trabajo
WORKDIR /app

# Copia de archivos
COPY package.json ./
COPY package-lock.json ./
COPY . ./

# Instalación de dependencias
RUN npm install
RUN npm run build

# Puerto en el cual se expone el servidor web
EXPOSE 5000

# Comando por defecto
CMD ["npm", "run", "serve"]