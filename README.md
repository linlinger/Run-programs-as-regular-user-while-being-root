# Run programs as regular user while being root

This qt application will simply  open a browser window as a regular user while the qt application is running with root privilege.


# Why I wrote this application?
At first I wanna open Firefox in a qt application running as root. and Firefox gives me the following error message

Running Firefox as root in a regular user's session is not supported.  ($XAUTHORITY is /home/linlinger/.Xauthority which is owned by linlinger.)

So I wanna fix it. My idea is open a Firefox window as the regular user who start the qt application running as root. And I believe there would be  some cases like me. So I write this qt application as an example to open some applications don't support running as root by an application running as root.

# How it works
	I use logname to get currently logged in username and use sudo -u to run command as the user.

# Attention before proceeding
	This application requires logname and xdg-open command installed
	Firefox needs to be the default browser

# Building the application
qmake -makefile

make

# Running the application as root

## using sudo

sudo application executable

## using pkexec
pkexec env DISPLAY=$DISPLAY XAUTHORITY=\$XAUTHORITY  '/path/to/executable'

