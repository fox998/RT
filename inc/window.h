
#ifndef WINDOW_H
# define WINDOW_H
# include "obj.h"

typedef	struct			s_cam
{
	t_dvec3		pos;
	t_dvec3		dir;
	t_dvec3		plane;
}						t_cam;

typedef struct			s_img
{
	void		*img_ptr;
	char		*data;
	int			bit_pix;
	int			byte_pix;
	int			line_size;
	int			endian;
	int			w;
	int			h;
}						t_img;

typedef struct			s_window
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*cam;
	void		*scn;
	int			w;
	int			h;
}						t_window;

#endif