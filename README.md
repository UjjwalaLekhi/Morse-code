# Morse-code
In this project we have made a wireless Morse code transmitter with piezoelectric input. Two piezoelectric disks are used to take input: one for dots and one for dashes. The output of the piezoelectric signal is fed to a conditioning circuit, the output of which is then fed to a monostable mode 555 timer circuit. The 555 timer circuit converts the short peizoelectric signals to a stable pulse of a longer duration. These pulses form parallel data inputs, which are fed into the HT12E encoder to convert the parallel data into serial format. The encoded serial data is transmitted wirelessly via an RF transmitter module.

On the receiver side, an RF receiver module captures the signal and passes it to the HT12D decoder, which converts the serial data back into parallel form.
An ESP32 microcontroller processes the decoded dot and dash inputs, translates the Morse code into corresponding characters, and displays the output on an LCD screen.
