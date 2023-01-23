
use crossbeam_utils::thread::scope;
use std::thread;
use std::time::Duration;

fn main(){
 // Variable vector.
 let var_vec = vec![1, 2, 3];

 // Scope
 scope(|s| {

     // Hilo
     s.spawn(|_| {
         println!("Un proceso hijo tomando prestado la variable varVec: {:?}", var_vec);
     });
     
      // Hilo
     s.spawn(|_| {
         println!("Otro proceso hijo tomando prestado la variable varVec: {:?}", var_vec);
         println!("Me duermo 2 segundos...");
         thread::sleep(Duration::from_millis(2000));
     });

 }).unwrap();
 
 println!("Este mensaje aparecerá cuando los hijos acaben.");
 
}