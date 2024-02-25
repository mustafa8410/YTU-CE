package Tests;

import Classes.Distributor;
import Classes.Individual;
import Classes.Journal;
import Classes.Subscriber;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class DistributorTest {

    Distributor distributor = new Distributor();
    Journal journal1 = new Journal("Economics","1",4,20);
    Journal journal2 = new Journal("History","2",6,40);
    Journal journal3 = new Journal("Gaming","3",3,60);
    Individual individual = new Individual("Mustafa","Istanbul","1",1,1,1);

    @Test
    void addJournal() {
        distributor.addJournal(journal1);
        assertTrue(distributor.searchJournal("1").equals(journal1));
    }

    @Test
    void addSubscriber() {
        distributor.addSubscriber(individual);
        assertTrue(distributor.searchSubscriber("Mustafa").equals(individual));
    }
}