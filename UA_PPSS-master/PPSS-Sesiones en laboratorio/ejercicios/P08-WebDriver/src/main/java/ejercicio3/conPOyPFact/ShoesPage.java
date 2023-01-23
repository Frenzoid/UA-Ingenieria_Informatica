package ejercicio3.conPOyPFact;

import org.openqa.selenium.Alert;
import org.openqa.selenium.JavascriptExecutor;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.FindBy;
import org.openqa.selenium.support.PageFactory;

import java.util.Set;

public class ShoesPage {
    public WebDriver driver;
    public String myHandleId;

    @FindBy(css = ".products-grid > li:nth-child(5) > .product-info > .actions > ul > li:nth-child(2) > a")
    WebElement wingtipShoe;

    @FindBy(css = ".products-grid > li:nth-child(6) > .product-info > .actions > ul > li:nth-child(2) > a")
    WebElement suedeShoe;

    @FindBy(css = "button[title='Compare']") WebElement compareButton;

    @FindBy(linkText = "Clear All") WebElement clearComparison;

    @FindBy(css = ".success-msg > ul > li > span") WebElement messageSpan;

    public ShoesPage(WebDriver driver) {
        this.driver = driver;
        myHandleId = driver.getWindowHandle();
    }

    public void selectShoeToCompare(int number) {
        JavascriptExecutor jse = (JavascriptExecutor) driver;
        switch (number) {
            case 5 -> {
                jse.executeScript("arguments[0].scrollIntoView();", wingtipShoe);
                wingtipShoe.click();
            }
            case 6 -> {
                jse.executeScript("arguments[0].scrollIntoView();", suedeShoe);
                suedeShoe.click();
            }
        }
    }

    public ProductComparisonPage submitCompare() {
        compareButton.click();
        ProductComparisonPage comparisonPage = PageFactory.initElements(driver, ProductComparisonPage.class);

        Set<String> setIds = driver.getWindowHandles();
        String[] handleIds = setIds.toArray(new String[setIds.size()]);

        comparisonPage.myHandleId = handleIds[1];
        comparisonPage.myHandleIdFrom = handleIds[0];

        driver.switchTo().window(comparisonPage.myHandleId);

        return comparisonPage;
    }

    public String ClearComparison() {
        clearComparison.click();
        Alert alert = driver.switchTo().alert();
        String mensaje = alert.getText();
        alert.accept();
        return mensaje;
    }

    public String getMessageSpanValue() {
        return messageSpan.getText();
    }

    public String getTile(){
        return driver.getTitle();
    }
}
