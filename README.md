# taggsystem
SUF taggsystem för maskiner

# Dependencies
Install the `MFRC522` - library for arduino

# Connections in prototype

LED pin 6 (out)
button signal in 7
button activation pin 8 (should be always on)
relay pin 2


# States

0 - Default. Identified user or admin will signal to the relay, holding button at the same time triggers state 1
1 - Admin state - Add user, button triggers next state, tag adds user
2 - Admin state - Add admin, button triggers next state, tag adds admin
3 - Admin state - Remove admin, button triggers next resets to next state, tag deletes user
