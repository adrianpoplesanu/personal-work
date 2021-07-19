if __name__ == '__main__':
    filenames = ["/home/apoplesanu/docs/readme.MD", "/home/apoplesanu/docs/readme.txt", "/home/apoplesanu/docs/readme.rst", "/home/apoplesanu"]
    for filename in filenames:
        raw_filename = filename.split('/')[-1]
        if '.' in raw_filename:
            print raw_filename.split('.')[-1]
        else:
            # check daca e fisier/folder si daca e fisier marcat cumva ca nu are extensie