#include <libft.h>

void	ft_strtabdel(char **str)
{
	size_t i;

	i = 0;
	while(str[i])
	{
		ft_strdel(&str[i]);
		i++;
	}
	ft_memdel((void **)str);
}
