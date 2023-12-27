import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Hospital {

    private ArrayList<Doctor> medicalPersonnelList;

    public Hospital() {
        ArrayList<Doctor> medicalPersonnelList = new ArrayList<Doctor>();
    }
    public void addMedicalPersonnel(Doctor personnel){
        medicalPersonnelList.add(personnel);
    }
    public void assignPatientToDoctor(Doctor doctor, Patient patient, Treatment treatment){
        double dailyFee = 100;
        double totalFee;
        try {
            doctor.performSurgery();
            System.out.println(doctor.getName() + " performed successful surgery on patient: " + patient.getName());
            System.out.println("Prescribed treatment: " + treatment.toString());
            int duration = (int) (Math.random() * 10) + 1;
            totalFee = (double) dailyFee * duration;
            Room r = new Room(duration);
            System.out.println("Allocated room: " + r.toString());
            System.out.println("Daily fee for " + patient.getName() + ':' + dailyFee);

        } catch (SurgeryUnsuccessfulException e) {
            System.out.println("Surgery by " + doctor.getName() + " was unsuccessful.");
            System.out.println("Patient: " + patient.getName() + "did not survive the surgery.");
            totalFee = 0;
        }
        System.out.println("Total fee for patient: " + patient.getName() + ':' + totalFee);
    }

    public static <Z> void showList(List<Z> doctor){
        for(Z doctor1: doctor) System.out.println(doctor1);
    }
}
