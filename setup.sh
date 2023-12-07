config-pin P9.14 pwm
config-pin P9.16 pwm
config-pin P8.19 pwm

# export pin
echo 3 > /sys/class/pwm/export
echo 4 > /sys/class/pwm/export