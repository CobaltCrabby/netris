# KENTRIS
Kentris Evolved Networked Tetris Response Intelligence System

## requirements
To run this application you'll need:
- node
- npm
- redis

This application uses the redis cache as a database. The redis documentation has instructions
on how to get started but essentially all you need to do is install redis on a linux machine
and enable it as a service and start it.

An easy way to get this running for a quick demonstration is to
run the application (Go to the directory this readme is in), run
the application `node index.js`, and run `ngrok` on port 3000 (ngrok http 3000). And
then make sure you have redis described as detailed in the previous paragraph.
Through ngrok you will get an internet--accessible tunnel to the application.

You can also grab the local ip address, given everybody's in the same network, and
make requests directly to that address but the other options a little easier because it
jumps around weird school network stuff that can occur. Just know that both options are
good and available.

On a debian based distro like debian or ubuntu, setting up the application with ngrok and redis would look like this:

- clone the netris repo
- `cd kentris`
- `sudo apt-get install nodejs redis`
- `sudo systemctl enable redis`
- `sudo systemctl start redis`
- `npm install`
- `node index.js`
- `ngrok http 3000`

## routes
| route                | description |
|----------------------|-----------|
| `/asUser/<user>`       | be a user |
| `/asUser/<user>/lose`  | make it known that your user has lost |
| `/asUser/<user>/clear` | make it known that your user has made one clear |
| `/user/<user>/clears`  | get the clears of a user (resets to zero after retrieval) |
| `/user/<user>/lost`    | check if a user has lost, if so, you have won |

### AUTHOR
Jack Davidson
