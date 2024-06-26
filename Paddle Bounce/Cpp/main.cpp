#include <SFML/Graphics.hpp> // Simple and Fast Multimedia Library for game development and graphics
#include <SFML/Audio.hpp> // Simple and Fast Multimedia Library for game development and audio
#include <iostream> // Standard input/output stream library
#include <fstream> // Library for file handling

using namespace std; // Use the standard namespace for iostream
using namespace sf; // Use the SFML namespace for easier access to SFML classes

class Render // Main class for rendering the game window
{
private:
    RenderWindow window; // SFML window object used to create the window

public:
    Render(int width, int height, const string& name) // Constructor to create a window
    {
        window.create(VideoMode(width, height), name, Style::Close); // Create a window with given width, height, and title, with a close button
        window.setFramerateLimit(60); // Limit the frame rate to 60 FPS for smooth game
    }

    RenderWindow& getWindow() // Function to get the window object
    {
        return window;
    }
};

class Paddle // Class for the paddle
{
private:
    RectangleShape shape; // Shape object for the paddle

public:
    Paddle(float posX, float posY) // Constructor to initialize paddle position
    {
        shape.setSize(Vector2f(100.0f, 20.0f)); // Set the size of the paddle
        shape.setFillColor(Color::White); // Set the paddle color to white
        shape.setPosition(posX, posY); // Set the paddle's position
    }

    void paddle_left() // Function to move paddle left
    {
        if (shape.getPosition().x > 0) // Check if the paddle is within the left boundary
        {
            shape.move(-6.0f, 0.0f); // Move the paddle to the left
        }
    }

    void paddle_right(float windowWidth) // Function to move paddle right
    {
        if (shape.getPosition().x + shape.getSize().x < windowWidth) // Check if the paddle is within the right boundary
        {
            shape.move(6.0f, 0.0f); // Move the paddle to the right
        }
    }

    const FloatRect getGlobalBounds() // Function to get the paddle's bounding box
    {
        return shape.getGlobalBounds();
    }

    void draw(RenderWindow& window) // Function to draw the paddle
    {
        window.draw(shape);
    }

    void setPaddleColor(const Color& color) // Function to set the paddle color
    {
        shape.setFillColor(color);
    }
};

class Ball // Class for the ball
{
private:
    CircleShape shape; // Shape object for the ball
    float speedX; // Ball's speed in X direction
    float speedY; // Ball's speed in Y direction
    bool gameover; // Boolean to check if game is over
    int score; // Player's score
    int highscore; // High score
    int speedlevel; // Speed level of the ball
    Color initialColor; // Initial color of the ball
    ifstream inFile; // Input file stream for reading high score
    fstream file; // File stream for reading and writing high score

public:
    Ball() : speedX(0.0f), speedY(0.0f), gameover(false), score(0), speedlevel(0) // Default constructor
    {
        shape.setRadius(10.0f); // Set ball radius
        shape.setFillColor(Color::White); // Set ball color to white
        shape.setOutlineThickness(1.0f); // Set outline thickness
        shape.setOutlineColor(Color::Black); // Set outline color to black
        shape.setPosition(0.0f, 0.0f); // Set initial position
        shape.setOrigin(10.0f, 10.0f); // Set origin to center
    }

    Ball(float startX, float startY, const Color& initial) : speedX(7), speedY(7), gameover(false), score(0), speedlevel(0), initialColor(initial) // Parameterized constructor
    {
        shape.setRadius(10.0f); // Set ball radius
        shape.setOutlineThickness(1.0f); // Set outline thickness
        shape.setOutlineColor(Color::Black); // Set outline color to black
        shape.setPosition(startX, startY); // Set initial position
        shape.setOrigin(10.0f, 10.0f); // Set origin to center
        shape.setFillColor(initialColor); // Set initial color
    }

