import reactor.core.publisher.Mono;

public class FlatMapTest01 {

    public DogGenerator dogGenerator;

    public FlatMapTest01() {
        this.dogGenerator = new DogGenerator();
    }

    public void run() {
        Mono<Dog> monoDog = dogGenerator.generateDog("bebe dex", 14);
        Dog result = dogGenerator.testing(monoDog, 1).block();
        System.out.println(result);

        Dog result2 = dogGenerator.testing2(monoDog, 2).block();
        System.out.println(result2);
    }

    public static void main(String[] args) {
        FlatMapTest01 flatMapTest01 = new FlatMapTest01();
        flatMapTest01.run();
    }

    class Dog {
        public String name;
        public int age;

        public Dog(String name, int age) {
            this.name = name;
            this.age = age;
        }

        @Override
        public String toString() {
            return "Dog{" +
                    "name='" + name + '\'' +
                    ", age=" + age +
                    '}';
        }
    }

    class DogGenerator {
        Mono<Dog> generateDog(String name, int age) {
            return Mono.just(new Dog(name, age));
        }

        Mono<Dog> testing(Mono<Dog> monoDog, int age) {
            return monoDog.flatMap(dog -> { System.out.println(dog); dog.age = age; return Mono.just(dog); });
        }

        Mono<Dog> testing2(Mono<Dog> monoDog, int age) {
            return monoDog.map(dog -> { dog.age = age; return dog; });
        }
    }
}
