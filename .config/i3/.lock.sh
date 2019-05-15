#!/bin/bash

image=/tmp/i3lock.png
screenshot="scrot $image"

#blurtype="0x5" # 7.52s
#blurtype="0x2" # 4.39s
blurtype="5x2" # 3.80s
#blurtype="2x8" # 2.90s
#blurtype="2x3" # 2.92s

# Get the screenshot, add the blur and lock the screen with it
$screenshot
convert $image -resize 50%
convert $image -blur $blurtype $image
convert $image -resize 200%
#convert $image ~/.config/i3/lock.png -gravity center -composite -matte $image
i3lock -i $image
rm $image
