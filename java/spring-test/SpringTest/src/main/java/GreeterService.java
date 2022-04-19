import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class GreeterService {
    @Autowired
    Greeter greeter;

    public void printHello() {
        System.out.println(greeter.hello());
    }
}
