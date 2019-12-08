#  Webcam

Author: David Kirk, 2019-12-03

## Summary
This skill consisted of figuring out what webcam software works best on the Raspberry Pi. Ultimately, we found mjpg-streamer to work best, given its high frame rates and relatively low latency.

## Modules, Tools, Source Used in Solution
We're using [mjpg-streamer](https://github.com/jacksonliam/mjpg-streamer) to stream video. To install, follow the instructions in the readme. To use, run the following commands:
```
cd ~/skill43/mjpg-streamer/mjpg-streamer-experimental
export LD_LIBRARY_PATH=.
./mjpg_streamer -i './input_uvc.so -d /dev/video0 -r 100x100 -f 10' -o './output_http.so -w ./www -p 8080'
```
This will create a server at port 8080 and stream video at 100x100 resolution.

NOTE: it seems to crash if run at 5fps.

## Supporting Artifacts
[![](http://img.youtube.com/vi/_r9w86t-d_o/0.jpg)](http://www.youtube.com/watch?v=_r9w86t-d_o "Webcam demo")


-----

## Reminders
- Repo is private
