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

    inputs = fscanf(file, "%d %d %c", &g->height, &g->width, &g->b_char);
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

void    set_circles() {

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
    draw(&g, surface);
}