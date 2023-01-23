package ejercicio2.conPO;

import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;

import java.time.Duration;

public class CustomerLoginPage {
    WebDriver driver;

    WebElement errorLabel;
    WebElement submitButton;

    WebElement emailField;
    WebElement passField;

    public CustomerLoginPage(WebDriver driver) {
        this.driver = driver;
        driver.manage().timeouts().implicitlyWait(Duration.ofSeconds(10));

        submitButton = driver.findElement(By.cssSelector("button#send2"));

        emailField = driver.findElement(By.cssSelector("input#email"));
        passField = driver.findElement(By.cssSelector("input#pass"));
    }

    public MyAccountPage validLogin(String email, String password) {

        emailField.sendKeys(email);
        passField.sendKeys(password);

        submitButton.submit();
        driver.manage().timeouts().implicitlyWait(Duration.ofSeconds(10));

        return new MyAccountPage(driver);
    }

    public String invalidLogin(String email, String password) {
        emailField.sendKeys(email);
        passField.sendKeys(password);

        submitButton.submit();
        driver.manage().timeouts().implicitlyWait(Duration.ofSeconds(10));

        errorLabel = driver.findElement(By.xpath("//*[@id='top']/body/div/div[2]/div[2]/div/div/div[2]/ul/li/ul/li/span"));
        return errorLabel.getText();
    }

    public String getTile(){
        return driver.getTitle();
    }

}
