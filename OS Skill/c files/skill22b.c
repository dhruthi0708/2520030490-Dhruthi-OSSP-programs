#include <stdio.h>

int main()
{
    int passed = 0;
    int total = 3;

    /* Test Case 1 */
    if (2 + 2 == 4)
    {
        printf("Test 1: PASS\n");
        passed++;
    }
    else
    {
        printf("Test 1: FAIL\n");
    }

    /* Test Case 2 */
    if (5 * 3 == 15)
    {
        printf("Test 2: PASS\n");
        passed++;
    }
    else
    {
        printf("Test 2: FAIL\n");
    }

    /* Test Case 3 */
    if (10 > 3)
    {
        printf("Test 3: PASS\n");
        passed++;
    }
    else
    {
        printf("Test 3: FAIL\n");
    }

    printf("\nTest Report\n");
    printf("-----------\n");
    printf("Passed: %d\n", passed);
    printf("Failed: %d\n", total - passed);
    printf("Total : %d\n", total);

    if (passed == total)
        printf("Overall Result: PASS\n");
    else
        printf("Overall Result: FAIL\n");

    return 0;
}
