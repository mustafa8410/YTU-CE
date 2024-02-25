package Classes;

import java.io.Serial;
import java.io.Serializable;

public class Subscription implements Serializable  {

    private final DateInfo dates;
    private PaymentInfo payment;
    private int copies;
    private final Journal journal;

    private final Subscriber subscriber;
    @Serial
    private static final long serialVersionUID = 1L;

    public Subscription(DateInfo dates, Journal journal, Subscriber subscriber) {
        this.dates = dates;
        this.journal = journal;
        this.subscriber = subscriber;
    }


    public Journal getJournal() {
        return journal;
    }

    public DateInfo getDates() {
        return dates;
    }

    public PaymentInfo getPayment() {
        return payment;
    }

    public void acceptPayment(double amount){
        payment.increasePayment(amount);
    }

    public double getRequiredTotalPayment(){
        double requiredPayment = (journal.getIssuePrice() * ((100 - payment.getDiscountRatio()) / 100.0) ) * copies * journal.getFrequency();
        System.out.println(requiredPayment);
        return requiredPayment;
    }

    public boolean canSend(int issueMonth){
        int startMonth = dates.getStartMonth();
        double requiredPaymentEach = (journal.getIssuePrice() * ( (100 - payment.getDiscountRatio() ) ) / 100.0) * copies;
        int published;
        if(issueMonth > startMonth){
            published = issueMonth / (12 / journal.getFrequency())  - startMonth / (12 / journal.getFrequency());
        }
        else if(issueMonth == startMonth){
            published = 1;
        }
        else{
            published = journal.getFrequency() - (startMonth / (12 / journal.getFrequency()) ) + (issueMonth / (12 / journal.getFrequency()) );

        }
        //System.out.println(payment.getReceivedPayment()); System.out.println(published); System.out.println(journal.getIssuePrice());

        return (payment.getReceivedPayment() >= requiredPaymentEach * published);
    }

    public int getCopies() {
        return copies;
    }

    public void setCopies(int copies) {
        this.copies = copies;
    }

    public void setPayment(PaymentInfo payment) {
        this.payment = payment;
    }

    public Subscriber getSubscriber() {
        return subscriber;
    }

    @Override
    public String toString() {
        String info;
        info = "Subscription to journal with issn number " + journal.getIssn() + '\n';
        info += "Subscriber: " + subscriber.getName() + '\n';
        info += "Copies delivered in each delivery: " + copies + '\n';
        return info;
    }
}
