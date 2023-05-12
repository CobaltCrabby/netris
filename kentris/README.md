# KENTRIS
Kentris Evolved Networked Tetris Response Intelligence System

## routes
| route                | description |
|----------------------|-----------|
| `/asUser/<user>`       | be a user |
| `/asUser/<user>/lose`  | make it known that your user has lost |
| `/asUser/<user>/clear` | make it known that your user has made one clear |
| `/user/<user>/clears`  | get the clears of a user (resets to zero after retrieval) |
| `/user/<user>/lost`    | check if a user has lost, if so, you have won |
