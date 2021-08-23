#include "mini_paint.h"

size_t  s_strlen(const char *str) {
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char    s_error(const char *str) {
    write(1, str, s_strlen(str));
    
    return (1);
}

int     set_surface(t_g *g, char **surface, FILE *file) {
    int inputs;
    int i;

    inputs = fscanf(file, "%d %d %c\n", &g->height, &g->width, &g->b_char);
    if (inputs != 3)
        return (1);
    *surface = (char *) malloc(sizeof(char) * (g->height * g->width + 1));
    if (!*surface)
        return (1);
    for (i = 0; i < (g->height * g->width); i++) {
        (*surface)[i] = g->b_char;
    }
    (*surface)[i] = '\0';
    return (0);
}

char    in_circle(t_circle *circle, float x, float y) {
    float   dist;

    dist = sqrtf(powf(x - circle->x, 2) + powf(y - circle->y, 2));
    if (dist <= circle->radius) {
        if (circle->radius - dist < 1)
            return (2);
        return (1);
    }
    return (0);
}

char    set_circles(t_g *g, FILE *file, char **surface) {
    t_circle    circle;
    int         inputs;
    int         border;

    inputs = 5;
    while (inputs == 5) {
        inputs = fscanf(file, "%c %f %f %f %c\n", &circle.type, &circle.x, &circle.y, &circle.radius, &circle.color);
        if (inputs != 5)
            return (1);
        if (circle.radius <= 0 || (circle.type != 'c' && circle.type != 'C'))
            return (1);
        for (int y = 0; y < g->height; y++) {
            for (int x = 0; x < g->width; x++) {
                border = in_circle(&circle, x, y);
                if ((circle.type == 'c' && border == 2) || (circle.type == 'C' && border == 1))
                    (*surface)[y * g->width + x] = circle.color;
            }
        }
    }
    return (0);
}

void    draw(t_g *g, char *surface) {
    for (int i = 0; i < g->height; i++) {
        write(1, surface + (i * g->width), g->width);
        write(1, "\n", 1);
    }
}

int main(int ac, char **av) {
    t_g     g;
    FILE *  file;
    char *  surface;

    memset(&g, 0, sizeof(t_g));
    surface = NULL;
    if (ac != 2)
        return (s_error("Error: argument\n"));
    if (!(file = fopen(av[1], "r")))
        return (s_error("Error: Operation file corrupted\n"));
    set_surface(&g, &surface, file);
    set_circles(&g, file, &surface);
    draw(&g, surface);
}