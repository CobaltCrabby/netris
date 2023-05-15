# KENTRIS
Kentris Evolved Networked Tetris Response Intelligence System

## Getting Started
To run this application you'll need:
- node
- npm
- redis

### installing the necessary services
```bash
sudo apt-get install nodejs redis
```
### redis
This application uses the redis cache as a database. The redis documentation has instructions
on how to get started but essentially all you need to do is install redis on a linux machine
and and start it as a systemd service.
```bash
sudo systemctl start redis
```

## Running 
- Clone the code from the git repository, or download it as a zip file.
- go to the kentris directory, it'll be the one with the index.js file
- make sure `redis` has been started as described in the previous paragraph
- `npm install` to install the javascript dependencies needed for this application
- `node index.js` to run the application

## accessing the application
You can choose to run `ngrok` on the application to create a tunnel
where you can access the application from anywhere on the internet.
OR you can choose to access the application directly by the local ip address
of the computer running kentris.

To find the ip of a linux computer:
```bash
hostname -I
```

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
