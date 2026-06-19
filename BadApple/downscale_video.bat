@echo off

set input="bad_apple.mp4"
set output="bad_apple_full.gif"
set width=160
set height=80
set fps=15

ffmpeg -i %input% -vf "fps=%fps%,scale=%width%:%height%:flags=lanczos,split[s0][s1];[s0]palettegen=max_colors=4[p];[s1][p]paletteuse=dither=none" %output%