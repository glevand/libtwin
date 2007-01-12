#include <stdio.h>
#include <assert.h>
#include <sys/time.h>
#include <time.h>

#include "twin.h"
#include "twin_png.h"

#define TEST_PIX_WIDTH		1200
#define TEST_PIX_HEIGHT		 800


twin_pixmap_t	*src32, *dst32, *msk;
int twidth, theight, titers;

static void test_argb32_source_argb32(void)
{
	twin_operand_t srco;

	srco.source_kind = TWIN_PIXMAP;
	srco.u.pixmap = src32;
	twin_composite(dst32, 0, 0, &srco, 0, 0, NULL, 0, 0, TWIN_SOURCE,
		       twidth, theight);
}

static void test_argb32_over_argb32(void)
{
	twin_operand_t srco;

	srco.source_kind = TWIN_PIXMAP;
	srco.u.pixmap = src32;
	twin_composite(dst32, 0, 0, &srco, 0, 0, NULL, 0, 0, TWIN_OVER,
		       twidth, theight);
}

static void do_test(const char *name, void (*test)(void))
{
	struct timeval start, end;
	unsigned long long sus, eus;
	char spc[128];
	char *s;
	int i;

	printf("%s", name);

	gettimeofday(&start, NULL);
	for (i = 0; i < titers; i++)
		test();
	gettimeofday(&end, NULL);
	sus = (unsigned long long)start.tv_sec * 1000000ull + start.tv_usec;
	eus = (unsigned long long)end.tv_sec * 1000000ull + end.tv_usec;

	s = spc;
	for (i = strlen(name); i <40; i++)
		*(s++) = ' ';
	*s = 0;
	printf("%s %f sec\n", spc, ((float)(eus - sus)) / 1000000.0);
}

#define DO_TEST(name) do_test(#name, test_##name)

static void do_tests(int width, int height, int iters)
{
	twidth = width;
	theight = height;
	titers = iters;

	DO_TEST(argb32_source_argb32);
	DO_TEST(argb32_over_argb32);
}

static void do_all_tests(const char *title)
{
	printf("* %s, 10x10x1000000 :\n", title);
	do_tests(10, 10, 1000000);

	printf("* %s, 100x100x20000 :\n", title);
	do_tests(100, 100, 20000);

	printf("* %s, 200x200x10000 :\n", title);
	do_tests(200, 200, 10000);

	printf("* %s, 1200x800x200 :\n", title);
	do_tests(1200, 800, 200);

	printf("\n");
}

int main(void)
{
	printf("loading test pixmaps...\n");

	/* Create some test pixmaps */
	src32 = twin_png_to_pixmap("twinperf-src32.png", TWIN_ARGB32);
	assert(src32);
	dst32 = twin_pixmap_create(TWIN_ARGB32,
				 TEST_PIX_WIDTH, TEST_PIX_HEIGHT);
	assert(dst32);

#if 0
	msk = twin_pixmap_create(TWIN_A8,
				 TEST_PIX_WIDTH, TEST_PIX_HEIGHT);
	assert(msk);
#endif

	/* fill pixmaps */
	twin_fill(dst32, 0x80112233, TWIN_SOURCE, 0, 0,
		  TEST_PIX_WIDTH, TEST_PIX_HEIGHT);
		       

	/* pre-touch data */
	test_argb32_source_argb32();

	do_all_tests("No features");

	twin_feature_init();

	do_all_tests("All features");
	
	return 0;
}
