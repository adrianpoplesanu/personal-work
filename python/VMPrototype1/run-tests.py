import subprocess
import re

expected_folder = "expected/"
tests_folder = "tests/"

script_name = 'main.py'
tests_data = open(expected_folder + 'test-list.txt', 'r')
test_files = tests_data.readlines()[:3]

success = []
failure = []
failure_expected = []
failure_actual = []

for test_file in test_files:
    target = tests_folder + test_file.strip().replace(".txt", ".ad")
    print('running ' + target)
    proc = subprocess.Popen(["python3", script_name, target], stdout=subprocess.PIPE)
    proc.wait()
    actual_output = proc.communicate()[0]
    expected_output = open(expected_folder + test_file.strip(), 'r').read()

    # print('---')
    # print(expected_output)
    # print('---')
    # print(actual_output.decode('utf-8'))
    # print('---')
    ok = re.fullmatch(expected_output, actual_output.decode('utf-8'))

    if not ok:
        failure.append("FAILURE - " + target)
        failure_expected.append(expected_output)
        failure_actual.append(actual_output)
    else:
        success.append(target)

if failure:
    for i, f in enumerate(failure):
        print(f)
        print("EXPECTED:\n" + failure_expected[i])
        print("ACTUAL:\n" + failure_actual[i].decode('utf-8'))
else:
    print('all tests passed!')
