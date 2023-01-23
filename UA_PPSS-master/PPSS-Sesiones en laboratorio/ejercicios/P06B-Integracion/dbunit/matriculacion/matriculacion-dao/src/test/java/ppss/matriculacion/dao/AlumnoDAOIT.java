package ppss.matriculacion.dao;

import org.dbunit.Assertion;
import org.dbunit.IDatabaseTester;
import org.dbunit.database.IDatabaseConnection;
import org.dbunit.dataset.IDataSet;
import org.dbunit.dataset.ITable;
import org.dbunit.util.fileloader.FlatXmlDataFileLoader;

import org.junit.jupiter.api.*;
import ppss.matriculacion.to.AlumnoTO;

import java.time.LocalDate;


// ESTRATEGIA DE INTEGRACIÓN: BOTTOM UP

@Tag("Integracion-fase1")
public class AlumnoDAOIT {

    private IDatabaseTester databaseTester;
    private IDatabaseConnection connection;

    @BeforeEach
    public void setUp() throws Exception {

        String cadena_conexionDB = "jdbc:mysql://oldbox.cloud:32768/matriculacion?useSSL=false";
        databaseTester = new MiJdbcDatabaseTester("com.mysql.cj.jdbc.Driver", cadena_conexionDB, "root", "ppss");
        connection = databaseTester.getConnection();
    }

    @Test
    public void testA1() throws Exception {
        IDataSet dataSet = new FlatXmlDataFileLoader().load("/tabla2.xml");
        databaseTester.setDataSet(dataSet);
        databaseTester.onSetup();

        AlumnoTO al = new AlumnoTO();
        al.setNif("33333333C");
        al.setNombre("Elena Aguirre Juarez");
        al.setFechaNacimiento(LocalDate.of(1985, 02, 22));

        Assertions.assertDoesNotThrow(()-> new FactoriaDAO().getAlumnoDAO().addAlumno(al));

        IDataSet databaseDataSet = connection.createDataSet();
        ITable actualTable = databaseDataSet.getTable("alumnos");

        IDataSet expectedDataSet = new FlatXmlDataFileLoader().load("/tabla3.xml");
        ITable expectedTable = expectedDataSet.getTable("alumnos");

        Assertion.assertEquals(expectedTable, actualTable);
    }

    @Test
    public void testA2() throws Exception {
        IDataSet dataSet = new FlatXmlDataFileLoader().load("/tabla2.xml");
        databaseTester.setDataSet(dataSet);
        databaseTester.onSetup();

        AlumnoTO al = new AlumnoTO();
        al.setNif("11111111A");
        al.setNombre("Alfonso Ramirez Ruiz");
        al.setFechaNacimiento(LocalDate.of(1982, 02, 22));

        Exception ex = Assertions.assertThrows(DAOException.class, ()-> new FactoriaDAO().getAlumnoDAO().addAlumno(al));
        Assertions.assertEquals("Error al conectar con BD", ex.getMessage());
    }

    @Test
    public void testA3() throws Exception {
        IDataSet dataSet = new FlatXmlDataFileLoader().load("/tabla2.xml");
        databaseTester.setDataSet(dataSet);
        databaseTester.onSetup();

        AlumnoTO al = new AlumnoTO();
        al.setNif("44444444D");
        al.setNombre(null);
        al.setFechaNacimiento(LocalDate.of(1982, 02, 22));

        Exception ex = Assertions.assertThrows(DAOException.class, ()-> new FactoriaDAO().getAlumnoDAO().addAlumno(al));
        Assertions.assertEquals("Error al conectar con BD", ex.getMessage());
    }

    @Test
    public void testA4() throws Exception {
        IDataSet dataSet = new FlatXmlDataFileLoader().load("/tabla2.xml");
        databaseTester.setDataSet(dataSet);
        databaseTester.onSetup();

        AlumnoTO al = null;

        Exception ex = Assertions.assertThrows(DAOException.class, ()-> new FactoriaDAO().getAlumnoDAO().addAlumno(al));
        Assertions.assertEquals("Alumno nulo", ex.getMessage());
    }

    @Test
    public void testA5() throws Exception {
        IDataSet dataSet = new FlatXmlDataFileLoader().load("/tabla2.xml");
        databaseTester.setDataSet(dataSet);
        databaseTester.onSetup();

        AlumnoTO al = new AlumnoTO();
        al.setNif(null);
        al.setNombre("Pedro Garcia Lopez");
        al.setFechaNacimiento(LocalDate.of(1982, 02, 22));

        Exception ex = Assertions.assertThrows(DAOException.class, ()-> new FactoriaDAO().getAlumnoDAO().addAlumno(al));
        Assertions.assertEquals("Error al conectar con BD", ex.getMessage());
    }

    @Test
    public void testB1() throws Exception {
        IDataSet dataSet = new FlatXmlDataFileLoader().load("/tabla2.xml");
        databaseTester.setDataSet(dataSet);
        databaseTester.onSetup();

        Assertions.assertDoesNotThrow(()-> new FactoriaDAO().getAlumnoDAO().delAlumno("11111111A"));

        IDataSet databaseDataSet = connection.createDataSet();
        ITable actualTable = databaseDataSet.getTable("alumnos");

        IDataSet expectedDataSet = new FlatXmlDataFileLoader().load("/tabla4.xml");
        ITable expectedTable = expectedDataSet.getTable("alumnos");

        Assertion.assertEquals(expectedTable, actualTable);
    }

    @Test
    public void testB2() throws Exception {
        IDataSet dataSet = new FlatXmlDataFileLoader().load("/tabla2.xml");
        databaseTester.setDataSet(dataSet);
        databaseTester.onSetup();

        Exception ex = Assertions.assertThrows(DAOException.class, ()-> new FactoriaDAO().getAlumnoDAO().delAlumno("33333333C"));
        Assertions.assertEquals("No se ha borrado ningun alumno", ex.getMessage());
    }
}

