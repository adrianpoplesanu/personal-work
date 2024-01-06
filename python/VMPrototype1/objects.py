class AdObjectType:
    INT = 0


class AdObject:
    pass


class AdObjectInteger(AdObject):
    def __init__(self, value: int):
        self._type = AdObjectType.INT
        self.value = value

    def inspect(self) -> str:
        return str(self.value)