use crossbeam_channel::unbounded;

fn main() {
    // Creamos un canal sin limites de mensajes.
    let (s, r) = unbounded();

    // Mandamos un mensaje al canal.
    s.send("Hola Mundo!!").unwrap();

    // Recibimos el mensaje del canal.
    println!("{}", r.recv().unwrap()); // "Hola Mundo!!".
}
