use crossbeam_utils::sync::ShardedLock;

fn main() {
    // Variable con bloqueos.
    let lock = ShardedLock::new(5);

    // Se pueden crear más de un lector.
    {
        let lector1_variable = lock.read().unwrap();
        let lector2_variable = lock.read().unwrap();
        println!("{}", lector1_variable); // 5
        println!("{}", lector2_variable); // 5
    } // Los lectores dejan de existir una vez fuera del ámbito.

    // Solo se puede tener un escritor por ámbito.
    {
        let mut w = lock.write().unwrap();
        *w += 1;
        println!("{}", w); // 6
    } // El escritor deja de existir una ve fuera del ámbito.

    {
        let lector1_variable = lock.read().unwrap();
        println!("{}", lector1_variable); // 6
    } // Los lectores dejan de existir una vez fuera del ámbito.
}
