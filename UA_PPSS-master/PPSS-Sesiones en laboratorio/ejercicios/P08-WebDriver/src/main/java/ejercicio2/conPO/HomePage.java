package ejercicio2.conPO;
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.chrome.ChromeDriver;

import java.time.Duration;

public class HomePage {
    WebDriver driver;
    WebElement accountDrop;
    WebElement loginLink;

    public HomePage(WebDriver sourceDriver) {
        // Me traigo el driver del los test, porque ahi en el @beforeEach nos encargaremos de arrancar el navegador, y cerrarlo en @afterEach.
        driver = sourceDriver;

        driver.get("http://demo-store.seleniumacademy.com/");
        driver.manage().timeouts().implicitlyWait(Duration.ofSeconds(10));

        accountDrop = driver.findElement(By.xpath("//*[@id='header']/div/div[2]/div/a"));
    }

    public CustomerLoginPage accessCustomerLoginPage() {
        accountDrop.click();
        loginLink = driver.findElement(By.linkText("Log In"));
        loginLink.click();

        return new CustomerLoginPage(driver);
    }

    public String getTile(){
        return driver.getTitle();
    }

}
