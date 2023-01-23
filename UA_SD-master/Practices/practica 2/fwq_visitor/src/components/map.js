/* eslint-disable react-hooks/exhaustive-deps */
import { useEffect, useState } from 'react';
import { useHistory } from "react-router-dom";
import { VISITORINTERVAL, SENSORCHECKINTERVAL, REGISTRYADDRESS } from "../configs/parametros";
import * as Axios from "axios";

function Map(props) {
    const history = useHistory();
    const socketRegistry = props.socketRegistry;
    const kafkaWebSocket = props.kafkaWebSocket;
    const method = props.method;

    const [user, setUser] = [props.user, props.setUser];
    const [matrix, setMatrix] = useState([]);

    let atracciones = [];
    let timers = [];
    let usuarios = [];
    let inter;
    const n = 20;

    useEffect(() => {

        // Si el usuario no esta registrado, no le permitimos acceder a esta página.
        if (!user.logged)
            history.push("/");


        bindSokets();

        for (let i = 0; i < n; i++) {
            // Columnas (array vacio).
            matrix[i] = [];
            for (let j = 0; j < n; j++) {
                // Filas ( populadas )
                matrix[i][j] = { color: "blue", value: " " }
            }
        }

        renderizarMapa();

        inter = setInterval(() => {
            user.x_actual = Number(user.x_actual);
            user.y_actual = Number(user.y_actual);
            user.x_destino = Number(user.x_destino);
            user.y_destino = Number(user.y_destino);

            if (usuarioEstaEnDestino()) {
                seleccionaAtraccion();
            } else {
                moverseSiguientePosicion();
            }

            kafkaWebSocket.emit("dato_enviado_usr", user);

            if (atracciones) {
                console.log("Atracciones actuales:", atracciones);

                atracciones.forEach((attr) => {
                    if (attr && attr.id) {
                        timers[attr.id]++;

                        colorearCasilla(attr.coordX, attr.coordY, "purple");
                        escribirCasilla(attr.coordX, attr.coordY, attr.tiempo);
                        definirImagenCasilla(attr.coordX, attr.coordY, attr.imagen);
                        bordearCasilla(attr.coordX, attr.coordY, "");

                        if (attr.tiempo >= 60)
                            bordearCasilla(attr.coordX, attr.coordY, "10px solid red");

                        if (attr.tiempo == 1000) {
                            bordearCasilla(attr.coordX, attr.coordY, "10px solid grey");
                            escribirCasilla(attr.coordX, attr.coordY, "Mala tmp.");
                        }

                        if (attr.time == 1000) {
                            bordearCasilla(attr.coordX, attr.coordY, "10px solid yellow");
                            escribirCasilla(attr.coordX, attr.coordY, "Mala tmp.");
                        }

                        if (timers[attr.id] && timers[attr.id] >= SENSORCHECKINTERVAL) {
                            colorearCasilla(attr.coordX, attr.coordY, "grey");
                            escribirCasilla(attr.coordX, attr.coordY, `Sensor ${attr.id} off`);
                            bordearCasilla(attr.coordX, attr.coordY, "");
                        }
                    }
                });
            }

            actualizarUsuario();
            renderizarMapa();


        }, VISITORINTERVAL);

        // Parar el bucle cuando se desrenderice el componente ( cuando se cambia a otra página )
        return () => {
            unbindSockets();
            clearInterval(inter);
        }

    }, []);


    // Auxiliares.

    let randomIntFromInterval = (min, max) => {
        // min and max included
        return Math.floor(Math.random() * (max - min + 1) + min)
    }


    // Métodos de gestion del usuario actual.

    let actualizarUsuario = () => {
        setUser({ ...user });
    }

    let usuarioEstaEnDestino = () => {
        return user.x_actual == user.x_destino && user.y_actual == user.y_destino;
    }

    let moverseSiguientePosicion = () => {

        // PARA X:
        // Destino está a la derecha.
        if (user.x_actual < user.x_destino) {

            // Si es más corto el tramo de donde estamos hacia el destino, que el tramo circundante, avanzamos.
            if ((user.x_destino - user.x_actual) < (user.x_actual + n - user.x_destino)) {
                user.x_actual++;

                // Si es más corto el tramo circundante, que el tramo de donde estamos hacia el destino, retrocedemos.
            } else if ((user.x_destino - user.x_actual) > (user.x_actual + n - user.x_destino)) {
                user.x_actual--;
            }

            // Destino está a la izquierda.
        } else if (user.x_actual > user.x_destino) {

            // Si es más corto el tramo de donde estamos hacia el destino, que el tramo circundante, retrocedemos.
            if ((user.x_actual - user.x_destino) < (user.x_destino + n - user.x_actual)) {
                user.x_actual--;

                // Si es más corto el tramo circundante, que el tramo de donde estamos hacia el destino, avanzamos.
            } else if ((user.x_actual - user.x_destino) > (user.x_destino + n - user.x_actual)) {
                user.x_actual++;
            }
        }

        //  PARA Y:
        // Destino está a la derecha.
        if (user.y_actual < user.y_destino) {

            // Si es más corto el tramo de donde estamos hacia el destino, que el tramo circundante, subimos.
            if ((user.y_destino - user.y_actual) < (user.y_actual + n - user.y_destino)) {
                user.y_actual++;

                // Si es más corto el tramo circundante, que el tramo de donde estamos hacia el destino, bajamos.
            } else if ((user.y_destino - user.y_actual) > (user.y_actual + n - user.y_destino)) {
                user.y_actual--;
            }

            // Destino está a la izquierda.
        } else if (user.y_actual > user.y_destino) {

            // Si es más corto el tramo de donde estamos hacia el destino, que el tramo circundante, bajamos.
            if ((user.y_actual - user.y_destino) < (user.y_destino + n - user.y_actual)) {
                user.y_actual--;

                // Si es más corto el tramo circundante, que el tramo de donde estamos hacia el destino, subimos.
            } else if ((user.y_actual - user.y_destino) > (user.y_destino + n - user.y_actual)) {
                user.y_actual++;
            }
        }

        // Si salta los limites, muevete a la otra zona.
        if (user.x_actual == n) user.x_actual = 0;
        if (user.x_actual == -1) user.x_actual = 19;
        if (user.y_actual == n) user.y_actual = 0;
        if (user.y_actual == -1) user.y_actual = 19;

    }

    let seleccionaAtraccion = () => {
        let atraccionesFiltradas = atracciones.filter((attr) => {
            if (attr && attr.tiempo < 60) { return attr }
        });

        console.log("Atracciones Filtradas:", atraccionesFiltradas)

        const numAtracciones = atraccionesFiltradas.length;

        if (numAtracciones == 0) {
            // Si no hay atracciones disponibles, quitate quitecito.
            console.log("ARRAY VACIO", numAtracciones);
            user.x_destino = user.x_actual;
            user.y_destino = user.y_actual;
            return;
        }

        const attrNum = randomIntFromInterval(0, numAtracciones - 1);

        // Provisional
        user.x_destino = Number(atraccionesFiltradas[attrNum].coordX);
        user.y_destino = Number(atraccionesFiltradas[attrNum].coordY);
    }


    // Métodos del renderizado del mapa

    let renderizarMapa = () => {
        setMatrix([...matrix]);
    }

    let definirImagenCasilla = (x, y, src) => {
        matrix[x][y].picture = src;
    }

    let escribirCasilla = (x, y, value) => {
        matrix[x][y].value = value;
    }

    let bordearCasilla = (x, y, border) => {
        matrix[x][y].border = border;
    }

    let colorearCasilla = (x, y, color) => {
        matrix[x][y].color = color;
    }


    // Métodos de la conexión de sockets.

    let bindSokets = () => {
        kafkaWebSocket.on("dato_recibido_usr", (usr) => {
            console.log("Usuario kafka", usr, "Usuario actual", user);

            if (usuarios[usr.id]) {
                bordearCasilla(usuarios[usr.id].x_actual, usuarios[usr.id].y_actual, "");
                colorearCasilla(usuarios[usr.id].x_actual, usuarios[usr.id].y_actual, "blue");
                escribirCasilla(usuarios[usr.id].x_actual, usuarios[usr.id].y_actual, " ");
            }

            if (user.id == usr.id)
                colorearCasilla(usr.x_actual, usr.y_actual, "green");
            else
                colorearCasilla(usr.x_actual, usr.y_actual, "#AF2908");

            escribirCasilla(usr.x_actual, usr.y_actual, usr.name);

            usuarios[usr.id] = usr;
            usuarios[usr.id].x_actual = Number(usuarios[usr.id].x_actual);
            usuarios[usr.id].y_actual = Number(usuarios[usr.id].y_actual);
            usuarios[usr.id].x_destino = Number(usuarios[usr.id].x_destino);
            usuarios[usr.id].y_destino = Number(usuarios[usr.id].y_destino);

        });

        socketRegistry.on("usuario_desconectado", (usr) => {
            console.log("Usuario Desconectado:", usr, usuarios, usuarios[usr.id]);

            bordearCasilla(usr.x_actual, usr.y_actual, "");
            colorearCasilla(usr.x_actual, usr.y_actual, "blue");
            escribirCasilla(usr.x_actual, usr.y_actual, " ");

            delete usuarios[usr.id];

        });

        socketRegistry.on("usuarioactual_desautenticado", () => {
            setUser({});
            history.push("/");
        });

        kafkaWebSocket.on("dato_recibido_attr", (attrarr) => {
            attrarr.map((attr) => {
                if (attr && atracciones[attr.id]) {

                    // Si la atraccion destino supera el tiempo, nos quedamos en el sitio, asi en el siguiente movimiento seleccionamos nueva atraccion.
                    if (attr.coordX == user.x_destino && attr.coordY == user.y_destino && attr.tiempo >= 60) {
                        user.x_destino = user.x_actual;
                        user.y_destino = user.y_actual;
                    }

                    if (atracciones[attr.id].coordX != attr.coordX || atracciones[attr.id].coordY != attr.coordY) {
                        colorearCasilla(atracciones[attr.id].coordX, atracciones[attr.id].coordY, "blue");
                        bordearCasilla(atracciones[attr.id].coordX, atracciones[attr.id].coordY, "");
                        escribirCasilla(atracciones[attr.id].coordX, atracciones[attr.id].coordY, "");
                    }

                    if (atracciones[attr.id].updatedAt != attr.updatedAt)
                        timers[attr.id] = 0;
                }
            });

            atracciones = attrarr;
        })
    }

    let unbindSockets = () => {
        socketRegistry.off("usuarioactual_desautenticado");
        kafkaWebSocket.off("dato_recibido_usr");
        kafkaWebSocket.off("dato_recibido_attr");
    }

    let desautenticar = (e = null) => {
        if (e)
            e.preventDefault();
        if (method == "rest") {
            Axios.get(REGISTRYADDRESS + "/logoff/" + user.id);
        }

        socketRegistry.emit("desautenticar_usuario", user);
    }


    return (
        <div className="container">

            {user.logged ?
                <div className="card text-white bg-dark mb-3 text-center mt-4 pt-4">
                    <div className="card-body">
                        <h5 className="card-title">
                            Nombre: {user.name}
                            &nbsp;&nbsp;
                            ID: {user.id}
                        </h5>
                        <h5 className="card-body">
                            Siguiente Posición: {user.x_actual}, {user.y_actual}
                            &nbsp;&nbsp;
                            Destino: {user.x_destino}, {user.y_destino}
                        </h5>
                        <code>
                            Password: {user.password}
                            <br />
                            Logged: {user.logged.toString()}
                        </code>
                    </div>
                </div>
                : ""}

            <div className="text-center my-3">
                <button onClick={desautenticar} className="btn btn-danger m-2"> Salir del parque.</button>
                <button onClick={(e) => { e.preventDefault(); history.push("/edit") }} className="btn btn-primary m-2"> Editar usuario.</button>
            </div>

            {matrix.map((i, ipos) => {

                return (
                    <div key={ipos} className="d-flex flex-row no-wrap justify-content-center">

                        {i.map((j, jpos) => {

                            return (
                                <div
                                    style={{
                                        minWidth: "60px",
                                        minHeight: "60px",
                                        textAlign: "center",
                                        color: "white",
                                        backgroundColor: matrix[ipos][jpos].color,
                                        border: matrix[ipos][jpos].border,
                                    }}
                                    className="card m-1"
                                    key={ipos + ", " + jpos}
                                >
                                    {matrix[ipos][jpos].picture ?
                                        <img src={matrix[ipos][jpos].picture} alt="salida" className="mx-auto" style={{ maxHeight: "60%", maxWidth: "60%" }} /> :
                                        ""
                                    }
                                    {matrix[ipos][jpos].value}
                                </div>
                            )
                        })}

                    </div>
                )

            })}
        </div>
    )

}

export default Map;