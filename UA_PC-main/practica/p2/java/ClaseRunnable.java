public class ClaseRunnable implements Runnable {
    String palabra;
    int veces = 10;

    public ClaseRunnable(String palabra) {
        this.palabra = palabra;
    }

    public void run() {
        for (int i = 0; i < veces; i++) {
            System.out.println(palabra);
        }
    }

    public static void main(String[] args) {
        ClaseRunnable h1 = new ClaseRunnable("h1");
        ClaseRunnable h2 = new ClaseRunnable("h2");

        Thread t1 = new Thread(h1);
        Thread t2 = new Thread(h2);

        t1.setPriority(1);

        t1.start();
        t2.start();

        System.out.println("Padre finalizado");
    }

}
