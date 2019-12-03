#  Webcam

Author: David Kirk, 2019-12-03

## Summary


## Sketches and Photos


## Modules, Tools, Source Used in Solution


## Supporting Artifacts
We're using [mjpg-streamer](https://github.com/jacksonliam/mjpg-streamer) to stream video. To install, follow the instructions in the readme. To use, run the following commands:
```
cd ~/skill43/mjpg-streamer/mjpg-streamer-experimental
export LD_LIBRARY_PATH=.
./mjpg_streamer -i './input_uvc.so -d /dev/video0 -r 320x240 -f 15' -o './output_http.so -w ./www -p 8080'
```
This will create a server at port 8080 and stream video at 320x240 resolution.


-----

## Reminders
- Repo is private
