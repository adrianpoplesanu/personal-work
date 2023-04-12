import reactor.core.publisher.Mono;

public class OrderingTest {

    private Mono<Dog> createEntity(Dog dog) {
        return Mono.just(dog);
    }

    private Mono<Dog> addAddress(Dog dog) {
        System.out.println(dog);
        dog.setAddress("buc noi 156");
        return Mono.just(dog);
    }

    private Mono<Dog> addAge(Dog dog) {
        System.out.println(dog);
        dog.setAge("12");
        return Mono.just(dog);
    }
    public void testingOrder() {
        Dog dog = new Dog("bebe dex");
        Mono<Dog> dogMono = createEntity(dog).then(addAddress(dog)).then(addAge(dog));
        Dog result = dogMono.block();
        System.out.println(result);
    }

    public static void main(String[] args) {
        OrderingTest orderingTest = new OrderingTest();
        orderingTest.testingOrder();
    }

    private class Dog {
        private String name;
        private String address;
        private String age;

        public Dog(String name) {
            this.name = name;
        }

        public String getName() {
            return name;
        }

        public void setName(String name) {
            this.name = name;
        }

        public String getAddress() {
            return address;
        }

        public void setAddress(String address) {
            this.address = address;
        }

        public String getAge() {
            return age;
        }

        public void setAge(String age) {
            this.age = age;
        }

        @Override
        public String toString() {
            return "Dog{" +
                    "name='" + name + '\'' +
                    ", address='" + address + '\'' +
                    ", age='" + age + '\'' +
                    '}';
        }
    }
}
