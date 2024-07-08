# Midgard Sherphant

Midgard Sherphant is a unique twist on the classic snake game implemented in C++ using object-oriented programming principles. The game introduces a new challenge: poisonous food that can decrease the snake's health, leading to its death if consumed excessively, even without being bitten by its body.

## Features

- **Classic Snake Gameplay**: Navigate the snake around the board to consume food and grow.
- **Poisonous Food**: Be careful of poisonous food that decreases the snake's health.
- **Health System**: The snake has a health attribute that decreases with each poisonous food consumed and regenerates slightly with normal food.
- **Game Over Conditions**: The game ends if the snake's health reaches zero or it collides with itself or the board boundaries.

## Classes

- **Snake**: Manages the snake's position, movement, and health.
- **Food**: Represents both normal and poisonous food, including their effects on the snake.
- **Game**: Controls the game logic, including the game loop, collision detection, and game state.

## How to Play

1. Use arrow keys to move the snake around the board.
2. Eat normal food to grow and increase your score.
3. Avoid or limit consumption of poisonous food to maintain the snake's health.
4. The game ends if the snake's health reaches zero, if it collides with itself, or if it runs into the board boundaries.

## Installation

1. Clone the repository:
