/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_ex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:55:54 by naal-jen          #+#    #+#             */
/*   Updated: 2023/03/21 22:41:18 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * ?casi gestiti:
 * * $$         	✔
 * * $ $ $ $ $  	✔
 * * "$"        	✔
 * * $ "$" $    	✔
 * * $ "$ $" $  	✔
 * * $ " $ "    	✔
 * * $ " $ $ "  	✔
 * * '$'        	✔
 * * $ '$' $    	✔
 * * $ '$ $' $  	✔
 * * ' $ '      	✔
 * * $ ' $ '    	✔
 * * $ ' $ $ '  	✔
 * * "'$'"      	✔
 * * $ "'$'"    	✔
 * * $ "'$ $'" $	✔
 * * $ "' $ '"  	✔ echo $USER "' $USER '"
 * * $ "' $'"   	✔ echo $USER "' $USER'"
 * * $ "'$ '"   	✔ echo $USER "'$USER '"
 * * $ "' $ $ '" 	✔ echo "' $USER $USER '"
 * * $ "' $ $'"  	✔ echo "' $USER $USER'"
 * * $ "'$ $ '"  	✔ echo "'$USER $USER '"
 * * $ " ' $ ' " 	✔ echo $USER " ' $USER ' "
 * * $ " ' $' "  	✔ echo $USER " ' $USER' "
 * * $ " '$ ' "  	✔ echo $USER " ' $USER' "
 * * $ " ' $  $ ' "	✔ echo $USER " ' $USER $USER ' "
 * * $ " ' $  $' "	✔ echo $USER " ' $USER $USER' "
 * * $ " '$  $ ' "	✔ echo $USER " '$USER $USER ' "
 * * " $ "        	✔ echo " $USER "
 * 
 * TODO: da gestire
 * * '"$"' when its before you dont print the ' you do print the " and between you dont have to expand the variable
 * * $ '"$"'
 * * $ '" $ "'
 * * $ '"$ "'
 * * $ '" $"'
 * * $ '" $ $ "'
 * * $ '" $ $"'
 * * $ '"$ $"'
 * * $ '" $$ "'
 * * $ ' "$" '
 * * $ ' "$ " '
 * * $ ' " $" '
 * * $ ' " $ $ " '
 * * $ ' " $ $" '
 * * $ ' "$ $" '
 * * $ ' " $$ " '
 * * $ $ "$$"
 * 
 * !casi che non devono essere gestiti
 * * $ "' $ $ "' -> quote
 * * $ "' $ $ "" -> dquote
 * * $ ' $ " $ " -> quote
 * * $ ' $ $ "   -> quote
 * 
 * Todo: funzione da creare:
 * * funziona che stampa la env prendendo il variabile dal $
*/

int	full_size(char *str)
{
	int i;
	int j;
	int	size_cmd;
	int		size_full;
	char	*cmd;
	char	*var;

	i = 0;
	j = 0;
	size_cmd = 0;
	size_full = 0;
	size_full = ft_strlen(str);
	while (str[i])
	{
		if (str[i] == '$')
		{
			j = i + 1;
			while (str[j] && (!(str[j] >= 9 && str[j] <= 13)))
			{
				j++;
			}
			var = ft_substr(str, i + 1, j - i);
			size_full -= ft_strlen(var) + 1;
			cmd = getenv(var);
			if (cmd)
			{
				size_cmd += ft_strlen(cmd);
			}
			else
				size_full += ft_strlen(var) + 1;
			i = j - 1;
		}
		i++;
	}
	size_cmd += size_full;
	return (size_cmd + 2);
}

