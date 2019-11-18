#  Security

Author: David Kirk, 2019-11-18

## Summary
Because this is a purely written skill, I complete it within this report.


### Quest 3 Security Weaknesses:
1. The UDP communication between the microcontroller and the server is one-way and has no mechanism to determine whether a message is legitimate or not. An attacker could forge a message and it would still be interpreted as legitimate by either side. This attacker could also listen to messages and pass them on to steal information.
2. If the "find device" command is sent multiple times in a row, it will spawn multiple threads which fight for control over the red LED. If this command were sent enough times, it is possible that the device could run out of memory, or at least become very slow while processing all the threads.
3. Our server has no way of differentiating between different microcontrollers, and assumes that it only ever connects to one device. If there were multiple users on the system, then anyone could access everyone's data simply by going to the right HTML endpoint.

### Quest 3 Attack Methods:
As mentioned above:
1. Man-in-the-middle attack
2. Denial of service attack
3. Loading data from an endpoint the user isn't supposed to know about.

### Mitigation
1. This man-in-the-middle attack could be avoided with some sort of certificate or public key agreement protocol, which ensures that a message is genuine.
2. This particular denial of service attack could be avoided by only having one dedicated thread to blinking the red LED, and restarting it every time a new message is recieved. To avoid processing too many messages at once, we could also increase the cooldown after receiving each message, so that the microcontroller could only process one message every interval.
3. We could make this system more secure by including a database, and having the server perform queries to fetch data when a device with a certain ID is connected. That way, simply typing the endpoint's address into a browser window won't show all data for all users.

### IoT Provisioning

One approach to IoT provisioning could use a server-side database. Each ESP32 could have an ID associated with it, either hard-coded or somehow assigned at startup. This ID would be the key to a database which the server can use to store the data associated with each device. Each message received from each device would include this key, allowing it to be sorted into the right spot.

-----

## Reminders
- Repo is private
