package ppss;

import org.dbunit.Assertion;
import org.dbunit.IDatabaseTester;
import org.dbunit.JdbcDatabaseTester;
import org.dbunit.database.DatabaseConfig;
import org.dbunit.database.IDatabaseConnection;
import org.dbunit.dataset.IDataSet;
import org.dbunit.dataset.IRowValueProvider;
import org.dbunit.dataset.ITable;
import org.dbunit.dataset.xml.FlatDtdDataSet;
import org.dbunit.util.fileloader.FlatXmlDataFileLoader;

import org.dbunit.ext.mysql.MySqlDataTypeFactory;
import org.junit.jupiter.api.*;
import ppss.Cliente;
import ppss.ClienteDAO;

/* IMPORTANTE:
    Dado que prácticamente todos los métodos de dBUnit lanzan una excepción,
    vamos a usar "throws Exeption" en los métodos, para que el código quede más
    legible sin necesidad de usar un try..catch o envolver cada sentencia dbUnit 
    con un assertDoesNotThrow()
*/

public class ClienteDAO_IT {
  
  private ClienteDAO clienteDAO; //SUT
  private IDatabaseTester databaseTester;
  private IDatabaseConnection connection;

  @BeforeEach
  public void setUp() throws Exception {

    String cadena_conexionDB = "jdbc:mysql://oldbox.cloud:32768/DBUNIT?useSSL=false";
    databaseTester = new MiJdbcDatabaseTester("com.mysql.cj.jdbc.Driver",
            cadena_conexionDB, "root", "ppss");
    //obtenemos la conexión con la BD
    connection = databaseTester.getConnection();
    clienteDAO = new ClienteDAO();
  }

  @Test
  public void testInsert() throws Exception {
    Cliente cliente = new Cliente(1,"John", "Smith");
    cliente.setDireccion("1 Main Street");
    cliente.setCiudad("Anycity");

    //Inicializamos el dataSet con los datos iniciales de la tabla cliente
    IDataSet dataSet = new FlatXmlDataFileLoader().load("/cliente-init.xml");

    //Inyectamos el dataset en el objeto databaseTester
    databaseTester.setDataSet(dataSet);

    //inicializamos la base de datos con los contenidos del dataset
    databaseTester.onSetup();

     //invocamos a nuestro SUT
    Assertions.assertDoesNotThrow(()-> clienteDAO.insert(cliente));

    //recuperamos los datos de la BD después de invocar al SUT
    IDataSet databaseDataSet = connection.createDataSet();
    //Recuperamos los datos de la tabla cliente
    ITable actualTable = databaseDataSet.getTable("cliente"); 

    //creamos el dataset con el resultado esperado
    IDataSet expectedDataSet = new FlatXmlDataFileLoader().load("/cliente-esperado.xml");
    ITable expectedTable = expectedDataSet.getTable("cliente");

    Assertion.assertEquals(expectedTable, actualTable);

   }

  @Test
  public void testDelete() throws Exception {
    Cliente cliente =  new Cliente(1,"John", "Smith");
    cliente.setDireccion("1 Main Street");
    cliente.setCiudad("Anycity");

    //inicializamos la BD
    IDataSet dataSet = new FlatXmlDataFileLoader().load("/cliente-esperado.xml");
    databaseTester.setDataSet(dataSet);
    databaseTester.onSetup();

    //invocamos a nuestro SUT
    Assertions.assertDoesNotThrow(()->clienteDAO.delete(cliente));

    IDataSet databaseDataSet = connection.createDataSet();
    //Recuperamos los datos de la tabla cliente
    ITable actualTable = databaseDataSet.getTable("cliente");
    
    //creamos el dataset con el resultado esperado
    IDataSet expectedDataSet = new FlatXmlDataFileLoader().load("/cliente-init.xml");
    ITable expectedTable = expectedDataSet.getTable("cliente");

    Assertion.assertEquals(expectedTable, actualTable);
  }

  @Test
  public void test_insert2() throws Exception {
    Cliente cliente = new Cliente(3,"Napoles", "Smith");

    cliente.setDireccion("1 Main Street");
    cliente.setCiudad("Anycity");

    IDataSet dataSet = new FlatXmlDataFileLoader().load("/cliente-init_2.xml");

    databaseTester.setDataSet(dataSet);
    databaseTester.onSetup();

    Assertions.assertDoesNotThrow(()-> clienteDAO.insert(cliente));

    IDataSet databaseDataSet = connection.createDataSet();
    ITable actualTable = databaseDataSet.getTable("cliente");

    IDataSet expectedDataSet = new FlatXmlDataFileLoader().load("/cliente-esperado_2.xml");
    ITable expectedTable = expectedDataSet.getTable("cliente");

    Assertion.assertEquals(expectedTable, actualTable);
  }

  @Test
  public void test_delete2() throws Exception {
    Cliente cliente = new Cliente(3,"Napoles", "Smith");

    IDataSet dataSet = new FlatXmlDataFileLoader().load("/cliente-esperado_2.xml");

    databaseTester.setDataSet(dataSet);
    databaseTester.onSetup();

    Assertions.assertDoesNotThrow(()-> clienteDAO.delete(cliente));


    // Contrastes:
    IDataSet databaseDataSet = connection.createDataSet();
    ITable actualTable = databaseDataSet.getTable("cliente");

    IDataSet expectedDataSet = new FlatXmlDataFileLoader().load("/cliente-init_2.xml");
    ITable expectedTable = expectedDataSet.getTable("cliente");

    Assertion.assertEquals(expectedTable, actualTable);
  }

  @Test
  public void testUpdate() throws Exception {
    IDataSet dataset = new FlatXmlDataFileLoader().load("/cliente-init_actualizar.xml");
    databaseTester.setDataSet(dataset);
    databaseTester.onSetup();

    Cliente c =  new Cliente(1,"John", "Smith");
    c.setDireccion("Other Street");
    c.setCiudad("NewCity");

    Assertions.assertDoesNotThrow(() -> clienteDAO.update(c));

    IDataSet databaseDataset = connection.createDataSet();
    ITable actualTable = databaseDataset.getTable("cliente");

    IDataSet expectedDataset = new FlatXmlDataFileLoader().load("/cliente-actualizar.xml");
    ITable expectedTable = expectedDataset.getTable("cliente");

    Assertion.assertEquals(expectedTable, actualTable);

  }

  @Test
  public void testRetrieve() throws  Exception {
    // Incializamos la base de datos basado desde un xml.
    IDataSet dataset = new FlatXmlDataFileLoader().load("/cliente-init_actualizar.xml");
    ITable expectedTable = dataset.getTable("cliente");

    databaseTester.setDataSet(dataset);
    databaseTester.onSetup();

    IDataSet databaseDataset = connection.createDataSet();
    ITable actualTable = databaseDataset.getTable("cliente");

    Cliente c;
    c = Assertions.assertDoesNotThrow(() -> clienteDAO.retrieve(1));

    Assertions.assertAll(
      // ¿¿¿ HAY QUE COMPROBAR EL ESTAODO DE LA BASE DE DATOS ADEMÁS DEL VALOR QUE DEVUELVE ???
      () -> Assertion.assertEquals(expectedTable, actualTable),

      () -> Assertions.assertEquals(actualTable.getValue(0, "nombre"), c.getNombre()),
      () -> Assertions.assertEquals(actualTable.getValue(0, "apellido"), c.getApellido()),
      () -> Assertions.assertEquals(actualTable.getValue(0, "direccion"), c.getDireccion()),
      () -> Assertions.assertEquals(actualTable.getValue(0, "ciudad"), c.getCiudad())
    );

  }
}
