package ppss;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import java.util.Arrays;
import static org.junit.jupiter.api.Assertions.*;

class CineTest {
    Cine sut;

    @BeforeEach
    void setup(){
        sut = new Cine();
    }

    @Test
    void reservaButacasC1() {
        boolean[] asientosEntrada = new boolean[3];
        Arrays.fill(asientosEntrada, Boolean.FALSE);

        boolean[] asientosSalida = new boolean[3];
        Arrays.fill(asientosSalida, Boolean.FALSE);
        asientosSalida[0] = true;

        assertTrue(sut.reservaButacas(asientosEntrada, 1));
        assertArrayEquals(asientosEntrada, asientosSalida);
    }

    @Test
    void reservaButacasC2() {
        boolean[] asientosEntrada = new boolean[1];
        Arrays.fill(asientosEntrada, Boolean.TRUE);

        boolean[] asientosSalida = new boolean[1];
        Arrays.fill(asientosSalida, Boolean.TRUE);
        asientosSalida[0] = true;

        assertFalse(sut.reservaButacas(asientosEntrada, 1));
        assertArrayEquals(asientosEntrada, asientosSalida);
    }

    @Test
    void reservaButacasC3() {
        boolean[] asientosEntrada = new boolean[3];
        Arrays.fill(asientosEntrada, Boolean.FALSE);

        boolean[] asientosSalida = new boolean[3];
        Arrays.fill(asientosSalida, Boolean.FALSE);
        asientosSalida[0] = true;

        assertTrue(sut.reservaButacasV1(asientosEntrada, 1));
        assertArrayEquals(asientosEntrada, asientosSalida);
    }

    @Test
    void reservaButacasC4() {
        boolean[] asientosEntrada = new boolean[1];
        Arrays.fill(asientosEntrada, Boolean.TRUE);

        boolean[] asientosSalida = new boolean[1];
        Arrays.fill(asientosSalida, Boolean.TRUE);
        asientosSalida[0] = true;

        assertFalse(sut.reservaButacasV1(asientosEntrada, 1));
        assertArrayEquals(asientosEntrada, asientosSalida);
    }
}