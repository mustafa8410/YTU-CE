package MustafaAlbayrak;

public class AcademicStaff extends Staff{

    private int numberOfCourses;

    public AcademicStaff(String name, double salary, int numberOfCourses) {
        super(name, salary);
        this.numberOfCourses = numberOfCourses;
    }

    @Override
    public void increaseSalary(double percentage) {
        double newSalary;
        newSalary = (getSalary() + (getSalary() * percentage /100.0)) + numberOfCourses*1000;
        setSalary(newSalary);

    }

    @Override
    public String toString() {
        return "Academic," + getName() + ',' + getSalary() + ',' + numberOfCourses;
    }
}
