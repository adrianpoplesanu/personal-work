#!/bin/bash
echo "Moving Orbital Gateway runtime properties files..."
rm -rf /home/vagrant/payment-temp-checkout
mkdir /home/vagrant/payment-temp-checkout
git clone un-link-aici
cp /home/vagrant/payment-temp-checkout $PAYMENTECH_HOME/bla\ bla\ bla
rm -rf /home/vagrant/payment-temp-checkout
echo "Runtime properties updated!"
