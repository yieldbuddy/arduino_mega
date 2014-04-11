The default Username and Password are both:   default
See the Raspberry Pi folder's 'readme' for more details.

yieldbuddy v1.17a - May 5, 2013

-Switched everything from MySQL to SQLite3
-Uses nginx instead of Apache 
-Python script much more reliable, and now with event logging
-void main() in the arduino sketch has a section for restoring defaults (just uncomment, run, then comment out again)
-Updated look of web interface, fixed up some code.
-Updates database only when values change now, increasing performance of the script by a lot
-Warning: Shuts down anything accessing database when it starts
-Data points are taken at regular time intervals now. Default: 90 seconds (960 points / day)
-Switched graphs from High Charts to Google Charts (uses Flash instead of Java)
-Added log to 'System' page
-More error handling
-Some minor interface changes in the Python Script, also lists Interface IP Addresses
-Changed all paths to reference Server Root, so everything can be run in a different location (not just /var/www). This was so you can run yieldbuddy on a USB flash drive and save your SD card from too many read/writes
-Activated analog read of TDS1, TDS2, and CO2 sensors (see sensor functions in Arduino sketch to change the formulas to match that of your equipment [datasheets]) 
-Updated install script - let me know how it goes on the forum, as I manually installed so this should work

yieldbuddy v1.16 - Mar 28, 2013

-Fixed set arduino time under system
-Fixed RTC setup sketch to use only the DS1307RTC library
-Split sketch into seperate files
-Fixed relay buttons on overview.php into a table
-Removed lighting and watering pages and put them on a new timers page
-Updated scripts to ensure yieldbuddy and wireless connection both stay up and running
-Added Email Address & Camera Connectback Address Settings to the Settings Page
-Added Alarms for the setpoint values which will automatically email you if out of range
-Encrypts email password as a hash in sql database and generates a new random key everytime you click "Save Email Settings".
(Doesn't store plaintext password, for better security)
-Cleaned up code a bit, with better error handling.

yieldbuddy v1.15c
-Created a daemon script that constantly checks to make sure your connected to your network (wlan0) and to make sure yieldbuddy is running
-Updated install script, again.
-Added redirect so you don't have to go to <ip address>/yieldbuddy/www anymore --->  <ip address>/yieldbuddy

yieldbuddy v1.15b
-Updated install script - tested and works.
-Raspberry Pi SD Image available on www.yieldbuddy.com


---Forum is up and running---


yieldbuddy v1.15
-Data logging is done to an SQL Database now (runs a lot faster now)
-Manual/Auto Relay Modes
-HighChart graphs added that display information from SQL Database (zoomable)
-Added Cambozola applet for viewing streaming webcam via motion
-Added a couple scripts that act like daemons checking to see if the wireless connection is still alive, if not, restart connection and another to check to make sure yieldbuddy is still running, if not, restarts yieldbuddy.
-Install script for Raspberry Pi added


Project Name Changed To: yieldbuddy -----------------------------------------------------------------
Website: www.yieldbuddy.com is alive!


Environment Controller v1.14b
-Fixed Water Timer issue going from PM to AM

Environment Controller v1.14
-Sessions are now used and you are required to login. See the readme in the Raspberry Pi folder for more details.  (username: default  password: default)
-Added data-parsing capabilities for settings, information, etc to the arduino
-Added "Lighting", "Watering", "Set Points", "System" pages
-Added Time Settings to System Page
-Added Restore Defaults to System Page  <--  Recommended after fresh firmware upgrade!
-Tested/Fixed timer issues
-envirocontrol.py lists/asks for the path of the serial device you would like to use upon startup

Environment Controller v1.13
-Fixed up touchscreen interface (odd touchscreen coordinates)
-New 'Defaults" button under 'Settings' (Arduino) writes settings to EEPROM (Run this after a fresh install to avoid bugs!)
-Updated Python script for less data points (making big log files)

Environment Controller v1.12
-Bundled everything a little nicer
-Included some 'readme' files :)
-Some files were missing; everything is complete, organized and easier to understand.

Environment Controller v1.11
-Graph generates automatically
-Edited gnuplot plotData.plt file
-Fixed Read Fail's
-Added firmware upload for arduino (new file: upload.php)
-Renamed dataLogger.py (python script) to envirocontrol.py

Environment Controller v1.10
-Basic Frontend for Sensor Values and Relay Controls
-Python script for rx/tx through serial port (USB RS-232)

Environment Controller v1.0
-Basic Ardunio Code working with Touchscreen
