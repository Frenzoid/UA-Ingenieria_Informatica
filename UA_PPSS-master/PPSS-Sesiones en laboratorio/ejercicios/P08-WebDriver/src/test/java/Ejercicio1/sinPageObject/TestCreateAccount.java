package Ejercicio1.sinPageObject;

import org.junit.jupiter.api.*;

import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.chrome.ChromeDriver;

import java.time.Duration;


public class TestCreateAccount {

    public WebDriver driver;

    @BeforeAll
    static void init() {
        System.setProperty("webdriver.chrome.driver",
                "./src/test/resources/drivers/chromedriver.exe");
    }

    @BeforeEach
    public void setUp() {
        driver = new ChromeDriver();
        driver.manage().window().maximize();
        driver.get("http://demo-store.seleniumacademy.com/");
        driver.manage().timeouts().implicitlyWait(Duration.ofSeconds(10));
    }

    @Test
    @Tag("OnlyOnce")
    public void createAccount() {
        Assertions.assertEquals("Madison Island", driver.getTitle());

        driver.findElement(By.xpath("//*[@id='header']/div/div[2]/div/a")).click();
        driver.findElement(By.linkText("Log In")).click();
        driver.manage().timeouts().implicitlyWait(Duration.ofSeconds(10));

        Assertions.assertEquals("Customer Login", driver.getTitle());

        driver.findElement(By.cssSelector("a[title='Create an Account']")).click();

        Assertions.assertEquals("Create New Customer Account", driver.getTitle());

        driver.findElement(By.cssSelector("input#firstname")).sendKeys("USR0004");
        driver.findElement(By.cssSelector("input#middlename")).sendKeys("USR0004");
        driver.findElement(By.cssSelector("input#lastname")).sendKeys("USR0004");
        driver.findElement(By.cssSelector("input#password")).sendKeys("USR0004");
        driver.findElement(By.cssSelector("input#email_address")).sendKeys("USR0004@test.com");
        driver.findElement(By.cssSelector("form#form-validate")).submit();

        Assertions.assertEquals("This is a required field.", driver.findElement(By.cssSelector("div#advice-required-entry-confirmation")).getText());

        driver.findElement(By.cssSelector("input#confirmation")).sendKeys("USR0004");
        driver.findElement(By.cssSelector("form#form-validate")).submit();
        driver.manage().timeouts().implicitlyWait(Duration.ofSeconds(10));

        Assertions.assertEquals("My Account", driver.getTitle());
    }

    @AfterEach
    public void finish(){
        driver.close();
    }
}
