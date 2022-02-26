import java.util.Scanner;

class Main {
    public static void main(String[] args) {
        try (Scanner s = new Scanner(System.in)) {
            int currentTime = s.nextInt();
            int currentMinute = s.nextInt();
            int requireMinutes = s.nextInt();

            int minuteSum = currentMinute + requireMinutes;
            currentTime += minuteSum / 60;
            if (currentTime >= 24) {
                currentTime -= 24;
            }
            
            currentMinute = minuteSum % 60;

            System.out.println(currentTime + " " + currentMinute);
        }
    }
}