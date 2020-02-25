# VACR_CTF_arduino-xmit-cw
VA Cyber Range CTF for arduino RF transmitting competition flags.


<IMG SRC=pics/VACR_CTF_arduino-xmit-cw-user.png width=250 align=right>In the VA Cyber Range, we like to do IoT and RF challenges.  In this one, we use an arduino to transmit a 2MHz CW square 
wave which appears across the whole spectrum. Students have to use the SDR kits we provide (recommend the
[RTL-SDR Dongle](https://www.rtl-sdr.com/buy-rtl-sdr-dvb-t-dongles/) ) to sniff around looking for a "low power, 
intermittent signal around the 150MHz range".

<IMG SRC=pics/VACR_CTF_arduino-xmit-cw-box1.png width=250 align=right>The schematic is as simple as a single wire hanging off the Arduino's ping D9, or if you want a bit more range, put a 
small 50 ohm coil from pin9 to GND to get more signal out there. If you want it to run all day, I recommend keeping hte LED off 
(prevent it from blinking) and even desoldering the power LED if you want the 9v battery to last a long time. 
 Here's what the box I put it in looked like. 
 
 <IMG SRC=pics/VACR_CTF_arduino-xmit-cw-box2.png width=250 align=right>Here's a photo of the UVA & GMU students at the [VMI CyberFusion 2020 conference](https://www.vmi.edu/about/conferences/cyberfusion/). Good Times...

<IMG SRC=http://theweeks.org/tmp/PICS/Tweeks-laptop-SDR-antenna.png width=250 align=right>[This is the SDR Kit](https://www.amazon.com/dp/B011HVUEME) kit I got from Amazon. It's one of the better RTL SDR kids as it includes the temp compensated radio, a nice set of rabbit ear antennas (to cover several bands) as well as a little tripod and glass/laptop suction cup.
