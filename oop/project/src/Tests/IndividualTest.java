package Tests;

import Classes.Individual;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class IndividualTest {

    Individual individual = new Individual("Mustafa","Istanbul","1234567812345678",8,2028,766);

    @Test
    void getCreditCardNr() {
        assertEquals("1234567812345678",individual.getCreditCardNr());
    }

    @Test
    void setExpireYear() {
        individual.setExpireYear(2004);
        assertEquals(2004,individual.getExpireYear());
    }
}