import { useEffect, useState } from 'react';
import { APIENGINE, REQUESTTIME } from "../configs/parametros";
import * as Axios from "axios"

function Map() {
    const [matrix, setMatrix] = useState([]);
    const [errorMsg, setErrorMsg] = useState("");

    useEffect(() => {

        const inter = setInterval(async () => {
            limpiarMapa();

            await Axios.get(APIENGINE + '/usuarios', { timeout: 5000 }).then((data) => {
                setErrorMsg("");
                data.data.forEach(usr => {
                    if (usr.logged) {
                        colorearCasilla(usr.x_actual, usr.y_actual, "#AF2908");
                        escribirCasilla(usr.x_actual, usr.y_actual, usr.name);
                    }
                })
            }).catch(err => setErrorMsg(err.message));

            await Axios.get(APIENGINE + '/atracciones', { timeout: 5000 }).then((data) => {
                setErrorMsg("");
                data.data.forEach(attr => {
                    colorearCasilla(attr.coord_x, attr.coord_y, "purple");
                    escribirCasilla(attr.coord_x, attr.coord_y, attr.time);
                    definirImagenCasilla(attr.coord_x, attr.coord_y, attr.picture);
                    bordearCasilla(attr.coord_x, attr.coord_y, "");

                    if (attr.time >= 60)
                        bordearCasilla(attr.coord_x, attr.coord_y, "10px solid red");

                    if (attr.time == 1000) {
                        bordearCasilla(attr.coord_x, attr.coord_y, "10px solid grey");
                        escribirCasilla(attr.coord_x, attr.coord_y, "Mala tmp.");
                    }
                })
            }).catch(err => setErrorMsg(err.message));

            renderizarMapa();

        }, REQUESTTIME);

        // Parar el bucle cuando se desrenderice el componente ( cuando se cambia a otra página )
        return () => {
            clearInterval(inter);
        }

    }, []);


    let limpiarMapa = () => {
        const n = 20;

        for (let i = 0; i < n; i++) {
            matrix[i] = [];
            for (let j = 0; j < n; j++) {
                matrix[i][j] = { color: "blue", value: " " }
            }
        }
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

    return (
        <div className="container">
            {errorMsg ?
                <div style={{ width: "100%" }} className="card card-header bg-danger text-white text-center mt-3">
                    {errorMsg}
                    <div className="text-center mt-2">
                        <div className="spinner-border">
                            <span className="sr-only"></span>
                        </div>
                    </div>
                </div> : ""
            }
            {matrix.length == 0 ?
                <div className="text-center">
                    <img src={"https://i.imgur.com/6Hq8096.gif"} className="mx-auto" />
                </div>
                : matrix.map((i, ipos) => {

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

                })
            }


        </div>
    )

}

export default Map;