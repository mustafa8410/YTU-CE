package Classes;

import java.io.*;
import java.time.LocalDate;
import java.util.*;
import javax.swing.JOptionPane;

public class Distributor implements Serializable, Runnable {

    private Hashtable<String,Journal> journals = new Hashtable<>();
    private Vector<Subscriber> subscribers = new Vector<>();
    @Serial
    private static final long serialVersionUID = 1L;


    public Distributor() {
    }

    public boolean addJournal(Journal journal){
        if(journal != null){
            if(!journals.containsKey(journal.getIssn())) {
                journals.put(journal.getIssn(), journal);
                System.out.println("Successfully added the journal.");
                return true;
            }
            else{
                System.out.println("This journal already exists!");
                return false;
            }
        }else{
            System.out.println("This journal doesn't exist!");
            return false;
        }
    }

    public Journal searchJournal(String issn){
        if(journals.containsKey(issn)) {
            System.out.println("Found journal with issn " + issn);
            return journals.get(issn);
        }
        else {
            System.out.println("Couldn't find any journal with issn: " + issn);
            return null;
        }

    }

    public boolean addSubscriber(Subscriber subscriber){
        if(subscriber != null){
            for(Subscriber subscriber1: subscribers){
                if(subscriber.getName().equals(subscriber1.getName())){
                    System.out.println("Subscriber already exists!"); return false;
                }
            }
            subscribers.add(subscriber);
            System.out.println("Successfully added subscriber.");
            return true;
        }
        else{
            System.out.println("Subscriber doesn't exist.");
            return false;
        }
    }

    public Subscriber searchSubscriber(String name){
        for(Subscriber subscriber: subscribers){
            if(subscriber.getName().equals(name)){
                System.out.println("Subscriber found with given name.");
                return subscriber;
            }
        }
        System.out.println("Couldn't find a subscriber with given name.");
        return null;
    }
    
        public Subscription findSubscription(String name,String issn){
        Journal journal = searchJournal(issn);
        if(journal == null){
            return null;
        }
        else{
           return journal.findSubscription(name);
        }
    }

    public boolean addSubscription(String issn, Subscriber subscriber, Subscription subscription,double discount, int copy){

        if(!journals.containsKey(issn)){
            System.out.println("There are no journals with given isnn.");
            return false;
        }
        Journal journal = journals.get(issn);
        if (subscriber == null) {
            System.out.println("Subscriber doesn't exist!"); return false;
        }

        if(subscription != null && subscription.getSubscriber() == subscriber && subscription.getJournal() == journal){
            journal.addSubscribtion(subscription);
            if(!subscribers.contains(subscriber))
                addSubscriber(subscriber);
            if(subscriber instanceof Corporation){
                    subscription.acceptPayment(subscription.getRequiredTotalPayment() - subscription.getPayment().getReceivedPayment());
                    System.out.println("Total payment from the corporation has been received.");
                }
            System.out.println("Subscription already exists, increased the number of copies by 1.");
            return true;
        }
        LocalDate date = LocalDate.now();
        int startMonth, startYear, endMonth;
        startMonth = date.getMonthValue();
        startYear = date.getYear();
        if(startMonth > 1) endMonth = startMonth - 1; else endMonth=12;
        DateInfo dates = new DateInfo(startMonth,endMonth,startYear);
        subscription = new Subscription(dates, journal, subscriber);
        //Scanner s = new Scanner(System.in);
        //System.out.println("Please provide with the desired discount ratio: ");
        //double discountRatio = s.nextDouble();
        PaymentInfo payment = new PaymentInfo(discount);
        subscription.setPayment(payment);
        //System.out.println("Please provide with the desired number of copies in each delivery: ");
        //int copies = s.nextInt();
        subscription.setCopies(copy);
        if(subscriber instanceof Corporation) {
            subscription.acceptPayment(subscription.getRequiredTotalPayment());
            System.out.println("Total payment from the corporation has been received.");
        }
        if(!subscribers.contains(subscriber)){
            subscribers.add(subscriber);
        }
        if(!journal.getSubscriptions().contains(subscription)) journal.addNewSubscription(subscription);
        System.out.println("Subscription successfully added.");
        return true;
    }

    public String listAllSendingOrders(int month,int year){
        Collection<Journal> jValues = journals.values(); StringBuilder messageBuilder = new StringBuilder("All sending orders:\n");
        for(Journal journal: jValues){
            if(month % (12 / journal.getFrequency()) == 0) {
                System.out.println(journal + "can be send to: "); messageBuilder.append(journal).append(" can be sent to: \n");
                for (Subscription subscription : journal.getSubscriptions()) {
                    if(year == subscription.getDates().getStartYear() || ((year-1) == subscription.getDates().getStartYear() && month <= subscription.getDates().getEndMonth()  && subscription.getDates().getStartMonth()!=1)) {
                        if (subscription.canSend(month)){ System.out.println(subscription.getSubscriber().getName()); messageBuilder.append(subscription.getSubscriber().getName()).append('\n');
                                }
                    }
                }
            }
        }
        return messageBuilder.toString();
    }

