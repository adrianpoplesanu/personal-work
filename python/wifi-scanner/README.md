run here:

virtualenv sandbox


airport -s
/System/Library/PrivateFrameworks/Apple80211.framework/Versions/Current/Resources/airport -s
networksetup -setairpotnetwork en0 SSID_OF_WIRELESS_NETWORK WIRELESS_NETWORK_PASSPHRASE

ipconfig getifaddr en0
