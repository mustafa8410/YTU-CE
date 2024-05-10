package Classes;

import java.io.Serial;
import java.io.Serializable;
import java.time.LocalDate;
import java.util.Hashtable;

public class PaymentInfo implements Serializable {

    private final double discountRatio;
    private double receivedPayment;

    private Hashtable<Integer, Double> paymentDates = new Hashtable<>();
    @Serial
    private static final long serialVersionUID = 1L;

    public PaymentInfo(double discountRatio) {
        this.discountRatio = discountRatio;
        receivedPayment=0;
    }

    public double getReceivedPayment() {
        return receivedPayment;
    }

    public void increasePayment(double amount){
        LocalDate date = LocalDate.now();
        Integer year = date.getYear();
        if(paymentDates.containsKey(year)){
            Double paymentValue = paymentDates.get(year);
            paymentValue+=amount;
            paymentDates.replace(year,paymentValue);
        }else{
            paymentDates.put(year,amount);
        }
        receivedPayment += amount;
    }

    public Hashtable<Integer, Double> getPaymentDates() {
        return paymentDates;
    }

    public double getDiscountRatio() {
        return discountRatio;
    }
}
