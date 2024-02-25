package Tests;

import Classes.*;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class JournalTest {

    Journal journal = new Journal("Economics","1",12,20);
    DateInfo dateInfo = new DateInfo(1,12,2004);
    Subscriber subscriber = new Individual("Mustafa","Istanbul","1111",8,2028,111);
    PaymentInfo paymentInfo = new PaymentInfo(0);
    Subscription subscription = new Subscription(dateInfo,journal,subscriber);

    @Test
    void addNewSubscription() {
        journal.addNewSubscription(subscription);
        assertTrue(journal.getSubscriptions().contains(subscription));
    }

    @Test
    void findSubscription() {
        journal.addNewSubscription(subscription);
        assertTrue(journal.findSubscription("Mustafa").equals(subscription));
    }
}