#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

/** @brief Sets pin `pin` to the desired `state`.
 *
 * Opens the corresponding pin file in write only mode, after
 * which the state is written to it and the file is closed.
 * This is used to control the state of GPIO pins on a Raspberry Pi.
 *
 * @param pin The pin to write the state to
 * @param state The state to set `pin` to (HIGH, 1 or LOW, 0)
 * @returns Void.
 */
void set_pin(char* pin, int state) {
  int file_descriptor;
  char pin_path[52];
  char state_as_str[2];

  sprintf(pin_path, "/sys/class/gpio/gpio%s/value", pin);
  sprintf(state_as_str, "%d", state);

  file_descriptor = open(pin_path, O_WRONLY);
  write(file_descriptor, state_as_str, 1);
  close(file_descriptor);
}

/** @brief Initializes `pin` for use with `set_pin()`.
 *
 * Opens the general GPIO export file and writes `pin` to it to enable the pin.
 * After that the direction of the pin according to `direction` is written to
 * the pin file to note if it is an output or input.
 * This is used to initialize GPIO pins for use on a Raspberry Pi.
 *
 * @param pin The pin to write the state to
 * @param direction The direction of the pin (`in` for input, `out` for output)
 * @returns Void.
 */
void init_pin(char* pin, char* direction) {
  int file_descriptor;
  char pin_path[52];

  sprintf(pin_path, "/sys/class/gpio/gpio%s/direction", pin);

  file_descriptor = open("/sys/class/gpio/export", O_WRONLY);
  write(file_descriptor, pin, 2);
  close(file_descriptor);

  sleep(1);

  file_descriptor = open(pin_path, O_WRONLY);
  write(file_descriptor, direction, 3);
  close(file_descriptor);

  set_pin(pin, 0);
}