    void update(float windowWidth, float windowHeight, const FloatRect& paddleBounds) // Function to update ball position and check collisions
    {
        if (shape.getPosition().x > windowWidth - 10 || shape.getPosition().x < 10) // Check collision with left and right walls
        {
            speedX = -speedX; // Reverse X direction
        }
        if (shape.getPosition().y < 10) // Check collision with top wall
        {
            speedY = -speedY; // Reverse Y direction
        }

        if (shape.getPosition().y > windowHeight - 10) // Check if the ball falls below the screen
        {
            gameover = true; // Set gameover to true
        }

        if (shape.getGlobalBounds().intersects(paddleBounds)) // Check collision with the paddle
        {
            speedY = -speedY; // Reverse Y direction
            score++; // Increase score
            cout << "speedX: " << speedX << "speedY: " << speedY << " speedLevel: " << speedlevel << endl;
        }

        shape.move(speedX, speedY); // Move the ball
        speed(); // Update speed based on score
    }

    void reset(float startX, float startY) // Function to reset ball position and variables
    {
        shape.setPosition(startX, startY); // Set initial position
        speedX = 7.0f; // Reset speed in X direction
        speedY = 7.0f; // Reset speed in Y direction
        gameover = false; // Reset gameover status
        score = 0; // Reset score
        speedlevel = 0; // Reset speed level
    }

    void setInitialColor(const Color& color) // Function to set the initial color
    {
        initialColor = color;
        shape.setFillColor(initialColor);
    }

    const FloatRect getGlobalBounds() // Function to get ball's bounding box
    {
        return shape.getGlobalBounds();
    }

    void draw(RenderWindow& window) // Function to draw the ball
    {
        window.draw(shape);
    }

    void setBallColor(const Color& color) // Function to set ball color
    {
        shape.setFillColor(color);
    }

    bool isGameOver() const // Function to check if the game is over
    {
        return gameover;
    }

    int getScore() // Function to get the current score
    {
        return score;
    }

    int getHighScore() // Function to get and update the high score
    {
        file.open("highscore.txt", ios::in | ios::out); // Open high score file for reading and writing
        inFile.open("highscore.txt"); // Open high score file for reading
        inFile >> highscore; // Read high score from file
        if (score > highscore) // Check if current score is greater than high score
        {
            highscore = score; // Update high score
            file.seekp(0); // Set file pointer to beginning
            file << highscore; // Write new high score to file
        }
        else
        {
            highscore = highscore; // Retain current high score
            return highscore;
        }

        file >> highscore; // Read high score from file again
        file.close(); // Close file
        inFile.close(); // Close input file
    }

    void speed() // Function to update ball speed based on score
    {
        int newSpeedLevel = (score / 4); // Calculate new speed level

        if (newSpeedLevel != speedlevel) // Check if speed level has changed
        {
            if (speedX > 0)
            {
                speedX += (newSpeedLevel - speedlevel) * 1.0f; // Increase speed in X direction
            }

            else if (speedX < 0)
            {
                speedX -= (newSpeedLevel - speedlevel) * 1.0f; // Decrease speed in X direction
            }

            speedY -= (newSpeedLevel - speedlevel) * 1.0f; // Increase speed in Y direction
            speedlevel = newSpeedLevel; // Update speed level
        }
    }
};

class Graphics // Class for managing graphics
{
private:
    Texture texture, text, tex; // Texture objects for background, main menu, and options
    Sprite background, main, option; // Sprite objects for background, main menu, and options

public:
    Graphics() // Constructor to load textures and set sprites
    {
        texture.loadFromFile("bg.jpg"); // Load background texture
        text.loadFromFile("main.jpg"); // Load main menu texture
        tex.loadFromFile("opti.jpg"); // Load options texture
        background.setTexture(texture); // Set background sprite texture
        main.setTexture(text); // Set main menu sprite texture
        option.setTexture(tex); // Set options sprite texture
    }

    void drawbg(RenderWindow& window) // Function to draw background
    {
        window.draw(background);
    }

    void drawmm(RenderWindow& window) // Function to draw main menu
    {
        window.draw(main);
    }

    void drawop(RenderWindow& window) // Function to draw options menu
    {
        window.draw(option);
    }
};

class Song // Class for managing game sounds
{
private:
    SoundBuffer tune, mtune, ktune; // Sound buffer objects for game, main menu, and button sounds
    Sound ingame, inmain, keyp; // Sound objects for game, main menu, and button sounds

public:
    Song() // Constructor to load sound buffers and set sounds
    {
        tune.loadFromFile("game.ogg"); // Load game sound
        ingame.setBuffer(tune); // Set game sound buffer
        ingame.setLoop(true); // Set game sound to loop
        ingame.setVolume(5.0f); // Set game sound volume

        mtune.loadFromFile("main.ogg"); // Load main menu sound
        inmain.setBuffer(mtune); // Set main menu sound buffer
        inmain.setLoop(true); // Set main menu sound to loop
        inmain.setVolume(5.0f); // Set main menu sound volume

        ktune.loadFromFile("key.ogg"); // Load button sound
        keyp.setBuffer(ktune); // Set button sound buffer
        keyp.setVolume(15.0f); // Set button sound volume
    }

