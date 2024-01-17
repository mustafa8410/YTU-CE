package Classes;

import java.io.Serial;
import java.io.Serializable;

public class Corporation extends Subscriber implements Serializable {

    private int bankCode;
    private String bankName;
    private int issueDay, issueMonth, issueYear;
    private int accountNumber;
    @Serial
    private static final long serialVersionUID = 1L;


    public Corporation(String name, String address, int bankCode, String bankName, int issueDay, int issueMonth, int issueYear, int accountNumber) {
        super(name, address);
        this.bankCode = bankCode;
        this.bankName = bankName;
        this.issueDay = issueDay;
        this.issueMonth = issueMonth;
        this.issueYear = issueYear;
        this.accountNumber = accountNumber;
    }

    public int getBankCode() {
        return bankCode;
    }

    public void setBankCode(int bankCode) {
        this.bankCode = bankCode;
    }

    public String getBankName() {
        return bankName;
    }

    public void setBankName(String bankName) {
        this.bankName = bankName;
    }

    public int getIssueDay() {
        return issueDay;
    }

    public void setIssueDay(int issueDay) {
        this.issueDay = issueDay;
    }

    public int getIssueMonth() {
        return issueMonth;
    }

    public void setIssueMonth(int issueMonth) {
        this.issueMonth = issueMonth;
    }

    public int getIssueYear() {
        return issueYear;
    }

    public void setIssueYear(int issueYear) {
        this.issueYear = issueYear;
    }

    public int getAccountNumber() {
        return accountNumber;
    }

    public void setAccountNumber(int accountNumber) {
        this.accountNumber = accountNumber;
    }

    @Override
    public String getBillingInformation() { ///??
        String info;
        info ="Name: " + getName() + '\n' + "Bank code: " + bankCode + '\n' + "Bank name: " + bankName + '\n' + "Issue Date: " + issueDay + '/' + issueMonth + '/' + issueYear + '\n' + "Account number: " + accountNumber + '\n' + "Address: " + getAddress();
        return info;


    }
}
