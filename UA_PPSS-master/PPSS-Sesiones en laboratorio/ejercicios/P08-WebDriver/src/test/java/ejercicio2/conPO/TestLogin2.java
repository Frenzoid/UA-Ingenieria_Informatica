package ejercicio2.conPO;
import ejercicio3.conPOyPFact.Cookies;
import org.junit.jupiter.api.*;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.chrome.ChromeDriver;

public class TestLogin2 {
    WebDriver driver;
    HomePage homePage;

    @BeforeAll
    static void init() {
        System.setProperty("webdriver.chrome.driver",
                "./src/test/resources/drivers/chromedriver.exe");
    }

    @BeforeEach
    public void setUp() {
        driver = new ChromeDriver();
        driver.manage().window().maximize();
        homePage = new HomePage(driver);
    }

    @Test
    public void test_Login_Correct() {
        Assertions.assertEquals("Madison Island", homePage.getTile());

        CustomerLoginPage clp = homePage.accessCustomerLoginPage();
        Assertions.assertEquals("Customer Login", clp.getTile());

        MyAccountPage maccp = clp.validLogin("USR0004@test.com", "USR0004");
        Assertions.assertEquals("My Account", maccp.getTile());
    }

    @Test
    public void test_Login_Incorrect() {
        Assertions.assertEquals("Madison Island", homePage.getTile());

        CustomerLoginPage clp = homePage.accessCustomerLoginPage();
        Assertions.assertEquals("Customer Login", clp.getTile());

        MyAccountPage maccp = clp.validLogin("USR0004@test.com", "USR0004");
        Assertions.assertEquals("My Account", maccp.getTile());
    }

    @AfterEach
    public void finish(){
        driver.close();
    }
}
