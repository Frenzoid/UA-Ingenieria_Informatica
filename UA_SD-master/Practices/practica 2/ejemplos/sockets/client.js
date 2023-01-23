const { io } = require("socket.io-client");
const socket = io("http://localhost:9111");

// Datos a mandar.
let datos = { saludo: "hola" };

// contandor de reintentos.
let intentos = 0;

// Con nuestro socket (cliente) podemos definir ciertos eventos a manejar entre cliente y servidor.
// Con socket.on("nombre_event", (dato) => {}}) definimos un evento de recepcio (servidor->cliente)
// Con socket.emit("nombre_event", "dato") definimos un evento de emision (cliente->servidor)

// Madamos un mensaje al servidor.
socket.emit("manda_hola", datos);

// Recibimos un mensaje del servidor.
socket.on('recibe_adios', (dato) => {
    console.log("El servidor ha mandado:", dato);
})

// Si el cliente pierde la conexion con el servidor...
socket.on('connect_error', (err) => {
    console.log("Se ha perdido la conexion con el servidor, reintentando. Intento:", intentos);
    intentos++;

    if (intentos >= 3) socket.disconnect();
});

