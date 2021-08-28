import time
import subprocess

def run_scanner_once():
    output = subprocess.check_output(['python', 'wifi-scanner.py'])

    output = output.decode('ascii')
    output = output.replace("\r","")

    print(output)

start_time = time.time()
keep_looping = True

while keep_looping:
    run_scanner_once()
    elapsed_time = time.time() - start_time
    if elapsed_time > 60:
        keep_looping = False
