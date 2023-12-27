package MustafaAlbayrak;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class FileUtility {
    public static List<Staff> readStaffFromFile(String fileName){
        List<Staff> staffList = new ArrayList<Staff>();
        double salary;
        int course;

        try {
            File file = new File(fileName);
            Scanner scanner = new Scanner(file);
            while(scanner.hasNextLine()){

                String data = scanner.nextLine();
                String[] sData = data.split(",");
                salary = Double.parseDouble(sData[2]);
                if("Academic".equals(sData[0])){
                    course = Integer.parseInt(sData[3]);
                    AcademicStaff as = new AcademicStaff(sData[1],salary,course);
                    staffList.add(as);
                }
                else{
                    Staff s = new Staff(sData[1],salary);
                    staffList.add(s);
                }
            }

        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
        return staffList;
    }

    public static void writeStaffToFile(List<Staff> staffList,String fileName){
        try {
            FileWriter writer = new FileWriter(fileName);
            for(Staff s: staffList){
                writer.write(s.toString() + '\n');
            }
            writer.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
