import json
import subprocess
import sys

def sort_dict(source):
    if type(source) != dict:
        if type(source) == list:
            original_list = [sort_dict(it) for it in source]
            return sorted(original_list, key=str)
        return source
    sorted_dict = {key: sort_dict(value) for key, value in sorted(source.items())}
    return sorted_dict

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Usage: python3 compare_json.py file1.json file2.json")
        sys.exit()
    filename1 = open(sys.argv[1], "r")
    data1 = filename1.read()
    source1 = json.loads(data1)
    sorted_dict1 = json.dumps(sort_dict(source1), indent=4)
    outfile1 = open("SORTED_" + sys.argv[1], "w")
    outfile1.write(sorted_dict1)
    outfile1.close()

    filename2 = open(sys.argv[2], "r")
    data2 = filename2.read()
    source2 = json.loads(data2)
    sorted_dict2 = json.dumps(sort_dict(source2), indent=4)
    outfile2 = open("SORTED_" + sys.argv[2], "w")
    outfile2.write(sorted_dict2)
    outfile2.close()

    command = "diff SORTED_" + sys.argv[1] + " SORTED_" + sys.argv[2]
    process = subprocess.Popen(command.split(), stdout=subprocess.PIPE)
    output, error = process.communicate()
    print("{0}".format(str(output.decode("utf-8"))))