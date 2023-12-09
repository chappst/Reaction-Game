#ifndef JOYSTICKSEL_H
#define JOYSTICKSEL_H
//Referenced a guide from Brian Fraser

double Joystick_readX();
double Joystick_readY();
int JoystickDirection();
int JoystickChoice();
void displaySelectedDifficulty(int difficulty);

void displayEasy();
void displayMed();
void displayHard();

#endif /*JOYSTICKSEL_H*/
