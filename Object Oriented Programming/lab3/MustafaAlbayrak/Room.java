import java.util.ArrayList;

public class Room {
    private static int nextRoomNumber = 1;
    private int roomNumber;
    private int durationOfStay;
    private ArrayList<Treatment> treatments;

    public Room(int durationOfStay) {
        this.durationOfStay = durationOfStay;
        ArrayList<Treatment> treatments = new ArrayList<Treatment>();
        this.roomNumber = nextRoomNumber;
        nextRoomNumber++;
    }

    public int getRoomNumber() {
        return roomNumber;
    }

    @Override
    public String toString() {
        return "Room{" +
                "roomNumber=" + roomNumber +
                ", durationOfStay=" + durationOfStay +
                '}';
    }

    public void addTreatments(Treatment treatment){
        treatments.add(treatment);
    }
}
