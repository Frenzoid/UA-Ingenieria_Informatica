const { Server } = require("socket.io");
const io = new Server();

// Cuando se recibe una conexion, se ejecuta esta funcion lambda.
io.on("connection", (socket) => {
    // Por cada socket, podemos definir ciertos eventos a manejar entre cliente y servidor.
    // Con socket.on("nombre_event", (dato) => {}}) definimos un evento de recepcio (cliente->servidor)
    // Con socket.emit("nombre_event", "dato") definimos un evento de emision (servidor->cliente)

    console.log("Cliente con id", socket.id, "conectado.");

    socket.on("manda_hola", (message) => {
        console.log(io.sockets.sockets.get(socket.id));

        console.log("El cliente", socket.id, "ha mandado:", message);
        socket.emit("recibe_adios", "adios");
    });

    socket.on('disconnect', () => {
        console.log("Cliente con id", socket.id, "desconectado.");
    });
});

io.listen(9111);