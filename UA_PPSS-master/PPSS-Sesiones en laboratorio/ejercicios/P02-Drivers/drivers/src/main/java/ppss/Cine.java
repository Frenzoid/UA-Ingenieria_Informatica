package ppss;

public class Cine {
    public boolean reservaButacas(boolean[] asientos, int solicitados) {
        boolean reserva = false;
        int j = 0;
        int sitiosLibres = 0;
        int primerLibre;
        if (solicitados >0) {  //este if lo añadimos por el test C5
            while ((j < asientos.length) && (sitiosLibres < solicitados)) {
                if (!asientos[j]) {
                    sitiosLibres++;
                } else {
                    sitiosLibres = 0;
                }
                j++;
            }
            if (sitiosLibres == solicitados) {
                primerLibre = (j - solicitados);
                reserva = true;
                for (int k = primerLibre; k < (primerLibre + solicitados); k++) {
                    asientos[k] = true;
                }
            }
        }
        return reserva;
    }

    //versión publicada a los alumnos
    public boolean reservaButacasV1(boolean[] asientos, int solicitados) {
        boolean reserva = false;
        int j = 0;
        int sitiosLibres = 0;
        int primerLibre;

        while ((j < asientos.length) && (sitiosLibres < solicitados)) {
            if (!asientos[j]) {
                sitiosLibres++;
            } else {
                sitiosLibres = 0;
            }
            j++;
        }
        if (sitiosLibres == solicitados) {
            primerLibre = (j - solicitados);
            reserva = true;
            for (int k = primerLibre; k < (primerLibre + solicitados); k++) {
                asientos[k] = true;
            }
        }

        return reserva;
    }
}
