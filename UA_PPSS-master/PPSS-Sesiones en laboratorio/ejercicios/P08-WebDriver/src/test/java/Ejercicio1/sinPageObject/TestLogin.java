package Ejercicio1.sinPageObject;
import org.junit.jupiter.api.*;
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.chrome.ChromeDriver;

import java.time.Duration;

public class TestLogin {
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
    public void loginOK(){
        Assertions.assertEquals("Madison Island", driver.getTitle());

        driver.findElement(By.xpath("//*[@id='header']/div/div[2]/div/a")).click();
        driver.findElement(By.linkText("Log In")).click();
        driver.manage().timeouts().implicitlyWait(Duration.ofSeconds(10));

        Assertions.assertEquals("Customer Login", driver.getTitle());

        driver.findElement(By.cssSelector("input#email")).sendKeys("USR0004@test.com");
        driver.findElement(By.cssSelector("form#login-form")).submit();

        Assertions.assertEquals("This is a required field.", driver.findElement(By.cssSelector("div#advice-required-entry-pass")).getText());

        driver.findElement(By.cssSelector("input#pass")).sendKeys("USR0004");
        driver.findElement(By.cssSelector("form#login-form")).submit();
        driver.manage().timeouts().implicitlyWait(Duration.ofSeconds(10));

        Assertions.assertEquals("My Account", driver.getTitle());
    }

    @Test
    public void loginFailed(){
        Assertions.assertEquals("Madison Island", driver.getTitle());

        driver.findElement(By.xpath("//*[@id='header']/div/div[2]/div/a")).click();
        driver.findElement(By.linkText("Log In")).click();

        Assertions.assertEquals("Customer Login", driver.getTitle());

        driver.findElement(By.cssSelector("input#email")).sendKeys("USR0004@test.com");
        driver.findElement(By.cssSelector("form#login-form")).submit();

        Assertions.assertEquals("This is a required field.", driver.findElement(By.cssSelector("div#advice-required-entry-pass")).getText());

        driver.findElement(By.cssSelector("input#pass")).sendKeys("MALPASS");
        driver.findElement(By.cssSelector("form#login-form")).submit();
        driver.manage().timeouts().implicitlyWait(Duration.ofSeconds(10));

        Assertions.assertEquals("Invalid login or password.", driver.findElement(By.xpath("//*[@id=\"top\"]/body/div/div[2]/div[2]/div/div/div[2]/ul/li/ul/li/span")).getText());
    }

    @AfterEach
    public void finish(){
        driver.close();
    }
}
