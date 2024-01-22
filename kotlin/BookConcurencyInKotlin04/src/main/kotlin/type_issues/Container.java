package type_issues;

import java.util.Map;

public class Container {
    private final Map<ContainerType, Long> params;

    public Container(Map<ContainerType, Long> params) {
        this.params = params;
    }

    public Map<ContainerType, Long> getParams() {
        return params;
    }
}
