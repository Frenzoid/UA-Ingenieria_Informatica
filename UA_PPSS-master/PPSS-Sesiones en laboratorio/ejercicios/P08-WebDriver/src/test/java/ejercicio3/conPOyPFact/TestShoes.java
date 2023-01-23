package ejercicio3.conPOyPFact;
import org.junit.jupiter.api.*;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.chrome.ChromeOptions;
import org.openqa.selenium.support.PageFactory;


public class TestShoes {
    public WebDriver driver;
    public MyAccountPage accPage;

    @BeforeAll
    static void init() {
        System.setProperty("webdriver.chrome.driver",
                "./src/test/resources/drivers/chromedriver.exe");
        Cookies.storeCookiesToFile("USR0004@test.com", "USR0004");
    }

    @BeforeEach
    public void setUp() {
        ChromeOptions chromeOptions = new ChromeOptions();
        chromeOptions.setHeadless(Boolean.parseBoolean(System.getProperty("chromeHeadless")));

        driver = new ChromeDriver(chromeOptions);
        driver.manage().window().maximize();

        Cookies.loadCookiesFromFile(driver);

        driver.get("http://demo-store.seleniumacademy.com/customer/account/");
        accPage = PageFactory.initElements(driver, MyAccountPage.class);
    }

    @Test
    public void compareShoes() {
        // 1 //
        Assertions.assertEquals("My Account", accPage.getTile());

        // 2 //
        ShoesPage shoesPage = accPage.accessShoesPage();

        // 3 //
        Assertions.assertEquals("Shoes - Accessories", shoesPage.getTile());

        // 4 //
        shoesPage.selectShoeToCompare(5);
        shoesPage.selectShoeToCompare(6);

        // 5 //
        ProductComparisonPage compPage = shoesPage.submitCompare();

        // 6 //
        Assertions.assertEquals("Products Comparison List - Magento Commerce", compPage.getTile());

        // 7 //
        shoesPage = compPage.close();

        // 8 //
        Assertions.assertEquals("Shoes - Accessories", shoesPage.getTile());

        // 9 //
        shoesPage.ClearComparison();

        // 10 //
        Assertions.assertEquals("The comparison list was cleared.", shoesPage.getMessageSpanValue());
    }


    // @AfterEach
    public void finish(){
       driver.close();
    }
}
