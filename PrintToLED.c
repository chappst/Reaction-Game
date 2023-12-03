#include <OLED_Library.h> // Include OLED library
#include <LED_Library.h> // Include LED library
#include <Button_Library.h> // Include Button library
#include <Joystick_Library.h> // Include Joystick library

// Define OLED, LED, Button, Joystick pins and variables
OLED display(OLED_PIN);
LED led(LED_PIN);
Button button(BUTTON_PIN);
Joystick joystick(JOYSTICK_PIN);

int player1_points = 0;
int player2_points = 0;

void setup() {
  // Initialize OLED, LED, Button, Joystick
  display.begin();
  led.begin();
  button.begin();
  joystick.begin();
}

void loop() {
  // Turn on OLED and display welcome message
  display.print("Hello, welcome to the reaction game");
  delay(2000);
  display.print("To play the reaction game choose your difficulty level,\nEasy:\nSingle led goes on/off\nMedium:\nOnly press button when 2 leds goes on\nHard:\nOnly press button when an led is blue\nYou will play 20 iterations each round");
  delay(5000);
  
  // Ask if user wants to continue
  display.print("Do you want to continue? Double toggle the joystick left for yes.");
  while (!joystick.isDoubleToggledLeft()) {
    // Wait for user input
  }

  // Offer difficulty levels and exit option
  display.print("Choose difficulty level: Easy, Medium, Hard, Exit\nToggle joystick up or down, double toggle left to select");
  while (true) {
    if (joystick.isDoubleToggledLeft()) {
      // User selected level
      break;
    }
    // Wait for user input to select difficulty level or exit
  }

  // Start game countdown
  display.print("Game starting in 3...");
  delay(1000);
  display.print("2...");
  delay(1000);
  display.print("1...");
  delay(1000);
  
  // Game loop for 20 iterations
  for (int i = 0; i < 20; i++) {
    // Game logic based on selected difficulty level
    
    // Update player points
    // For example:
    player1_points++;
    player2_points++;
    
    // Display player points
    display.print("Player 1: " + String(player1_points) + "\nPlayer 2: " + String(player2_points));
    
    // Delay between rounds
    delay(1000);
  }
}
