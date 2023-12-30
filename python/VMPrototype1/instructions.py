class Instructions:
    size = 0

    def __init__(self):
        # List<Byte>
        self.bytes = []

    def add(self, _byte):
        self.bytes.append(_byte)
        self.size += 1
