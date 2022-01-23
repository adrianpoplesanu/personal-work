package com.adrianpoplesanu.BlueAlert;

import java.security.Principal;

class StompPrincipal implements Principal {
    public String name;

    public StompPrincipal(String name) {
        this.name = name;
    }

    @Override
    public String getName() {
        return name;
    }
}
