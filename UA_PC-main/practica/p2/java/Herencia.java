public class Herencia extends Thread {
    String palabra;
    int veces = 10;

    public Herencia(String palabra) {
        this.palabra = palabra;
    }

    public void run() {
        for (int i = 0; i < veces; i++) {
            System.out.println(palabra);
        }
    }

    public static void main(String[] args) {
        Thread h1 = new Herencia("h1");
        Thread h2 = new Herencia("h2");

        h1.start();
        h2.start();

        System.out.println("Padre finalizado");
    }
}