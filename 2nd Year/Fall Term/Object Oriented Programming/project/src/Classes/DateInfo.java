package Classes;

import java.io.Serial;
import java.io.Serializable;

public class DateInfo implements Serializable {

    private int startMonth, endMonth, startYear;
    @Serial
    private static final long serialVersionUID = 1L;

    public DateInfo(int startMonth, int endMonth, int startYear) {
        this.startMonth = startMonth;
        this.endMonth = endMonth;
        this.startYear = startYear;
    }

    public int getStartMonth() {
        return startMonth;
    }

    public int getEndMonth() {
        return endMonth;
    }

    public int getStartYear() {
        return startYear;
    }
}
