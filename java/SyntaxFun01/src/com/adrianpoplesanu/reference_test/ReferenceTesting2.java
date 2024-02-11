package com.adrianpoplesanu.reference_test;

public class ReferenceTesting2 {

    void updateReference(Dog dog) {
        dog.setName("bebe dutz");
    }

    void reassignReference(Dog dog) {
        dog = new Dog("bicutz");
        System.out.println(dog);
    }

    void run() {
        Dog dog = new Dog("dex");
        System.out.println(dog);
        updateReference(dog);
        System.out.println(dog);
        reassignReference(dog);
        System.out.println(dog);
    }

    public static void main(String[] args) {
        ReferenceTesting2 referenceTesting2 = new ReferenceTesting2();
        referenceTesting2.run();
    }

    class Dog {
        private String name;

        public Dog(String name) {
            this.name = name;
        }

        public String getName() {
            return name;
        }

        public void setName(String name) {
            this.name = name;
        }

        @Override
        public String toString() {
            return "Dog{" +
                    "name='" + name + '\'' +
                    '}';
        }
    }
}
