import React, { useEffect, useState } from 'react';
import { useHistory } from "react-router-dom";
import { REGISTRYADDRESS } from '../configs/parametros';
import * as Axios from "axios";

function Register(props) {
    const history = useHistory();
    const socketRegistry = props.socketRegistry;
    const method = props.method;

    const [user, setUser] = [props.user, props.setUser];
    const [errorMsg, setErrorMsg] = useState("");
    let pass2 = "";

    useEffect(() => {
        // Si el usuario ya esta registrado, no le permitimos acceder a esta página.
        if (user.logged)
            history.push("/map");

        bindSokets();

        return () => { unbindSockets(); }

    }, []);

    let bindSokets = () => {
        socketRegistry.on("usuario_registrado", (registeredUser) => {
            setUser(registeredUser);
            history.push("/");
        });

        socketRegistry.on("error_registry", (err) => { setErrorMsg(err) });
    };

    let unbindSockets = () => {
        socketRegistry.off("error_registry");
        socketRegistry.off("usuario_registrado");
    }

    let registrarse = (e) => {
        e.preventDefault();

        if (!user.name || !user.password)
            setErrorMsg("Faltan datos!");
        else if (pass2 != user.password)
            setErrorMsg("Las contraseñas no coinciden.");
        else {
            if (method == "rest") {
                Axios.post(REGISTRYADDRESS + '/register',
                    user, { timeout: 1000 }
                ).then((response) => {
                    setUser(response.data);
                    history.push("/");
                }).catch((err) => {
                    console.log(err);
                    setErrorMsg(err.response.data.message);
                });
            } else if (method == "sockets") {
                socketRegistry.emit("registrar_usuario", user);
            }

        }
    }


    return (
        <div className="container">
            <div>
                <h1 className="text-center mt-3">
                    {user.name ? "¡ Registrando " + user.name + " !" : "Registrarse"}
                </h1>

                <form>
                    <div className="form-group p-0 mb-3">
                        <label>Name</label>
                        <input onChange={(e) => { setUser({ ...user, name: e.target.value }); }} className="form-control" placeholder="Introduce tu name de user"></input>
                    </div>
                    <div className="form-check p-0 mb-3">
                        <label>Password</label>
                        <input onChange={(e) => { setUser({ ...user, password: e.target.value }) }} className="form-control" placeholder="Introduce tu contraseña" type="password"></input>
                    </div>
                    <div className="form-check p-0 mb-3">
                        <label>Confirm Password</label>
                        <input onChange={(e) => { pass2 = e.target.value }} className="form-control" placeholder="Confirmar contraseña" type="password"></input>
                    </div>
                    <button onClick={registrarse} className="btn btn-success">
                        Registrarse!
                    </button>
                    <button onClick={() => { history.push("/login") }} className="btn btn-primary ms-2">
                        Ya tines cuenta? Autenticate.
                    </button>
                </form>

                {!errorMsg ? "" :
                    <div style={{ width: "100%" }} className="card card-header bg-danger text-white text-center mt-3">
                        {errorMsg}
                    </div>
                }
            </div >
        </div >
    )

}

export default Register;