# My Debian Setup Guide

This is just my quick-notes on fixing that and getting updates and theming on my fresh installs.
Out of the box, the Debian `sources.list` has been messed up for quite some time,
getting rid of the extra stuff that comes along with a fresh boot is tedious,
and there's other little quality of life stuff I just don't wanna have to constantly tinker with
every time I install a new Debian image somewhere.

## Grab an ISO, Burn a Stick

This is the most self-explanatory part, I thinks.
Get a stable debian install image from 
`https://cdimage.debian.org/debian-cd/current/amd64/iso-dvd/`
or wherever makes sense, and use a utility
like Rufus, Balena Etcher, or GNOME Multiwriter.
During installation I skip setting up the network
because a lot of times its finecky.
Set up the network after the inital boot into the installed system.

## Fixing Apt

1. Edit the sources list
`sudo nano /etc/apt/sources.list` <br>
and add replace its content with <br>
`deb http://ftp.debian.org/debian/ bookworm main contrib non-free non-free-firmware`
Then run `sudo apt upgrade` and `sudo apt update`

## Removing "bloat"/add-on software

The normal way to do this is opening the Synaptic Package Manager
and then manually going through your packages and selecting what ya do and don't
want, but I think that's a pain. So, instead, here's a lil script to remove
most of the not-so-necessary stuff.

```sh
sudo apt remove \
firefox-esr firefox-esr-* aisleriot anthy anthy-common aspell aspell-* \
cheese cheese-common coinor-* culmus eog espeak-* evince evolution evolution-* \
fcitx5 fcitx5-* fortune-mod fortunes-* four-in-a-row geoclue-* ghostscript \
gnome-calculator gnome-calendar gnome-chess gnome-contacts gnome-games gnome-klotski \
gnome-mahjongg gnome-maps gnome-mines gnome-music gnome-nibbles gnome-online-accounts \
gnome-robots gnome-sudoku gnome-taquin gnome-tetravex gnome-weather hdate-applet \
hitori hoichess hspell hspell-* hunspell hunspell-* hyphen-* iagno ispell kasumi \
libaa1  libanthy* mlterm mlterm-* mozc-* mueller7-dict ispell myspell myspell-* \
mythes-* opencc quadrapassel re rhythmbox rhythmbox-* shotwell shotwell-common \
swath swath-data swell-foop t1-* tali totem totem-* vim vim-* \
wamerican wbrazilian wbulgarian wcatalan wdanish wdutch wfrench witalian wngerman \
wnorwegian wpolish wportugese wspanish wswedish xiterm+thai
```
A lot of these packages just seem really silly to me.
Why does Debian include like six different competiting spellcheckers?
Why do some of them not even include an English dictionary on an `EN-US` Debian install?
Why do we have a specifically Thai terminal 
(_that is ostensibly just an English terminal anyway_)?
Why are these so many different versions of the same couple games?
No idea, we nuke em regardless. 
Then we install useful schtuff for our Desktop Environment.
```sh
sudo dpkg --add-architecture i386
sudo apt update
sudo apt install \
git gcc tcc tilix flatpak chromium vlc \
libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev libsdl2-net-dev \
gnome-shell-extensions gnome-shell-extension-manager chrome-gnome-shell codium \
libc6:i386 libstdc++6:i386 libvulkan1:i386 mesa-vulkan-drivers:i386
flatpak remote-add --if-not-exists flathub https://dl.flathub.org/repo/flathub.flatpakrepo
flatpak update
```
Optionally, if you wanna add Steam at this point,
```sh
flatpak install flathub com.valvesoftware.Steam
```

## Setting up useful shortcuts

Go into the settings widget, scroll down to Keyboard,
and at the very bottom click `View and Customize Shortcuts`.
In `Custom Shortcuts`, add the shortcut (ex. `Super + T`)
and bind it to the file you made before.
Mine looks something like:
![image](https://github.com/user-attachments/assets/2a66a2a3-cac3-4590-ad2c-39b943ef53f9)

## Customizing the Desktop

Here's a couple extensions I really like:
[michele_g's `Dash to Dock`](https://extensions.gnome.org/extension/307/dash-to-dock/) <br>
I recommend enabling `Toggle On All Monitors`, making the icons a little smaller (32px),
disabling `Show _Applications_ Icon`, `Show Trash Can` and `Show volumes and devices`, 
`Show Overview on Startup`, and then manually setting the color and opacity of the dock;
I personally like `15% Black`. 

[0cry0n's `Resource Monitor`](https://extensions.gnome.org/extension/1634/resource-monitor/)
I like to disable decimals and set it up so that it shows everything in percentages.

Then, of course, remove the random crap that's on the Dock by default
and put the stuff you want. I like to have my web browser and terminal,
and maybe Steam depending on what the machine is for.

## Building my homebrew utils

I like having a place to put / install my homebrew software,
so we're gonna go ahead and set that up, too.
```sh
mkdir -p ~/.local/bin
echo export PATH="$HOME/.local/bin:$PATH=" >> ~/.bashrc
```
Then we download and built
```sh
cd ~/.local/bin && git clone https://github.com/JohnAlexINL/JohnAlexINL.git .
chmod +x build
mkdir -p tmp
./build && rm -rf ./src
```
