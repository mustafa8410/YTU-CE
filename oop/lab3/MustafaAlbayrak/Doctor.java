import javax.print.Doc;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Doctor implements ISurgeon,IMedicalPersonnel{
    private static ArrayList<Doctor> doctorList = new ArrayList<Doctor>();
    private String name;
    private double experience;
    private int surgeries;

    public Doctor(String name) {
        this.name = name;
        doctorList.add(this);
    }
    public Doctor(){}

    @Override
    public String toString() {
        return "Doctor{" +
                "name='" + name + '\'' +
                ", experience=" + experience +
                ", surgeries=" + surgeries +
                '}';
    }

    public int getSurgery() {
        return surgeries;
    }

    @Override
    public String getName() {
        return this.name;
    }

    @Override
    public void performSurgery() throws SurgeryUnsuccessfulException {
        double random = new Random().nextDouble();
    if(random > 0.80)
        throw new SurgeryUnsuccessfulException("Surgery is unsuccessful.");
    else {
        surgeries++;
        experience += 2.5;
    }
    }

    public static List<Doctor> getDoctorList(){
        return doctorList;
    }

    /*public void addDoctor(Doctor doctor){
        if(doctorList == null) {
            doctorList = new ArrayList<Doctor>();
        }
        doctorList.add(doctor);
    }*/
}