    public String listSendingOrders(String issn, int month, int year){
        Journal journal = journals.get(issn); if(journal == null) return "This journal doesn't exist!\n";   StringBuilder messageBuilder = new StringBuilder();
        if(month % (12 / journal.getFrequency()) == 0 ){
            System.out.println(journal + "can be sent to: "); messageBuilder.append("Sending orders for journal: ").append(journal.toString()).append(":\n");
            for (Subscription subscription : journal.getSubscriptions()) {
                if(year == subscription.getDates().getStartYear() || ((year-1) == subscription.getDates().getStartYear() && month <= subscription.getDates().getEndMonth() && subscription.getDates().getStartMonth()!=1) ) {
                    if (subscription.canSend(month)) {System.out.println(subscription.getSubscriber().getName()); messageBuilder.append(subscription.getSubscriber().getBillingInformation()).append("\n\n"); }
                }
            }

        } else return "This journal doesn't get published in the given date.\n";
        return messageBuilder.toString();
    }

    public String listIncompletePayments(){
        LocalDate date = LocalDate.now();
        int month=date.getMonthValue(); int year=date.getYear();
        Collection<Journal> jValues = journals.values();
        System.out.println("Incomplete payments for: ");StringBuilder messageBuilder = new StringBuilder("Incomplete payments for: \n");
        for(Journal journal: jValues){
            if(month % (12 / journal.getFrequency()) == 0 ){
                System.out.println(journal + " by: "); messageBuilder.append(journal).append(" by:\n");
                for(Subscription subscription: journal.getSubscriptions()){
                    if(year == subscription.getDates().getStartYear() || ((year-1) == subscription.getDates().getStartYear() && month <= subscription.getDates().getEndMonth()  && subscription.getDates().getStartMonth()!=1)){
                        if (!subscription.canSend(month)){ System.out.println(subscription.getSubscriber().getName()); messageBuilder.append(subscription.getSubscriber().getName()).append('\n'); }
                    }
                }

            }
        }
        
        return messageBuilder.toString();

    }

    public String listSubscriberSubscriptions(String subscriberName){
        Collection<Journal> jValues = journals.values();
        if(searchSubscriber(subscriberName) == null) return "This subscriber doesn't exist.\n";
        StringBuilder messageBuilder = new StringBuilder("Subscriptions of subscriber named "); messageBuilder.append(subscriberName).append(":\n");
        for(Journal journal: jValues){
            for(Subscription subscription: journal.getSubscriptions()){
                if(subscription.getSubscriber().getName().equals(subscriberName)){
                    System.out.println(subscription); messageBuilder.append(subscription.toString()).append("\n\n");
                }
            }
        }
        return messageBuilder.toString();

    }

    public void newPaymentReceived(String subscriberName, String issn, double amount){
        Subscriber subscriber = searchSubscriber(subscriberName); if(subscriber == null) return;
        Journal journal = searchJournal(issn); if(journal == null) return;
        for(Subscription subscription: journal.getSubscriptions()){
            if(subscription.getSubscriber().getName().equals(subscriberName)){
                subscription.acceptPayment(amount);
                System.out.println("Payment completed successfully.");
                return;
            }
        }
        System.out.println("Couldn't find a subscription with given details.");
    }

    public String listSubscriptions(String issn){
        Journal journal = searchJournal(issn);
        if(journal == null) return "This journal doesn't exist.\n";
        StringBuilder messageBuilder = new StringBuilder();
        messageBuilder.append("Subscriptions to ").append(journal.toString()).append(":\n");
        for(Subscription subscription: journal.getSubscriptions()){
            System.out.println(subscription.toString()); messageBuilder.append(subscription.toString()).append('\n');
        }
        return messageBuilder.toString();
    }

    public void saveState(String fileName){

        File file = new File(fileName);
        if(file.exists()) file.delete();
        try {
            file.createNewFile();
        } catch (IOException e) {
            System.out.println("An error occurred.");
        }
        try {
            FileOutputStream fileOut = new FileOutputStream(fileName);
            ObjectOutputStream objOut = new ObjectOutputStream(fileOut);
            objOut.writeObject(journals);
            objOut.writeObject(subscribers);
            objOut.close();
            fileOut.close();
            System.out.println("Saved successfully.");
        } catch (IOException e) {
            System.out.println("An exception has occurred while saving the datas.");
        }
    }

    public void loadState(String fileName){
        try {
            FileInputStream file = new FileInputStream(fileName);
            ObjectInputStream obj = new ObjectInputStream(file);
            journals = (Hashtable<String, Journal>) obj.readObject();
            subscribers = (Vector<Subscriber>) obj.readObject();
            obj.close();
            file.close();
            System.out.println("Loaded datas successfully.");

        } catch (IOException e) {
            System.out.println("An error occurred.");
        }catch (ClassNotFoundException e){
            System.out.println("Journals or Subscribers couldn't be found.");
        }
    }

