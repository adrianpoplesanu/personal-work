import java.util.Timer;
import java.util.TimerTask;

public class TimeSchedulerTest {

    public void runTasks() {
        Timer timer = new Timer();
        timer.schedule(new TaskRunner(), 2000L, 2000L);
    }

    public static void main(String[] args) {
        System.out.println("running...");
        TimeSchedulerTest timeSchedulerTest = new TimeSchedulerTest();
        timeSchedulerTest.runTasks();
    }

    private class TaskRunner extends TimerTask {

        @Override
        public void run() {
            System.out.println("ola ola e");
        }
    }
}
