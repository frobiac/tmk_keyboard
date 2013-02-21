make -f Makefile.lufa hypernano &&
teensy_loader_cli -mmcu=atmega32u4 -w -v frobiac.hex &&
sudo -S /usr/sbin/hid_listen
