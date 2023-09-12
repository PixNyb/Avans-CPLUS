int main() {
  int var1, var2;
  int *ptr1, *ptr2;

  /*
   * ptr1 = 0 naar var1 in memory
   * ptr2 = 0 naar var2 in memory
   * var1 = 0
   * var2 = 0
   */
  ptr1 = &var1;
  ptr2 = &var2;

  /*
   * ptr1 = var1 in memory
   * ptr2 = var2 in memory
   * var1 = 0 naar 63
   * var2 = 0 naar 9
   */
  *ptr1 = 63;
  *ptr2 = 9;

  /*
   * ptr1 = var1 in memory naar var2 in memory
   * ptr1 = var2 in memory naar var2 in memory
   * var1 = 63 naar 78
   * var2 = 9 naar 78
   */
  *ptr1 = *ptr2;
  ptr1 = ptr2;
  *ptr1 = 78;

  return 0;
}