#include "yats.h"
#include "matchtest.h"

SETUP_YATS();

static void test_simple() {
	unsigned char expected[] = {
		0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x61, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		C_INT_1, 1,
		C_STR,
		0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		'o', 'n', 'e',
		C_STR,
		0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		'n', 'o', 't', ' ', 'o', 'n', 'e',
		O_LIT, 0x00,
		O_LLOAD, 0x00,
		/* first pattern */
		O_MATCH,
		0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		P_LIT, 0x00,
		O_POP,
		O_LIT, 0x01,
		O_ECHO,
		O_BR_8,
		0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		/* second pattern */
		O_MATCH,
		0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		P_ANY,
		O_POP,
		O_LIT, 0x02,
		O_ECHO,
		O_HALT
	};
	ASSERT_GEN_BC_EQ(expected, "let x = 1; match x { 1 { echo 'one'; }; * { echo 'not one'; }; };");
}

static void test_list() {
	unsigned char expected[] = {
		0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		C_INT_1, 2,
		C_INT_1, 1,
		C_STR,
		0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		'v', 'a', 'r',
		O_END,
		O_NEWLIST,
		O_LLOAD, 0x00,
		/* first pattern */
		O_MATCH,
		0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		P_LS,
		0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		P_ANY,
		P_ANY,
		O_POP,
		O_LIT, 0x00,
		O_ECHO,
		O_BR_8,
		0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		/* second pattern */
		O_MATCH,
		0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		P_LS,
		0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		P_ANY,
		O_POP,
		O_LIT, 0x01,
		O_ECHO,
		O_BR_8,
		0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		/* third pattern */
		O_MATCH,
		0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		P_VLS,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		O_POP,
		O_LIT, 0x02,
		O_ECHO,
		O_HALT
	};
	ASSERT_GEN_BC_EQ(expected, "let x = []; match x { [ *, * ] { echo 2; }; [ * ] { echo 1; }; [ ... ] { echo 'var'; }; };");
}

static void test_table() {
	unsigned char expected[] = {
		0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x9E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		C_STR,
		0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		'x',
		C_STR,
		0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		'y',
		C_INT_1, 2,
		C_INT_1, 1,
		C_STR,
		0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		'v', 'a', 'r',
		O_END,
		O_NEWTABLE,
		O_LLOAD, 0x00,
		/* first pattern */
		O_MATCH,
		0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		P_TABLE,
		0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		P_LIT, 0x00,
		P_ANY,
		P_LIT, 0x01,
		P_ANY,
		O_POP,
		O_LIT, 0x02,
		O_ECHO,
		O_BR_8,
		0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		/* second pattern */
		O_MATCH,
		0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		P_TABLE,
		0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		P_LIT, 0x00,
		P_ANY,
		O_POP,
		O_LIT, 0x03,
		O_ECHO,
		O_BR_8,
		0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		/* third pattern */
		O_MATCH,
		0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		P_VTABLE,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		O_POP,
		O_LIT, 0x04,
		O_ECHO,
		O_HALT
	};
	ASSERT_GEN_BC_EQ(expected, "let x = {}; match x { { .x: *, .y: * } { echo 2; }; { .x: * } { echo 1; }; { ... } { echo 'var'; }; };");
}

static void test_bind() {
	unsigned char expected[] = {
		0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x56, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		C_INT_1, 1,
		C_STR,
		0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		'o', 'n', 'e',
		O_LIT, 0x00,
		O_LLOAD, 0x00,
		/* first pattern */
		O_MATCH,
		0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		P_LIT, 0x00,
		O_POP,
		O_LIT, 0x01,
		O_ECHO,
		O_BR_8,
		0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		/* second pattern */
		O_MATCH,
		0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		P_BIND, 0x01,
		O_INCSP, 0x01,
		O_DEL, 0x01,
		O_LLOAD, 0x01,
		O_ECHO,
		O_POP,
		O_HALT
	};
	ASSERT_GEN_BC_EQ(expected, "let x = 1; match x { 1 { echo 'one'; }; let x { echo x; }; };");
}

static void test_bind_list() {
	unsigned char expected[] = {
		0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x5F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		C_INT_1, 1,
		C_STR,
		0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		'o', 'n', 'e',
		O_END,
		O_LIT, 0x00,
		O_NEWLIST,
		/* first pattern */
		O_MATCH,
		0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		P_LIT, 0x00,
		O_POP,
		O_LIT, 0x01,
		O_ECHO,
		O_BR_8,
		0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		/* second pattern */
		O_MATCH,
		0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		P_LS,
		0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		P_BIND, 0x00,
		O_INCSP, 0x01,
		O_DEL, 0x00,
		O_LLOAD, 0x00,
		O_ECHO,
		O_POP,
		O_HALT
	};
	ASSERT_GEN_BC_EQ(expected, "match [ 1 ] { 1 { echo 'one'; }; [ let x ] { echo x; }; };");
}

TEST(matchtest) {
	test_simple();
	test_list();
	test_table();
	test_bind();
	test_bind_list();

	return NUM_FAILED;
}
