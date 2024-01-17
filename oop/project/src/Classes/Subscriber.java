package Classes;


import java.io.Serial;
import java.io.Serializable;

public abstract class Subscriber implements Serializable {
    private String name;
    private String address;

    @Serial
    private static final long serialVersionUID = 1L;

    public Subscriber(String name, String address) {
        this.name = name;
        this.address = address;
    }

    public String getName() {
        return name;
    }

    public String getAddress() {
        return address;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    public abstract String getBillingInformation();
}
