
#include "struct.h"
#include "libft.h"

static void		*lst_to_arr(t_list *lst)
{
	void	**arr;
	t_list	*tmp;
	int		size;
	int		i;

	size = 0;
	tmp = lst;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	arr = malloc(sizeof(t_obj_3d *) * size);
	i = -1;
	while (lst)
	{
		arr[++i] = lst->content;
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
	return (arr);
}

void	get_scene(void *window)
{
	t_scene		*scn;
	t_window	*wind;

	wind = window;
	scn = (t_scene *)malloc(sizeof(t_scene));
	scn->obj = lst_to_arr(wind->lst_obg);
	wind->scn = scn;
}