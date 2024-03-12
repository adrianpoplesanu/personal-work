from wad_data import WADData


class DoomEngine():
    def __init__(self, wad_path="wad/doom1.wad"):
        self.wad_path = wad_path
        self.wad_data = WADData(self)


if __name__ == '__main__':
    doom = DoomEngine()
