#!/usr/bin/perl

$TTYDEV="/dev/cu.usbmodem1d11";
$SOUND_DIR="/Applications/iMovie HD.app/Contents/Resources/Sound Effects/Skywalker Sound Effects/";

open (TRIP, "<", "$TTYDEV") or die "Can't open Arduino";

while (<TRIP>){
    print;
    if (/tripped/){
        system("./halloween_sounds.sh"); 
    }
}

