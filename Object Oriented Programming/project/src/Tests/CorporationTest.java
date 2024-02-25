package Tests;

import Classes.Corporation;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class CorporationTest {
    Corporation corporation = new Corporation("Yildiz","Davutpasa",12,"Is Bankasi",12,12,1980,1);

    @Test
    void getBankName() {
        assertEquals("Is Bankasi",corporation.getBankName());
    }

    @Test
    void getIssueDay() {
        assertEquals(12,corporation.getIssueDay());
    }
}