    public synchronized void report(){
        Scanner scanner = new Scanner(System.in);
        System.out.println("Give date to see subscriptions that are going to expire after: ");
        int month, yearSub, subscriptionEndMonth, subscriptionEndYear;
        System.out.println("Month: "); month = scanner.nextInt();
        System.out.println("Year: "); yearSub= scanner.nextInt();
        System.out.println("Give year range to see the payments received in between:");
        int startYear, endYear;
        System.out.println("Start year: "); startYear = scanner.nextInt();
        System.out.println("End year: "); endYear = scanner.nextInt();
        Collection<Journal> journalCollection = journals.values();

        //subscriptions expiring
        System.out.println("Subscriptions expiring after " + month + '/' + yearSub + ':');

        for(Journal journal: journalCollection){
            for(Subscription subscription: journal.getSubscriptions()){
                subscriptionEndMonth = subscription.getDates().getEndMonth();
                if(subscriptionEndMonth == 12) subscriptionEndYear = subscription.getDates().getStartYear();
                else subscriptionEndYear = subscription.getDates().getStartYear() + 1;
                if(subscriptionEndYear > yearSub) System.out.println(subscription);
                else if(subscriptionEndYear == yearSub && subscriptionEndMonth > month) System.out.println(subscription);

            }
        }
        
        

        //received payments

        System.out.println("Received annual payments between " + startYear + '-' + endYear + ": ");
        int yearIterator; double received;
        Hashtable<Integer,Double> collectedPayments;
        for(Journal journal: journalCollection){
            for(Subscription subscription: journal.getSubscriptions()){
                collectedPayments = subscription.getPayment().getPaymentDates();
                yearIterator=startYear;
                while (yearIterator <= endYear){
                    if(collectedPayments.containsKey(yearIterator)){
                        received = collectedPayments.get(yearIterator);
                        System.out.println("Subscriber: " + subscription.getSubscriber().getName() + "/Journal issn: " + journal.getIssn() + "/Received: " + received);
                    }
                    yearIterator++;
                }

            }
        }
    }
    
    public synchronized void report(int subMonth, int subYear, int startYear, int endYear){
        //Scanner scanner = new Scanner(System.in);
        //System.out.println("Give date to see subscriptions that are going to expire after: ");
        int subscriptionEndMonth, subscriptionEndYear;
        //System.out.println("Month: "); month = scanner.nextInt();
        //System.out.println("Year: "); yearSub= scanner.nextInt();
        //System.out.println("Give year range to see the payments received in between:");

        //System.out.println("Start year: "); startYear = scanner.nextInt();
        //System.out.println("End year: "); endYear = scanner.nextInt();
        Collection<Journal> journalCollection = journals.values();

        //subscriptions expiring
        StringBuilder messageBuilder = new StringBuilder();
        System.out.println("Subscriptions expiring after " + subMonth + '/' + subYear + ':');
        messageBuilder.append("Subscriptions expiring after ").append(subMonth).append('/').append(subYear).append(":\n");
        for(Journal journal: journalCollection){
            for(Subscription subscription: journal.getSubscriptions()){
                subscriptionEndMonth = subscription.getDates().getEndMonth();
                if(subscriptionEndMonth == 12) subscriptionEndYear = subscription.getDates().getStartYear();
                else subscriptionEndYear = subscription.getDates().getStartYear() + 1;
                if(subscriptionEndYear > subYear){ System.out.println(subscription); messageBuilder.append(subscription.toString()).append('\n'); }
                else if(subscriptionEndYear == subYear && subscriptionEndMonth >= subMonth){ System.out.println(subscription); messageBuilder.append(subscription.toString()).append('\n');
                }

            }
        }
        
        JOptionPane.showMessageDialog(null,messageBuilder.toString());

        //received payments
        
        StringBuilder nMessage = new StringBuilder();

        System.out.println("Received annual payments between " + startYear + '-' + endYear + ": ");
        nMessage.append("Received annual payments between ").append(startYear).append('-').append(endYear).append(":\n ");
        int yearIterator; double received;
        Hashtable<Integer,Double> collectedPayments;
        for(Journal journal: journalCollection){
            for(Subscription subscription: journal.getSubscriptions()){
                collectedPayments = subscription.getPayment().getPaymentDates();
                yearIterator=startYear;
                while (yearIterator <= endYear){
                    if(collectedPayments.containsKey(yearIterator)){
                        received = collectedPayments.get(yearIterator);
                        System.out.println("Subscriber: " + subscription.getSubscriber().getName() + "/Journal issn: " + journal.getIssn() + "/Received: " + received);

                        nMessage.append("Subscriber: ").append(subscription.getSubscriber().getName()).append("/Journal issn: ").append(journal.getIssn()).append(" / Received: ").append(received).append('\n');
                    }
                    yearIterator++;
                }

            }
        }
        JOptionPane.showMessageDialog(null,nMessage.toString());
    }



    public void run(){
        report();
    }



}
