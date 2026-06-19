#/usr/bin/env bash

input="bad_apple.mp4"
output="bad_apple_full.gif"
width=160
height=80
fps=15

if !command -v ffmpeg &>/dev/null; then
	echo "ffmpeg is missing. Install it to continue."
	return 1
fi

ffmpeg -i $input -vf \
	"fps=$fps,scale=$width:$height:flags=lanczos,split[s0][s1];[s0]palettegen=max_colors=4[p];[s1][p]paletteuse=dither=none" \
	$output