char	*control_ex(char *str)
{
	int		size_for_malloc;
	int	i;
	int	j;
	int		case_1; //? the case where we have "''"
	int		case_2; //? the case where we have '""'
	int		case_3;
	int		case_4; //? know am after a '
	char	*var; // variable to be expanded
	char	*cmd; // hold the value of the variable expanded
	char	*new_str; // final string to be returned
	char	**str_split;
	char	**new_split;
	int		help_me_man;

	i = 0;
	j = 0;
	help_me_man = 0;
	case_1 = 0;
	case_2 = 0;
	case_3 = 0;
	case_4 = 0;
	size_for_malloc = full_size(str);
	str_split = ft_split(str, ' ');
	new_str = (char *)malloc(sizeof(char) * size_for_malloc + 1);
	while (str_split[i][j])
	{
		new_str[j] = str_split[i][j];
		j++;
	}
	new_str[j] = ' ';
	j++;
	new_str[j] = '\0';
	i++;
	j = 0;
	while (str_split[i])
	{
		if (ft_strnstr(str_split[i], "\"", ft_strlen(str_split[i])))
		{
			i++;
			if (str_split[i] && ft_strnstr(str_split[i], "\'", ft_strlen(str_split[i])))
			{
				case_3 = 1;
				break ;
			}
			else
				i--;
		}
		i++;
	}
	i = 1;
	if (case_3 == 1)
	{
		// printf("hello me and you\n");
		while (str_split[i])
		{
			// printf("%s\n", str_split[i]);
			if (ft_strnstr(str_split[i], "\'", ft_strlen(str_split[i])) && (!(ft_strnstr(str_split[i], "$", ft_strlen(str_split[i])))))
			{
				// printf("am i here now \n");
				new_str = ft_strjoin(new_str, "\1'");
				new_str = ft_strjoin(new_str, " ");
			}
			else if (ft_strnstr(str_split[i], "$", ft_strlen(str_split[i])))
			{
				if (ft_strnstr(str_split[i], "\'", 1) || ft_strnstr(str_split[i], "\'", 2))
					case_3 = 3;
				else if (ft_strnstr(str_split[i], "$", ft_strlen(str_split[i])) && (ft_strnstr(str_split[i], "\'", ft_strlen(str_split[i]) - 1) || ft_strnstr(str_split[i], "\'", ft_strlen(str_split[i]) - 2)))
					case_3 = 6;
				// printf("%d\n", case_3);
				var = ft_strchr(str_split[i], '$');
				var++;
				j = ft_strlen(var);
				if (var[j - 1] == '\'')
				{
					j--;
					var[j] = '\0';
					cmd = getenv(var);
					new_str = ft_strjoin(new_str, cmd);
					new_str = ft_strjoin(new_str, "\'");
					case_3 = 4;
				}
				else if (!(var[j - 1] >= 'A' && var[j - 1] <= 'Z'))
				{
					while((!(var[j - 1] >= 'A' && var[j - 1] <= 'Z')))
						j--;
					var[j] = '\0';
				}
				if (case_3 != 4 && case_3 != 3 && case_3 != 6)
				{
					cmd = getenv(var);
					if (cmd == NULL)
					{
						printf("i have a problem with the cmd man help!! case_1\n");
						new_str = ft_strjoin(new_str, " ");
					}
					else
					{
						new_str = ft_strjoin(new_str, cmd);
						new_str = ft_strjoin(new_str, " ");
					}
				}
				else if (case_3 == 3)
				{
					// printf("hello\n");
					cmd = getenv(var);
					if (cmd == NULL)
					{
						printf("i have a problem with the cmd man help!! case_1\n");
						new_str = ft_strjoin(new_str, " ");
					}
					else
					{
						// printf("hello\n");
						new_str = ft_strjoin(new_str, "\1'");
						new_str = ft_strjoin(new_str, cmd);
						new_str = ft_strjoin(new_str, " ");
						case_3 = 0;
					}

				}
				else if (case_3 == 6)
				{
					// printf("helloma\n");
					// new_str = ft_strjoin(new_str, "\1'");
					new_str = ft_strjoin(new_str, cmd);
					new_str = ft_strjoin(new_str, "' ");
					case_3 = 0;

				}
			}
			i++;
		}
	}
	while (str_split[i])
	{
		if (ft_strnstr(str_split[i], "\"", ft_strlen(str_split[i])) && ft_strnstr(str_split[i], "\'", ft_strlen(str_split[i])))
		{
			while (str_split[i][j])
			{
				if (str_split[i][j] == '\"')
				{
					if (ft_strnstr(str_split[i], "\'", ft_strlen(str_split[i])))
					case_1 = 1;
					break ;
				}
				else if (str_split[i][j] == '\'')
				{
					case_2 = 1;
					j++;
					while (str_split[i][j] != '\'')
					{
						if (str_split[i][j] == '$')
						{

						}
						new_str = ft_strjoin(new_str, str_split[i] + j);
					}
				}
				j++;
			}
			j = 0;
			if (case_1 && ft_strnstr(str_split[i], "$", ft_strlen(str_split[i])))
			{
				var = ft_strchr(str_split[i], '$');
				var++;
				j = ft_strlen(var);
				if (!(var[j - 1] >= 'A' && var[j - 1] <= 'Z'))
				{
					while((!(var[j - 1] >= 'A' && var[j - 1] <= 'Z')))
						j--;
					var[j] = '\0';
					case_1 = 2;
				}
				// printf("%s\n%d\n", var, j);
				cmd = getenv(var);
				// printf("%s\n", cmd);
				if (cmd == NULL)
				{
					printf("i have a problem with the cmd man help!! case_1\n");
					new_str = ft_strjoin(new_str, " ");
				}
				else if (case_1 == 1)
				{
					new_str = ft_strjoin(new_str, "\1'");
					new_str = ft_strjoin(new_str, cmd);
					new_str = ft_strjoin(new_str, " ");
					help_me_man = 1;
				}
				else if (case_1 == 2 && help_me_man == 1)
				{
					
					new_str = ft_strjoin(new_str, cmd);
					new_str = ft_strjoin(new_str, "\' ");
					case_1 = 1;

				}
				else if (case_2 == 1)
				{
					var = ft_strchr(str_split[i], '$');
					var++;
					cmd = getenv(var);
					if (cmd == NULL)
					{
						printf("i have a problem with the cmd man help!! case_1\n");
						new_str = ft_strjoin(new_str, " ");
					}
					new_str = ft_strjoin(new_str, cmd);
					new_str = ft_strjoin(new_str, "\'");
				}
				else
				{
					new_str = ft_strjoin(new_str, "\1'");
					new_str = ft_strjoin(new_str, cmd);
					new_str = ft_strjoin(new_str, "'");
				}
				j = 0;
			}
			else
			{
				// printf("heelo\n£");
				new_str = ft_strjoin(new_str, "\1'");
				new_str = ft_strjoin(new_str, " ");
			}
		}
		else if (ft_strnstr(str_split[i], "\'", ft_strlen(str_split[i])))
		{
				// printf("heelo1\n");
			if (ft_strnstr(str_split[i], "\'", 1) && str_split[i][ft_strlen(str_split[i]) - 1] == '\'') //! here
			{
				// printf("heelo2\n");
				new_str = ft_strjoin(new_str, str_split[i]);
				new_str = ft_strjoin(new_str, " ");
				if (case_4 != 2)
					case_4 = 1;
				
			}
			else if (ft_strnstr(str_split[i], "$", 2) && (ft_strnstr(str_split[i], "\'", 1) || str_split[i][ft_strlen(str_split[i]) - 1] == '\''))
			{
				// printf("heelo3\n");
				new_str = ft_strjoin(new_str, str_split[i]);
				new_str = ft_strjoin(new_str, " ");
			}
			else
			{
				// printf("heelo4\n");
				i++;
				new_str = ft_strjoin(new_str, "\1'");
				while ((ft_strnstr(str_split[i], "\'", ft_strlen(str_split[i]))) == NULL)
				{
					
					i++;
				}
			}
		}
		else if (ft_strnstr(str_split[i], "$", 1))
		{
			// printf("hello am here now\n");
			if (ft_strnstr(str_split[i], "\"", ft_strlen(str_split[i])) && ft_strnstr(str_split[i], "\'", ft_strlen(str_split[i])))
			{
				var = ft_substr(str_split[i], 1, ft_strlen(str_split[i]) - 3);
				cmd = getenv(var);
				if (cmd == NULL)
				{
					printf("1i have a problem with the cmd man help!! $\n");
					new_str = ft_strjoin(new_str, " ");
				}
				else
				{
					new_str = ft_strjoin(new_str, cmd);
					new_str = ft_strjoin(new_str, " ");
				}

			}
			else if (ft_strnstr(str_split[i], "\"", ft_strlen(str_split[i])))
			{
				var = ft_substr(str_split[i], 1, ft_strlen(str_split[i]) - 2);
				cmd = getenv(var);
				if (cmd == NULL)
				{
					printf("i have a problem with the cmd man help!!2\n");
					new_str = ft_strjoin(new_str, " ");
				}
				else
				{
					new_str = ft_strjoin(new_str, cmd);
					new_str = ft_strjoin(new_str, " ");
				}
			}
			else if (ft_strnstr(str_split[i], "\'", ft_strlen(str_split[i])))
			{
				var = ft_substr(str_split[i], 0, ft_strlen(str_split[i]) - 1);
				new_str = ft_strjoin(new_str, var);
				new_str = ft_strjoin(new_str, " ");
			}
			else
			{
				if (case_4 == 1)
				{
					new_str = ft_strjoin(new_str, str_split[i]);
					new_str = ft_strjoin(new_str, " ");
					case_4 = 2;
				}
				else
				{
					var = ft_substr(str_split[i], 1, ft_strlen(str_split[i]));
					if (ft_strnstr(var, "$", ft_strlen(var)))
					{
						new_split = ft_split(var, '$');
						while (new_split[j])
						{
							cmd = getenv(new_split[j]);
							if (cmd == NULL)
							{
								printf("i have a problem with the cmd man help!!3\n");
								new_str = ft_strjoin(new_str, " ");
							}
							else
								new_str = ft_strjoin(new_str, cmd);
							j++;
						}
						j = 0;
					}
					else
					{
						cmd = getenv(var);
						if (cmd == NULL)
						{
							printf("i have a problem with the cmd man help!!3\n");
							new_str = ft_strjoin(new_str, " ");
						}
						else
						{
							new_str = ft_strjoin(new_str, cmd);
							new_str = ft_strjoin(new_str, " ");
						}
					}
				}
			}
		}
		else if (ft_strnstr(str_split[i], "\"", 1) && ft_strnstr(str_split[i], "$", 2))
		{
			var = ft_substr(str_split[i], 2, ft_strlen(str_split[i]) - 2);
			if (var[strlen(var) - 1] == '"')
				var[strlen(var) - 1] = '\0';
			cmd = getenv(var);
			if (cmd == NULL)
			{
				printf("i have a problem with the cmd man help!!4\n");
				new_str = ft_strjoin(new_str, " ");
			}
			else
			{
				new_str = ft_strjoin(new_str, cmd);
				new_str = ft_strjoin(new_str, " ");
			}
		}
		else if (ft_strnstr(str_split[i], "\'", 1) && ft_strnstr(str_split[i], "$", 2))
		{
			if (str_split[i][ft_strlen(str_split[i]) - 1] == '\'')
			{
				var = ft_substr(str_split[i], 1, ft_strlen(str_split[i]) - 2);
				new_str = ft_strjoin(new_str, var);
				new_str = ft_strjoin(new_str, " ");
			}
			else
			{
				var = ft_substr(str_split[i], 1, ft_strlen(str_split[i]) - 1);
				new_str = ft_strjoin(new_str, var);
				new_str = ft_strjoin(new_str, " ");
			}
		}
		else if (str_split[i])
		{
			new_str = ft_strjoin(new_str, str_split[i]);
			new_str = ft_strjoin(new_str, " ");
		}
		i++;
	}
	return (new_str);
}