    void playGamesound() // Function to play game sound
    {
        if (ingame.getStatus() != Music::Playing)
        {
            ingame.play();
        }
    }

    void stopGameSound() // Function to stop game sound
    {
        if (ingame.getStatus() == Music::Playing)
        {
            ingame.stop();
        }
    }

    void playMainsound() // Function to play main menu sound
    {
        if (inmain.getStatus() != Music::Playing)
        {
            inmain.play();
        }
    }

    void stopMainSound() // Function to stop main menu sound
    {
        if (inmain.getStatus() == Music::Playing)
        {
            inmain.stop();
        }
    }

    void playButtonsound() // Function to play button sound
    {
        if (keyp.getStatus() != Music::Playing)
        {
            keyp.play();
        }
    }
};

enum class GameState // Enum class to handle game states
{
    MainMenu, // Main menu state
    Game, // Game state
    Options, // Options menu state
    Exit // Exit state
};

int main() // Main function
{
    Render windowManager(400, 600, "Paddle-Bounce"); // Create a window with given width, height, and title

    bool isPlaying = false; // Boolean to check if the game is playing
    bool isPaused = false; // Boolean to check if the game is paused
    GameState gameState = GameState::MainMenu; // Initialize game state to main menu

    Font font; // Font object
    font.loadFromFile("fut.ttf"); // Load font file

    Text text, tex; // Text objects for score and high score
    text.setFont(font); // Set font for text
    text.setCharacterSize(15); // Set character size
    text.setFillColor(Color::White); // Set text color to white
    text.setStyle(Text::Regular); // Set text style
    text.setString("Score: "); // Set initial text
    text.setPosition(10.0f, 10.0f); // Set position

    tex.setFont(font); // Set font for high score text
    tex.setCharacterSize(15); // Set character size
    tex.setFillColor(Color::White); // Set text color to white
    tex.setStyle(Text::Regular); // Set text style
    tex.setString("High-Score: "); // Set initial text
    tex.setPosition(250.0f, 10.0f); // Set position

    Paddle paddle(windowManager.getWindow().getSize().x / 2 - 60, 575); // Create a paddle at the bottom center
    Ball ball(windowManager.getWindow().getSize().x / 2, windowManager.getWindow().getSize().y / 2, Color::White); // Create a ball at the center
    ball.setInitialColor(Color::White); // Set initial color for the ball
    Graphics screen; // Create Graphics object for drawing
    Song msc; // Create Song object for sounds

    while (windowManager.getWindow().isOpen()) // Main game loop
    {
        Event event; // Event object

        while (windowManager.getWindow().pollEvent(event)) // Event handling loop
        {
            if (event.type == Event::Closed) // Check if window close event
            {
                windowManager.getWindow().close(); // Close the window
            }
            if (event.type == Event::KeyPressed) // Check if a key is pressed
            {
                if (event.key.code == Keyboard::Key::Escape) // Check if Escape key is pressed
                {
                    windowManager.getWindow().close(); // Close the window
                }
                else if (event.key.code == Keyboard::Key::Num1 && gameState == GameState::MainMenu) // Start game from main menu
                {
                    msc.playButtonsound(); // Play button sound
                    gameState = GameState::Game; // Change game state to Game
                }
                else if (event.key.code == Keyboard::Key::Num2 && gameState == GameState::MainMenu) // Open options from main menu
                {
                    msc.playButtonsound(); // Play button sound
                    gameState = GameState::Options; // Change game state to Options
                }
                else if (event.key.code == Keyboard::Key::Num3 && gameState == GameState::MainMenu) // Exit game from main menu
                {
                    msc.playButtonsound(); // Play button sound
                    windowManager.getWindow().close(); // Close the window
                }
                else if (event.key.code == Keyboard::Key::BackSpace && gameState != GameState::MainMenu) // Return to main menu from other states
                {
                    msc.playButtonsound(); // Play button sound
                    gameState = GameState::MainMenu; // Change game state to MainMenu
                }
                else if (event.key.code == Keyboard::Key::P && gameState == GameState::Game) // Pause/resume game
                {
                    msc.playButtonsound(); // Play button sound
                    isPaused = !isPaused; // Toggle pause state
                }
            }
        }

        windowManager.getWindow().clear(); // Clear the window

        if (gameState == GameState::MainMenu) // Main menu state
        {
            screen.drawmm(windowManager.getWindow()); // Draw main menu
            msc.playMainsound(); // Play main menu sound
        }
        else if (gameState == GameState::Options) // Options state
        {
            if (Keyboard::isKeyPressed(Keyboard::Key::I)) // Change ball color to red
            {
                msc.playButtonsound(); // Play button sound
                ball.setBallColor(Color::Red); // Set ball color to red
            }
            else if (Keyboard::isKeyPressed(Keyboard::Key::O)) // Change ball color to green
            {
                msc.playButtonsound(); // Play button sound
                ball.setBallColor(Color::Green); // Set ball color to green
            }

            if (Keyboard::isKeyPressed(Keyboard::Key::K)) // Change paddle color to blue
            {
                msc.playButtonsound(); // Play button sound
                paddle.setPaddleColor(Color::Blue); // Set paddle color to blue
            }
            else if (Keyboard::isKeyPressed(Keyboard::Key::L)) // Change paddle color to green
            {
                msc.playButtonsound(); // Play button sound
                paddle.setPaddleColor(Color::Green); // Set paddle color to green
            }
            screen.drawop(windowManager.getWindow()); // Draw options menu
        }
        else if (gameState == GameState::Game) // Game state
        {
            if (!isPaused) // If the game is not paused
            {
                if (!ball.isGameOver()) // If the game is not over
                {
                    if (Keyboard::isKeyPressed(Keyboard::Key::Left)) // Move paddle left
                    {
                        paddle.paddle_left();
                    }

                    if (Keyboard::isKeyPressed(Keyboard::Key::Right)) // Move paddle right
                    {
                        paddle.paddle_right(windowManager.getWindow().getSize().x);
                    }

                    ball.update(windowManager.getWindow().getSize().x, windowManager.getWindow().getSize().y, paddle.getGlobalBounds()); // Update ball position and check collisions
                    text.setString("Score: " + to_string(ball.getScore())); // Update score text
                    tex.setString("High-Score: " + to_string(ball.getHighScore())); // Update high score text
                    screen.drawbg(windowManager.getWindow()); // Draw background
                    windowManager.getWindow().draw(text); // Draw score text
                    windowManager.getWindow().draw(tex); // Draw high score text
                    paddle.draw(windowManager.getWindow()); // Draw paddle
                    ball.draw(windowManager.getWindow()); // Draw ball
                    msc.playGamesound(); //
                    msc.stopMainSound(); // Stop main menu sound
                }
                else // If the game is over
                {
                    gameState = GameState::MainMenu; // Change game state to main menu
                    msc.stopGameSound(); // Stop game sound
                    ball.reset(windowManager.getWindow().getSize().x / 2, windowManager.getWindow().getSize().y / 2); // Reset ball position
                    msc.stopMainSound(); // Stop main menu sound
                }
            }
            else // If the game is paused
            {
                Text pauseText; // Text object for pause message
                pauseText.setFont(font); // Set font for pause message
                pauseText.setCharacterSize(30); // Set character size
                pauseText.setFillColor(Color::White); // Set text color to white
                pauseText.setString("Game is Paused\nPress P to resume"); // Set pause message
                pauseText.setPosition((windowManager.getWindow().getSize().x - pauseText.getLocalBounds().width) / 2, (windowManager.getWindow().getSize().y - pauseText.getLocalBounds().height) / 2); // Set position
                windowManager.getWindow().draw(pauseText); // Draw pause message
                msc.stopGameSound(); // Stop game sound
            }
        }

        windowManager.getWindow().display(); // Display the window

        if (gameState == GameState::Exit) // Check if game state is exit
        {
            break; // Exit the game loop
        }
    }

    return 0; // Return 0 to indicate successful execution
}
