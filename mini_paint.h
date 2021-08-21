#ifndef __MINI_PAINT_H__
#define __MINI_PAINT_H__

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct  s_g {
	int		width;
	int		height;
	char	b_char;
}               t_g;

typedef struct	s_circle {
	char	type;
	float	x;
	float	y;
	float	radius;
	char	color;
}				t_circle;

#endif