import reactor.core.publisher.Mono;

public class DeferTest01 {

    private Mono<Dog> generateDog(String name) {
        Dog dog = new Dog("bebe dex");
        return Mono.just(dog);
    }

    public void doTesting() {
        Mono.defer(() -> generateDog("unused param").map(dog -> dog.name).doOnEach((name) -> {
            if (name.get() != null) {
                System.out.println(name.get());
            }
        })).block();
    }

    public static void main(String[] args) {
        DeferTest01 deferTest01 = new DeferTest01();
        deferTest01.doTesting();
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
