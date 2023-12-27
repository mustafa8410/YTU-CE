package MustafaAlbayrak;

import java.util.List;

public class SalaryIncreaseThread implements Runnable {

    private List<Staff> staffList;
    private double increasePercentage;

    public SalaryIncreaseThread(List<Staff> staffList, double increasePercentage) {
        this.staffList = staffList;
        this.increasePercentage = increasePercentage;
    }

    public void run(){
        for(Staff s: staffList){
            s.increaseSalary(increasePercentage);
        }
    }
}
