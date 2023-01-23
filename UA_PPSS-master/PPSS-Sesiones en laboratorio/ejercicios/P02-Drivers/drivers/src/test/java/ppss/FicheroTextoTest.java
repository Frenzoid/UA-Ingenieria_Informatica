package ppss;

import org.junit.jupiter.api.Tag;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Assertions;
import static org.junit.jupiter.api.Assertions.*;

class FicheroTextoTest {

    FicheroTexto sut = new FicheroTexto();

    @Test
    void contarCaracteresC1() {
        FicheroException ex = assertThrows(FicheroException.class,
                () -> sut.contarCaracteres("ficheroC1.txt"));

        assertEquals("ficheroC1.txt (No existe el fichero o directorio)", ex.getMessage());
    }

    @Test
    void contarCaracteresC2() {
        assertDoesNotThrow(() -> assertEquals(3, sut.contarCaracteres("src/test/resources/ficheroCorrecto.txt")));
    }

    @Tag("excluidos")
    @Test
    void contarCaracteresC3() {
        Assertions.fail();
    }

    @Tag("excluidos")
    @Test
    void contarCaracteresC5() {
        Assertions.fail();
    }
}