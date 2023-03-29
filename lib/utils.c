/* utils.c */
/** @brief Hash `str` to `hash` for use in a switch case
 *
 * A string needs to be hashed for it to be used
 * inside of a switch statement. We want to use a switch
 * statement instead of an if-else chain for it's
 * simplicity and lower amount of low-level operations.
 *
 * @param str The string to hash
 *
 * @returns hash The hashed version of `str`
 */
unsigned long hash(const char *str) {
  unsigned long hash = 5381;
  unsigned long int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + c;
  return hash;
}