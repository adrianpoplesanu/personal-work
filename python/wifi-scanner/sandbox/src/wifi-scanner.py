import subprocess
  
#devices = subprocess.check_output(['netsh','wlan','show','network'])
devices = subprocess.check_output(['/System/Library/PrivateFrameworks/Apple80211.framework/Versions/Current/Resources/airport', '-s'])
  
devices = devices.decode('ascii')
devices = devices.replace("\r","")
  
for line in devices.split('\n')[1:-1]:
    mark_for_add = True
    network = line.strip().split(' ')[0]
    with open('all-networks.txt', 'r') as all_networks:
        nets = all_networks.readlines()
        for net in nets:
            if network == net.strip():
                mark_for_add = False
                break
        #if not nets:
        #    print('pisat')
        #    mark_for_add = True
    if mark_for_add:
        with open('all-networks.txt', 'a+') as all_networks:
            print('adding ' + network + ' to pool')
            all_networks.write(network + '\n')

