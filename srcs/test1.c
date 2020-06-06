#include <math.h>
#include <stdio.h>

typedef struct test_t
{
	double r;
	double g;
	double b;
}				test;

test	multi(test *a, test *b)
{
	test result;

	result.r = fmin(a->r * b->r, 1.0);
	result.g = fmin(a->g * b->g, 1.0);
	result.b = fmin(a->b * b->b ,1.0);
	return (result);
}


typedef union	u_color
{
	int				combination;
	unsigned char	color_array[4];
}				t_union_color;


int main(void)
{
	test	a;
	test	b;
	test	new;

	a.r = 0.15231;
	a.g = 0.5893;
	a.b = 0.942324;

	b.r = 0.3627;
	b.g = 0.23470918;
	b.b = 0.14327089;

	new = multi(&a, &b);
	// printf("%f %f %f", new.r, new.g, new.b);

	t_union_color c;

	c.color_array[2] = 0.23470918 * 256;
	c.color_array[1] = 0.14327089 * 256;
	c.color_array[0] = 0.15231 * 256;

	int color =  65536 * c.color_array[2] + 256 * c.color_array[1] + c.color_array[0];
	
	printf("%d %d %d\n", c.color_array[2], c.color_array[1], c.color_array[0]);
	printf("%d", color);
	return (0);
 }