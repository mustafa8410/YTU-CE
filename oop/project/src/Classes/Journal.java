package Classes;

import java.io.Serial;
import java.io.Serializable;
import java.util.ArrayList;

public class Journal implements Serializable {

    private String name,issn;
    private int frequency;
    private double issuePrice;

    private ArrayList<Subscription> subscriptions = new ArrayList<>();

    @Serial
    private static final long serialVersionUID = 1L;
    public Journal(String name, String issn, int frequency, double issuePrice) {
        this.name = name;
        this.issn = issn;
        this.frequency = frequency;
        this.issuePrice = issuePrice;
    }

    public int getFrequency() {
        return frequency;
    }

    public double getIssuePrice() {
        return issuePrice;
    }

    public void addSubscribtion(Subscription subscription){
        if(subscription != null && subscription.getJournal().getIssn().equals(issn)){
            int newCopies = subscription.getCopies() + 1;
            subscription.setCopies(newCopies);
            addNewSubscription(subscription);
        }
        else System.out.println("Subscription is not found.\n");

    }

    public void addNewSubscription(Subscription subscription){
        for(Subscription s: subscriptions){
            if(s.getSubscriber().getName().equals(subscription.getSubscriber().getName())){
                System.out.println("This subscription already exists.");
                return;
            }
        }
        subscriptions.add(subscription);
        System.out.println("Added a new subscription.");
    }
    
    public Subscription findSubscription(String name){
        for(Subscription subscription: subscriptions){
            if(subscription.getSubscriber().getName().equals(name)){
                System.out.println("Found the subscription.");
                return subscription;
            }
        }
        System.out.println("Couldn't find any subscription with given name.");
        return null;
    }

    public ArrayList<Subscription> getSubscriptions() {
        return subscriptions;
    }

    public String getIssn() {
        return issn;
    }

    public String getName() {
        return name;
    }

    @Override
    public String toString() {
        return "Journal: " + "name='" + name + '\'' + ", issn='" + issn + "' / Frequency:" + frequency + "/ Issue Price:  " + issuePrice ;
    }
}
