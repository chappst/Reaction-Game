#include <OLED_Library.h> // Include OLED library
#include <LED_Library.h> // Include LED library
#include <Button_Library.h> // Include Button library
#include <Joystick_Library.h> // Include Joystick library
#include<stdio.h>
#include<stdlib.h>

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
  display.print("To play the reaction game choose your difficulty level");
  delay(5000);
  display.print("Easy:\nSingle led goes on/off");
  delay(5000);
  display.print("Medium:\nOnly press button when 2 leds goes on");
  delay(5000);
  display.print("Hard:\nOnly press button when an led is blue");
  delay(5000); 
  display.print("You will play 20 iterations each round");
  
  // Ask if user wants to continue
  bool userWantsToContinue = false;

  while (!userWantsToContinue) {
  display.print("Do you want to continue? Toggle the joystick left/right to select, double toggle left to confirm.");

  bool selected = false;
  bool yesSelected = true; // Initial selection is on "Yes"
  
  while (!selected) {
    // Display options ("Yes" and "No")
    if (yesSelected) {
      display.print("> Yes\nNo");
    } else {
      display.print("Yes\n> No");
    }

    // Check joystick input to select option
    if (joystick.isToggledLeft()) {
      yesSelected = true;
    } else if (joystick.isToggledRight()) {
      yesSelected = false;
    } else if (joystick.isDoubleToggledLeft()) {
      selected = true;
    }

    // Delay for responsiveness
    delay(100);
  }

  // Check user's final selection
  if (yesSelected) {
    userWantsToContinue = true;
  } else {
    // Perform actions for "No" selection or exit the loop
    // For example:
    // Exit the game or perform other actions
    break;
  }
}


  // Offer difficulty levels and exit option
  int selectedLevel = 0; // Represents the selected level: 0 for Easy, 1 for Medium, 2 for Hard, 3 for Exit

  while (true) {
  display.print("Choose difficulty level: Easy, Medium, Hard, Exit\nToggle joystick up or down, double toggle left to select");

  // Display the options based on the selected level
  if (selectedLevel == 0) {
    display.print("> Easy\nMedium\nHard\nExit");
  } else if (selectedLevel == 1) {
    display.print("Easy\n> Medium\nHard\nExit");
  } else if (selectedLevel == 2) {
    display.print("Easy\nMedium\n> Hard\nExit");
  } else if (selectedLevel == 3) {
    display.print("Easy\nMedium\nHard\n> Exit");
  }

  // Check joystick input to scroll through options and select
  if (joystick.isToggledUp()) {
    selectedLevel = (selectedLevel + 3) % 4; // Move selection up
  } else if (joystick.isToggledDown()) {
    selectedLevel = (selectedLevel + 1) % 4; // Move selection down
  } else if (joystick.isDoubleToggledLeft()) {
    // User selected level or Exit
    if (selectedLevel == 0) {
      // Perform actions for Easy level selection
      break;
    } else if (selectedLevel == 1) {
      // Perform actions for Medium level selection
      break;
    } else if (selectedLevel == 2) {
      // Perform actions for Hard level selection
      break;
    } else if (selectedLevel == 3) {
      // Perform actions for Exit selection or exit the loop
      // For example:
      // Exit the game or perform other actions
      break;
    }
  }

  // Delay for responsiveness
  delay(100);
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
