import java.util.Arrays;
public class sort_studs {
    public static class Person {
        protected String firstname;
        protected String lastname;
        protected String country;

        protected Person(String country, String firstname, String lastname){
            this.firstname = firstname;
            this.lastname = lastname;
            this.country = country;
        }
        
        public String toString() {
            return firstname + " " + lastname + " " + "(" + country + ")";
        }
    }

    public static class Student extends Person implements Comparable<Student>{
        protected Student(String country, String firstname, String lastname) {
            super(country, firstname, lastname);
        }

        @Override
        public int compareTo(Student s) {
            int i =  lastname.compareTo(s.lastname);
            if (i != 0) return i;

            i = firstname.compareTo(s.firstname);
            if (i != 0) return i;

            return country.compareTo(s.country);
        }
    }

    public static class Citizen extends Person implements Comparable<Citizen> {
        protected Citizen(String country, String firstname, String lastname) {
            super(country, firstname, lastname);
        }

        @Override
        public int compareTo(Citizen c) {
            int i = country.compareTo(c.country);
            if (i != 0) return i;

            i = lastname.compareTo(c.lastname);
            if (i != 0) return i;

            return firstname.compareTo(c.firstname);
        }
    }

    public static void main(String[] args) {
        Student[] studs = {
                new Student("Poland", "Jan", "Kowalski"),
                new Student("France", "Jean", "Killy"),
                new Student("Poland", "Maria", "Nowak"),
                new Student("Poland", "Julia", "Nowak"),
                new Student("Germany", "Hans", "Schultz"),
                new Student("France", "Jeanne", "Marat"),
        };
        Arrays.sort(studs);
        System.out.println("Students: by lastname, firstname, country");
        
        for (Student s : studs)
            System.out.println(s);
        Citizen[] cits = {
                new Citizen("Poland", "Jan", "Kowalski"),
                new Citizen("France", "Jean", "Killy"),
                new Citizen("Poland", "Maria", "Nowak"),
                new Citizen("Poland", "Julia", "Nowak"),
                new Citizen("Germany", "Hans", "Schultz"),
                new Citizen("France", "Jeanne", "Marat"),

        };
        Arrays.sort(cits);
        System.out.println("Citizens: by country, lastname, firstname");
        
        for (Citizen c : cits)
            System.out.println(c);
    }
}
