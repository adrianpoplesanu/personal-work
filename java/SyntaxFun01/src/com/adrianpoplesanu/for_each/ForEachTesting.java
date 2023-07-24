package com.adrianpoplesanu.for_each;

import java.util.ArrayList;
import java.util.List;

public class ForEachTesting {

    private List<Info> defaultStatus(List<Info> infos) {
        infos.forEach(info -> {
            Status newStatus = new Status();
            newStatus.setValue(false);
            info.setStatus(newStatus);
        });
        return infos;
    }

    public void testFunctionality() {
        List<Info> infos = new ArrayList<>();
        infos.add(new Info());
        defaultStatus(infos);
        for (int i = 0; i < infos.size(); i++) {
            System.out.println(infos.get(i).getStatus().isValue());
        }
    }

    public static void main(String[] args) {
        ForEachTesting forEachTesting = new ForEachTesting();
        forEachTesting.testFunctionality();
    }

    class Info {
        private Status status;

        public Info() {

        }

        public Status getStatus() {
            return status;
        }

        public void setStatus(Status status) {
            this.status = status;
        }
    }

    class Status {
        private boolean value;

        public Status() {

        }

        public boolean isValue() {
            return value;
        }

        public void setValue(boolean value) {
            this.value = value;
        }
    }
}
