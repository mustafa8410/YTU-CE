package Tests;

import Classes.Individual;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class SubscriberTest {
    Individual individual = new Individual("Mustafa","aaa","1",12,2024,268);

    @Test
    void getName() {
        assertEquals("Mustafa",individual.getName());
    }

    @Test
    void getAddress() {
        assertEquals("aaa",individual.getAddress());
    }
}