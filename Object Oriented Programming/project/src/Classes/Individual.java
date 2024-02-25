package Classes;

import java.io.Serial;
import java.io.Serializable;

public class Individual extends Subscriber implements Serializable {

    private String creditCardNr;
    private int expireMonth;
    private int expireYear;
    private int CCV;
    @Serial
    private static final long serialVersionUID = 1L;

    public Individual(String name, String address, String creditCardNr, int expireMonth, int expireYear, int CCV) {
        super(name, address);
        this.creditCardNr = creditCardNr;
        this.expireMonth = expireMonth;
        this.expireYear = expireYear;
        this.CCV = CCV;
    }

    public String getCreditCardNr() {
        return creditCardNr;
    }

    public void setCreditCardNr(String creditCardNr) {
        this.creditCardNr = creditCardNr;
    }

    public int getExpireMonth() {
        return expireMonth;
    }

    public void setExpireMonth(int expireMonth) {
        this.expireMonth = expireMonth;
    }

    public int getExpireYear() {
        return expireYear;
    }

    public void setExpireYear(int expireYear) {
        this.expireYear = expireYear;
    }

    public int getCCV() {
        return CCV;
    }

    public void setCCV(int CCV) {
        this.CCV = CCV;
    }

    @Override
    public String getBillingInformation() {
        String info;
        info = "Name: " + getName() + "  Address: " +  getAddress() + "\nCredit Card No: " + creditCardNr + '\n' + "Expiration Date: " + expireMonth + '/' + expireYear + '\n';
        info += "CCV: " + CCV + '\n';
        return info;
    }
}
