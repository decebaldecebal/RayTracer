/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rserban <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 11:34:22 by rserban           #+#    #+#             */
/*   Updated: 2015/03/11 15:58:19 by rserban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

void        savebmp(const char *filename, int w, int h, int dpi, t_color *data)
{
    FILE *f;
    int k, s, filesize, m, ppm;
    double factor;
    unsigned char bmpfileheader[14] = {'B', 'M', 0,0,0,0,  0,0,0,0,  54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0};

    k = w * h;
    s = 4 * k;
    filesize = 54 + s;
    factor = 39.375;
    m = static_cast<int>(factor);
    ppm = dpi * m;

    bmpfileheader[ 2] = (unsigned char)(filesize);
	bmpfileheader[ 3] = (unsigned char)(filesize>>8);
	bmpfileheader[ 4] = (unsigned char)(filesize>>16);
	bmpfileheader[ 5] = (unsigned char)(filesize>>24);

	bmpinfoheader[ 4] = (unsigned char)(w);
	bmpinfoheader[ 5] = (unsigned char)(w>>8);
	bmpinfoheader[ 6] = (unsigned char)(w>>16);
	bmpinfoheader[ 7] = (unsigned char)(w>>24);

	bmpinfoheader[ 8] = (unsigned char)(h);
	bmpinfoheader[ 9] = (unsigned char)(h>>8);
	bmpinfoheader[10] = (unsigned char)(h>>16);
	bmpinfoheader[11] = (unsigned char)(h>>24);

	bmpinfoheader[21] = (unsigned char)(s);
	bmpinfoheader[22] = (unsigned char)(s>>8);
	bmpinfoheader[23] = (unsigned char)(s>>16);
	bmpinfoheader[24] = (unsigned char)(s>>24);

	bmpinfoheader[25] = (unsigned char)(ppm);
	bmpinfoheader[26] = (unsigned char)(ppm>>8);
	bmpinfoheader[27] = (unsigned char)(ppm>>16);
	bmpinfoheader[28] = (unsigned char)(ppm>>24);

	bmpinfoheader[29] = (unsigned char)(ppm);
	bmpinfoheader[30] = (unsigned char)(ppm>>8);
	bmpinfoheader[31] = (unsigned char)(ppm>>16);
	bmpinfoheader[32] = (unsigned char)(ppm>>24);

	f = fopen(filename, "wb");

	fwrite(bmpfileheader, 1, 14, f);
	fwrite(bmpinfoheader, 1, 40, f);

	for (int i = 0; i < k; i++)
    {
		double red = data[i].r;
		double green = data[i].g;
		double blue = data[i].b;

		unsigned char color[3] = {(int)floor(blue),(int)floor(green),(int)floor(red)};

		fwrite(color, 1, 3, f);
	}

	fclose(f);
}

t_mat		*new_material(t_color *c, float diff, float refl, float refr[2])
{
	t_mat *mat;

	mat = (t_mat *)malloc(sizeof(t_mat));
	if (!mat)
		mem_error();
	mat->color.r = c->r;
	mat->color.g = c->g;
	mat->color.b = c->b;
	mat->diff = diff;
	mat->spec = 1.0f - diff;
	mat->refl = refl;
	mat->refr = refr[0];
	mat->refrind = refr[1];
	return (mat);
}

int			main()
{
	t_env	e;
	char filein[50];
	char fileout[50];
    std::clock_t start;
    std::thread t[THREADS];

    e.objs = NULL;
    e.lights = NULL;
    e.aliasingsq = ANTIALIASING * ANTIALIASING;
    e.totpixels = WIN_WIDTH * WIN_HEIGHT;
    cout<<"Input file:\n";
    cin>>filein;
    read_file(&e, filein);
    if (!e.objs)
        mem_error();
    e.img = (t_color *)malloc(sizeof(t_color) * (WIN_WIDTH * WIN_HEIGHT));
    if (!e.img)
        mem_error();
    cout<<"Output to:\n";
    cin>>fileout;
    cout<<endl;
    start = std::clock();
    printf("Rendering...\n");
    for (int i = 0;i < THREADS;i++)
        t[i] = std::thread(draw_scene, &e, WIN_HEIGHT / THREADS * i, WIN_HEIGHT / THREADS * (i + 1));
    for (int i = 0;i < THREADS;i++)
        t[i].join();
    if (!strstr(fileout, ".bmp"))
        strcat(fileout, ".bmp");
    savebmp(fileout, WIN_WIDTH, WIN_HEIGHT, 72, e.img);
    cout<<"\nRendering complete in "<<(double)(std::clock() - start ) / (double) CLOCKS_PER_SEC<<" seconds.\nImaged saved to: "<<fileout<<endl;
    free_environment(&e);
    return (0);
}
