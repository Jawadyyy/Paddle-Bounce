# Paddle-Bounce 

A simple paddle-ball game built using the Simple and Fast Multimedia Library (SFML). The objective is to keep the ball from falling below the paddle while it bounces off the paddle and walls. The game tracks the score and high score.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Game Controls](#game-controls)
- [Features](#features)
- [File Structure](#file-structure)
- [Credits](#credits)

## Installation

1. Clone the repository:
    ```sh
    git clone https://github.com/your-username/paddle-bounce.git
    cd paddle-bounce
    ```
2. Install SFML library:
    - On Ubuntu:
        ```sh
        sudo apt-get install libsfml-dev
        ```
    - On Windows:
        - Download and install SFML from [https://www.sfml-dev.org/download.php](https://www.sfml-dev.org/download.php).

3. Compile the code:
    ```sh
    g++ -c main.cpp
    g++ main.o -o paddle-bounce -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
    ```
  
4. Downnload the Zip:
    - Just play the game by downloading the Zip

## Usage

Run the executable:
```sh
./paddle-bounce
```

## Example
![Game Screenshot](https://imgur.com/a/m5KUS1i)

## Game Controls

- `Left Arrow`: Move paddle left
- `Right Arrow`: Move paddle right
- `Num1`: Start game (from main menu)
- `Num2`: Options menu (from main menu)
- `Num3`: Exit game (from main menu)
- `Backspace`: Return to main menu
- `P`: Pause/resume game
- `I`: Change ball color to red (in options)
- `O`: Change ball color to green (in options)
- `K`: Change paddle color to blue (in options)
- `L`: Change paddle color to green (in options)

## Features

- Paddle movement
- Ball bouncing
- Score tracking
- High score tracking
- Pause/resume functionality
- Change ball and paddle colors

## File Structure

- `main.cpp`: Main source code file
- `bg.jpg`: Background image
- `main.jpg`: Main menu image
- `opti.jpg`: Options menu image
- `game.ogg`: Game sound file
- `main.ogg`: Main menu sound file
- `key.ogg`: Button sound file
- `fut.ttf`: Font file
- `highscore.txt`: File to store high score

## Credits

- **Simple and Fast Multimedia Library (SFML)**: [SFML Library](https://www.sfml-dev.org/)
- **Game Developer**: Jawadyyy


## Contributing

Contributions are welcome! Please fork the repository and submit a pull request with your changes. For major changes, please open an issue first to discuss what you would like to change.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

