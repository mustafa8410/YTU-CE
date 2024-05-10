import java.util.ArrayList;
import java.util.LinkedList;

public class Patient implements IMedicalPersonnel{
    private String name;
    private LinkedList<Treatment> treatments;


    public Patient(String name) {
        this.name = name;
        ArrayList<Treatment> treatments = new ArrayList<Treatment>();
    }

    public LinkedList<Treatment> getTreatments() {
        return treatments;
    }

    @Override
    public String toString() {
        return "Patient{" +
                "name='" + name + '\'' +
                '}';
    }

    @Override
    public String getName() {
        return name;
    }
}
