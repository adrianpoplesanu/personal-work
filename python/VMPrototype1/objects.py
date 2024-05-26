class AdObjectType:
    INT = 0
    BOOL = 1


class AdObject:
    object_type = None
    value = None


class AdObjectInteger(AdObject):
    def __init__(self, value: int):
        self.object_type = AdObjectType.INT
        self.value = value

    def inspect(self) -> str:
        return str(self.value)


class AdBoolean(AdObject):
    def __init__(self, value: int):
        self.object_type = AdObjectType.BOOL
        self.value = value

    def inspect(self) -> str:
        if self.value:
            return 'true'
        return 'false'
