#!/bin/bash
if [[ -n "$(pgrep test.o)" ]]; then
	pkill test.o
	~/Documents/eww/target/release/eww close mpd-client
else
	~/Documents/eww/target/release/eww open mpd-client
	exec ~/.config/eww/test.o
fi
