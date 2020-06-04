#include "unoptest.h"
#include "yats.h"

SETUP_YATS();

static void test_neg() {
	unsigned char expected[] = {
		0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		O_ICONST_B1, 0x10,
		O_LLOAD, 0x00,
		O_NEG,
		O_POP,
		O_HALT
	};
	ASSERT_GEN_BC_EQ(expected, "let x = 16; -x;");
}

static void test_len() {
	unsigned char expected[] = {
		0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		'Y', 'A', 'S', 'L',
		O_NEWSTR,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		O_LLOAD, 0x00,
		O_LEN,
		O_POP,
		O_HALT
	};
	ASSERT_GEN_BC_EQ(expected, "let x = 'YASL'; len x;");
}

static void test_not() {
	unsigned char expected[] = {
		0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		O_BCONST_T,
		O_LLOAD, 0x00,
		O_NOT,
		O_POP,
		O_HALT
	};
	ASSERT_GEN_BC_EQ(expected, "let x = true; !x;");
}

static void test_bnot() {
	unsigned char expected[] = {
		0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		O_ICONST_0,
		O_LLOAD, 0x00,
		O_BNOT,
		O_POP,
		O_HALT
	};
	ASSERT_GEN_BC_EQ(expected, "let x = 0x00; ^x;");
}

int unoptest(void) {
	test_len();
	test_neg();
	test_not();
	test_bnot();

	return __YASL_TESTS_FAILED__;
}
