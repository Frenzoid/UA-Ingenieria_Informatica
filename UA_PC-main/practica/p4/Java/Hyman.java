
// java Hyman.java
// taskset -c 0 java Hyman.java

import java.lang.Math; // para random

public class Hyman extends Thread {
  static int n = 1;
  int turno = 0;

  static volatile int C[] = { 0, 0 };
  int hl1; // id de hilo
  int hl2; // id de hilo

  public void run() {
    try {
      for (;;) {
        C[hl1] = 1;
        while (turno != hl1) {
          while (C[hl2] == 1)
            ;
          turno = hl1;
        }

        // Espera Tiempo Aleatorio
        sleep((long) (100 * Math.random()));
        n = n + 1;
        System.out.println("En hilo " + hl1 + ", n = " + n);
        C[hl1] = 0;
        ;
      }
    } catch (InterruptedException e) {
      return;
    }
  }

  Hyman(int id) {
    this.hl1 = id;
    this.hl2 = (id == 1) ? 0 : 1;
  }

  public static void main(String args[]) {
    Thread thr1 = new Hyman(0);
    Thread thr2 = new Hyman(1);

    thr1.start();
    thr2.start();
  }
}