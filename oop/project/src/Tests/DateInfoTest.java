package Tests;

import Classes.DateInfo;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class DateInfoTest {
    DateInfo dateInfo = new DateInfo(4,3,2004);

    @Test
    void getStartMonth() {
        assertEquals(dateInfo.getStartMonth(),4);
    }

    @Test
    void getEndMonth() {
        assertEquals(dateInfo.getEndMonth(),3);
    }

    @Test
    void getStartYear() {
        assertEquals(dateInfo.getStartYear(),2004);
    }
}