package ppss;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Assertions;
import static org.junit.jupiter.api.Assertions.*;

class DataArrayTest {


    @Test
    void DeleteC1() {
        // Entrada
        DataArray sut = new DataArray(new int[]{1,3,5,7});

        // Salida
        int[] arrEs = {1,3,7};
        int numElemEsperado = 3;

        // Llamar a sut
        assertDoesNotThrow(() -> sut.delete(5), "Excepción lanzada");
        assertAll("TestC1",
                () -> assertArrayEquals(arrEs, sut.getColeccion()),
                () -> assertEquals(numElemEsperado, sut.size())
        );
    }

    @Test
    void DeleteC2() {
        // Entrada
        DataArray sut = new DataArray(new int[]{1,3,3,5,7});

        // Salida
        int[] arrEs = {1,3,5,7};
        int numElemEsperado = 4;

        // Llamar a sut
        assertDoesNotThrow(() -> sut.delete(3), "Excepción lanzada");
        assertAll("TestC1",
                () -> assertArrayEquals(arrEs, sut.getColeccion()),
                () -> assertEquals(numElemEsperado, sut.size())
        );
    }

    @Test
    void DeleteC3() {
        // Entrada
        DataArray sut = new DataArray(new int[]{1,2,3,4,5,6,7,8,9,10});

        // Salida
        int[] arrEs = {1,2,3,5,6,7,8,9,10};
        int numElemEsperado = 9;

        // Llamar a sut
        assertDoesNotThrow(() -> sut.delete(4), "Excepción lanzada");
        assertAll("TestC1",
                () -> assertArrayEquals(arrEs, sut.getColeccion()),
                () -> assertEquals(numElemEsperado, sut.size())
        );
    }

    @Test
    void DeleteC4() {
        // Entrada
        DataArray sut = new DataArray();

        // Salida y comprobación de llada a sut
        DataException ex = assertThrows(DataException.class,
                () -> sut.delete(4));

        assertEquals("No hay elementos en la colección", ex.getMessage());
    }

    @Test
    void DeleteC5() {
        // Entrada
        DataArray sut = new DataArray(new int[]{1,3,5,7});

        // Salida y comprobación de llada a sut
        DataException ex = assertThrows(DataException.class,
                () -> sut.delete(-5));

        assertEquals("El valor a borrar debe ser > 0", ex.getMessage());
    }

    @Test
    void DeleteC6() {
        // Entrada
        DataArray sut = new DataArray();

        // Salida y comprobación de llada a sut
        DataException ex = assertThrows(DataException.class,
                () -> sut.delete(0));

        assertEquals("Colección vacía. Y el valor a borrar debe ser > 0", ex.getMessage());
    }

    @Test
    void DeleteC7() {
        // Entrada
        DataArray sut = new DataArray(new int[]{1,3,5,7});

        // Salida y comprobación de llada a sut
        DataException ex = assertThrows(DataException.class,
                () -> sut.delete(8));

        assertEquals("Elemento no encontrado", ex.getMessage());
    }
}