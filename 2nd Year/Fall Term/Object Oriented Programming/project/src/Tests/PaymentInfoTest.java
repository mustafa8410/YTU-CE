package Tests;

import Classes.PaymentInfo;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class PaymentInfoTest {
    PaymentInfo paymentInfo = new PaymentInfo(0);

    @Test
    void getReceivedPayment() {
        assertEquals(paymentInfo.getReceivedPayment(),0);
    }

    @Test
    void increasePayment() {
        paymentInfo.increasePayment(56.5);
        assertEquals(paymentInfo.getReceivedPayment(),56.5);
    }
}