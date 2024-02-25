package Tests;

import Classes.*;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class SubscriptionTest {

    DateInfo dateInfo = new DateInfo(1,12,2004);
    Subscriber subscriber = new Individual("Mustafa","Istanbul","1111",8,2028,111);
    Journal journal = new Journal("Economics","1",4,20);
    PaymentInfo paymentInfo = new PaymentInfo(0);
    Subscription subscription = new Subscription(dateInfo,journal,subscriber);

    @Test
    void canSend() {
        subscription.setCopies(1);
        subscription.setPayment(paymentInfo);
        assertFalse(subscription.canSend(6));
        subscription.acceptPayment(20);
        subscription.acceptPayment(40);
        assertTrue(subscription.canSend(6));
    }

    @Test
    void getCopies() {
        subscription.setCopies(5);
        assertNotEquals(10, subscription.getCopies());
        assertEquals(5, subscription.getCopies());

    }
}