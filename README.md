# video-player-opencv
Video player with opencv library
![image](https://user-images.githubusercontent.com/33726233/116883830-3adf3580-ac50-11eb-89a2-33d8498f362c.png)

## About
Video player with undo, skip, play and pause control

## Compile and Run
```
$ g++ -std=c++11 -o test main.cpp `pkg-config --cflags --libs opencv` && ./test frag_bunny.mp4
```
notes: `frag_bunny.mp4` is the video file name to play.
