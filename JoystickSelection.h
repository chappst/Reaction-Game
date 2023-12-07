#ifndef JOYSTICKSELECTION_H
#define JOYSTICKSELECTION_H

double Joystick_readX();
double Joystick_readY();
int JoystickDirection();
int JoystickChoice();
void displaySelectedDifficulty(int difficulty);

void displayEasy();
void displayMed();
void displayHard();

#endif /*JOYSTICKSELECTION_H*/
