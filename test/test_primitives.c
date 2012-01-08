#include <stdlib.h>
#include <check.h>

#include <argon/primitives/ops.h>

START_TEST(check_not)
{
   uint8_t val[] = {255,255,255,255,0,0,0,0,1,1,1,1,254,254,254,254,
                    128,128,128,128,127,127,127,127,2,2,2,2,253,253,253,253};
   uint8_t res[32];

   ar_vnot_u8(res,val,32);

   for (uint32_t i = 0; i < 32; i++) {
      fail_if(res[i] != 255 - val[i], "~x = y, where y + x = 255");
   }
}
END_TEST

START_TEST(check_add)
{
   uint8_t val_1[] = {12,23,34,45,56,67,78,89,90,10,11,12,13,14,15,16,
                      17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
   uint8_t val_2[] = {4,1,4,2,4,3,4,4,4,5,4,6,4,7,4,8,
                      5,1,5,2,5,3,5,4,5,5,5,6,5,7,5,7};

   uint8_t res[32];

   ar_vadd_u8(res,val_1,val_2,32);

   for (uint32_t i = 0; i < 32; i++) {
      fail_if(res[i] != val_1[i] + val_2[i], "res should be val_1 + val_2");
   }
}
END_TEST

START_TEST(check_sub)
{
   uint8_t val_1[] = {12,23,34,45,56,67,78,89,90,10,11,12,13,14,15,16,
                      17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
   uint8_t val_2[] = {4,1,4,2,4,3,4,4,4,5,4,6,4,7,4,8,
                      5,1,5,2,5,3,5,4,5,5,5,6,5,7,5,7};

   uint8_t res[32];

   ar_vsub_u8(res,val_1,val_2,32);

   for (uint32_t i = 0; i < 32; i++) {
      fail_if(res[i] != val_1[i] - val_2[i], "res should be val_1 - val_2");
   }
}
END_TEST

START_TEST(check_max)
{
   uint8_t val_1[] = {5,3,5,3,4,4,8,8,9,1,5,5,7,8,7,8,
                      2,4,6,8,9,7,9,9,8,8,8,8,5,6,5,6};
   uint8_t val_2[] = {4,2,2,2,5,7,9,9,8,0,4,2,6,9,6,9,
                      3,5,7,9,8,6,4,2,9,9,9,9,4,7,2,9};

   uint8_t res[32];

   ar_vmax_u8(res,val_1,val_2,32);

   for (uint32_t i = 0; i < 32; i++) {
      fail_if(res[i] % 2 == 0, "For this test, All maxs should be 1 mod 2");
   }
}
END_TEST

START_TEST(check_min)
{
   uint8_t val_1[] = {5,3,5,3,4,4,8,8,9,1,5,5,7,8,7,8,
                      2,4,6,8,9,7,9,9,8,8,8,8,5,6,5,6};
   uint8_t val_2[] = {4,2,2,2,5,7,9,9,8,0,4,2,6,9,6,9,
                      3,5,7,9,8,6,4,2,9,9,9,9,4,7,2,9};

   uint8_t res[32];

   ar_vmin_u8(res,val_1,val_2,32);

   for (uint32_t i = 0; i < 32; i++) {
      fail_if(res[i] % 2 == 1, "For this test, All mins should be 0 mod 2");
   }
}
END_TEST

START_TEST(check_mul)
{
   uint8_t val_1[] = {5,3,5,3,4,4,8,8,9,1,5,5,7,8,7,8,
                      2,4,6,8,9,7,9,9,8,8,8,8,5,6,5,6};
   uint8_t val_2[] = {4,2,2,2,5,7,9,9,8,0,4,2,6,9,6,9,
                      3,5,7,9,8,6,4,2,9,9,9,9,4,7,2,9};

   uint8_t res[32];

   ar_vmul_u8(res,val_1,val_2,32);

   for (uint32_t i = 0; i < 32; i++) {
      fail_if(res[i] != val_1[i] * val_2[i], "res should be val_1 * val_2");
   }
}
END_TEST

Suite *
primitive_suite()
{
   Suite *s = suite_create("Primitives");

   /* Core test case */
   TCase *tc_basics = tcase_create("Basics");
   tcase_add_test(tc_basics, check_not);
   tcase_add_test(tc_basics, check_add);
   tcase_add_test(tc_basics, check_sub);
   tcase_add_test(tc_basics, check_max);
   tcase_add_test(tc_basics, check_min);
   tcase_add_test(tc_basics, check_mul);
   suite_add_tcase(s, tc_basics);

   return s;
}

int main()
{
   int number_failed;
   Suite *s = primitive_suite();
   SRunner *sr = srunner_create(s);
   srunner_run_all(sr, CK_NORMAL);
   number_failed = srunner_ntests_failed(sr);
   srunner_free(sr);
   return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

