/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_ex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:55:54 by naal-jen          #+#    #+#             */
/*   Updated: 2023/03/24 11:58:39 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		i; //? index
	int		j; //? index
	int		y; //? helper index
	int		case_1; //? the case where we have "''"
	int		case_2; //? the case where we have '""'
	int		case_3; //? 
	int		case_4; //? know am after a '
	int		case_5; //? where you have this struct '"$USER"'
	int		start;
	int		done;
	char	*var; // variable to be expanded
	char	*cmd; // hold the value of the variable expanded
	char	*new_str; // final string to be returned
	char	**str_split;
	char	**new_split;
	int		help_me_man;

	i = 0;
	j = 0;
	y = 0;
	help_me_man = 0;
	case_1 = 0;
	case_2 = 0;
	case_3 = 0;
	case_4 = 0;
	case_5 = 0;
	start = 0;
	done = 1;
	size_for_malloc = full_size(str);
	str_split = ft_split(str, ' ');
	new_str = (char *)malloc(sizeof(char) * size_for_malloc + 1);

	//! -------------------------------------------------------------------------- */
	//!                       add you first command and clean it                   */
	//! -------------------------------------------------------------------------- */
	while (str_split[i][j])
	{
		if (str_split[i][j] == '\'' || str_split[i][j] == '\"')
			j++;
		new_str[y] = str_split[i][j];
		j++;
		y++;
	}
	new_str[y] = ' ';
	y++;
	new_str[y] = '\0';
	i++;
	j = 0;

	//! -------------------------------------------------------------------------- */
	//!                to chech for the " ' ' " and for the ' " " '                */
	//! -------------------------------------------------------------------------- */
	while (str_split[i])
	{
		if (ft_strnstr(str_split[i], "\"", 1))
		{
			i++;
			if (str_split[i] && ft_strnstr(str_split[i], "\'", ft_strlen(str_split[i])))
			{
				case_3 = 1;
				printf("this is my case\n");
				break ;
			}
			else
				i--;
		}
		else if (ft_strnstr(str_split[i], "\'", 1) && ft_strlen(str_split[i]) == 1)
		{
			i++;
			if (str_split[i] && ft_strnstr(str_split[i], "\"", ft_strlen(str_split[i])))
			{
				case_1 = 1;
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
					if (str_split[i][0] == '\'')
						new_str = ft_strjoin(new_str, "\1\'");
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
	else if (case_1 == 1)
	{
		i++;
		while (str_split[i])
		{
			if (ft_strnstr(str_split[i], "\"", ft_strlen(str_split[i])) && (!(ft_strnstr(str_split[i], "$", ft_strlen(str_split[i])))))
			{
				new_str = ft_strjoin(new_str, "\1\"");
				new_str = ft_strjoin(new_str, " ");
			}
			else if (ft_strnstr(str_split[i], "$", ft_strlen(str_split[i])))
			{
				if (ft_strnstr(str_split[i], "\"", 1) || ft_strnstr(str_split[i], "\"", 2))
					case_3 = 3;
				else if (ft_strnstr(str_split[i], "$", ft_strlen(str_split[i])) && (ft_strnstr(str_split[i], "\"", ft_strlen(str_split[i]) - 1) || ft_strnstr(str_split[i], "\'", ft_strlen(str_split[i]) - 2)))
					case_3 = 6;
				var = ft_strchr(str_split[i], '$');
				j = ft_strlen(var);
				if (var[j - 1] == '\"')
				{
					j--;
					var[j] = '\0';
					if (str_split[i][0] == '\"')
						new_str = ft_strjoin(new_str, "\1\"");
					new_str = ft_strjoin(new_str, var);
					new_str = ft_strjoin(new_str, "\"");
					case_3 = 2;
				}
				else if (!(var[j - 1] >= 'A' && var[j - 1] <= 'Z'))
				{
					while((!(var[j - 1] >= 'A' && var[j - 1] <= 'Z')))
						j--;
					var[j] = '\0';
				}
				if (case_3 == 3)
				{
					new_str = ft_strjoin(new_str, "\1\"");
					new_str = ft_strjoin(new_str, var);
					new_str = ft_strjoin(new_str, " ");
					case_3 = 0;
				}
				else if (case_3 != 2)
				{
					new_str = ft_strjoin(new_str, var);
					new_str = ft_strjoin(new_str, " ");
				}
			}
			i++;
		}
	}

	/* -------------------------------------------------------------------------- */
	/*                             //! all other cases                            */
	/* -------------------------------------------------------------------------- */
	while (str_split[i])
	{
		if (ft_strnstr(str_split[i], "\"", ft_strlen(str_split[i])) && ft_strnstr(str_split[i], "\'", ft_strlen(str_split[i])))
		{
			while (str_split[i][j])
			{
				if (str_split[i][j] == '\"' && case_2 != 1)
				{
					if (ft_strnstr(str_split[i], "\'", ft_strlen(str_split[i])))
					case_1 = 1;
					break ;
				}
				else if (str_split[i][j] == '\'')
				{
					if (str_split[i][j + 1] != '"')
					{
						y = j;
						y++;
						while (str_split[i][y] != '"')
							y++;
						var = ft_substr(str_split[i], j + 1, y - j);
						new_str = ft_strjoin(new_str, var);
						y++;
						j = y;
						while (str_split[i][y] != '"')
							y++;
						// y++;
						var = ft_substr(str_split[i], j, y - j);
						new_str = ft_strjoin(new_str, var);
						new_str = ft_strjoin(new_str, "\"");
						done = 1;
						break ;
					}
					start = 1;
					if (start)
					{
						//! you started with a "
					}
					case_2 = 1;
					j++;
					if (str_split[i][j] == '\"' && strlen(str_split[i]) == 2)
					{
						new_str = ft_strjoin(new_str, "\1\"");
						new_str = ft_strjoin(new_str, " ");
						i++;
						while (str_split[i])
						{
							if (ft_strnstr(str_split[i], "$", 1))
							{
								var = ft_strchr(str_split[i], '$');
								// var++;
								if (ft_strnstr(var, "$", 1))
								{
									printf("295\n");
									//! it means you have more than one variable and no spaces
								}
								if (var[ft_strlen(var) - 2] == '\'' || var[ft_strlen(var) - 2] == '\"')
								{
									var[ft_strlen(var) - 2] = '\0';
									case_5 = 1;
								}
								else if (var[ft_strlen(var) - 1] == '\'' || var[ft_strlen(var) - 1] == '\"')
								{
									var[ft_strlen(var) - 1] = '\0';
									case_5 = 1;
								}
								// new_str = ft_strjoin(new_str, "\1\"");
								new_str = ft_strjoin(new_str, var);
								if (case_5 == 1)
									new_str = ft_strjoin(new_str, "\1\"");
								new_str = ft_strjoin(new_str, " ");
							}
							if (ft_strnstr(str_split[i], "\"\'", 2))
								new_str = ft_strjoin(new_str, "\1\"");
							i++;
						}
						i--;
						break ;
					}
					else if ((str_split[i][j] == '\"' && strlen(str_split[i]) > 2))
					{
						while (str_split[i][j] != '$')
							j++;
						var = ft_strchr(str_split[i], '$');
						if (ft_strnstr(var, "$", 1))
						{
							//! it means you have more than one variable and no spaces
						}
						if (var[ft_strlen(var) - 2] == '\'' || var[ft_strlen(var) - 2] == '\"')
						{
							var[ft_strlen(var) - 2] = '\0';
							case_5 = 1;
						}
						else if (var[ft_strlen(var) - 1] == '\'' || var[ft_strlen(var) - 1] == '\"')
						{
							var[ft_strlen(var) - 1] = '\0';
							case_5 = 1;
						}
						new_str = ft_strjoin(new_str, "\1\"");
						new_str = ft_strjoin(new_str, var);
						if (case_5 == 1)
							new_str = ft_strjoin(new_str, "\"");
						i++;
						if (ft_strnstr(str_split[i], "\"", 1) && ft_strnstr(str_split[i], "\'", 2))
						{
							new_str = ft_strjoin(new_str, " ");
							new_str = ft_strjoin(new_str, "\1\"");
						}
						while (str_split[i]) //! hey
						{
							if (ft_strnstr(str_split[i], "$", 1))
							{
								var = ft_strchr(str_split[i], '$');
								// var++;
								if (ft_strnstr(var, "$", 1))
								{
									printf("295\n");
									//! it means you have more than one variable and no spaces
								}
								if (var[ft_strlen(var) - 2] == '\'' || var[ft_strlen(var) - 2] == '\"')
								{
									var[ft_strlen(var) - 2] = '\0';
									case_5 = 1;
								}
								else if (var[ft_strlen(var) - 1] == '\'' || var[ft_strlen(var) - 1] == '\"')
								{
									var[ft_strlen(var) - 1] = '\0';
									case_5 = 1;
								}
								// new_str = ft_strjoin(new_str, "\1\"");
								new_str = ft_strjoin(new_str, " ");
								new_str = ft_strjoin(new_str, var);
								if (case_5 == 1)
									new_str = ft_strjoin(new_str, "\1\"");
								new_str = ft_strjoin(new_str, " ");
							}
							if (ft_strnstr(str_split[i], "\"\'", 2))
								new_str = ft_strjoin(new_str, "\1\"");
							i++;
						}
						i--;
						break ;
					}
				}
				j++;
			}
			j = 0;
			if (case_1 && ft_strnstr(str_split[i], "$", ft_strlen(str_split[i])))
			{
				printf("hi\n");
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
				printf("%s\n", var);
				if (ft_strnstr(var, "\'", ft_strlen(var)))
				{
					new_split = ft_split(var, '\'');
					y = 0;
					while (new_split[y])
					{
						if (ft_strnstr(new_split[y], "$", 1))
						{
							var = new_split[y];
							var++;
						}
						else
							var = new_split[y];
						cmd = getenv(var);
						new_str = ft_strjoin(new_str, cmd);
						new_str = ft_strjoin(new_str, "\'");
						y++;
					}
					break ;
					done = 1;
				}
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
					printf("347\n");
					new_str = ft_strjoin(new_str, cmd);
					new_str = ft_strjoin(new_str, "\' ");
					case_1 = 1;

				}
				else if (case_2 == 1)
				{
					printf("yes yes am here\n");
					//! check which case needed this condition in order to mergre the solutions of case_2
					var = ft_strchr(str_split[i], '$');
					var++;
					cmd = getenv(var);
					if (cmd == NULL)
					{
						printf("i have a problem with the cmd man help!! case_1fsda\n");
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
			else if (case_2 != 1 && done != 1)
			{
				printf("heelo\n£");
				new_str = ft_strjoin(new_str, "\1'");
				new_str = ft_strjoin(new_str, " ");
			}
		}
		else if (ft_strnstr(str_split[i], "\'", ft_strlen(str_split[i])))
		{
			printf("heelo1\n");
			if (ft_strnstr(str_split[i], "\'", 1) && str_split[i][ft_strlen(str_split[i]) - 1] == '\'')
			{
				printf("heelo2\n");
				new_str = not_v(new_str, str_split[i]);
				// if (case_4 != 2) //! didnt find the case yet / maybe there is no need
				// 	case_4 = 1;
				
			}
			else if (ft_strnstr(str_split[i], "$", 2) && (ft_strnstr(str_split[i], "\'", 1) || str_split[i][ft_strlen(str_split[i]) - 1] == '\''))
			{
				printf("heelo3\n");
				new_str = not_v(new_str, str_split[i]);
			}
			else
			{
				printf("heelo4\n");
				i++;
				new_str = ft_strjoin(new_str, "\1'");
				while ((ft_strnstr(str_split[i], "\'", ft_strlen(str_split[i]))) == NULL)
				{
					
					i++;
				}
			}
		}
		else if (ft_strnstr(str_split[i], "$", 1)) //! here it was an else if statment
		{
			printf("543\n");
			if (ft_strnstr(str_split[i], "\"", ft_strlen(str_split[i])) && ft_strnstr(str_split[i], "\'", ft_strlen(str_split[i])))
			{
				printf("546\n");
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
				printf("563\n");
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
				printf("579\n");
				var = ft_substr(str_split[i], 0, ft_strlen(str_split[i]) - 1);
				new_str = ft_strjoin(new_str, var);
				new_str = ft_strjoin(new_str, " ");
			}
			else
			{
				printf("586\n");
				if (case_4 == 1)
				{
					printf("589\n");
					new_str = ft_strjoin(new_str, str_split[i]);
					new_str = ft_strjoin(new_str, " ");
					case_4 = 2;
				}
				else
				{
					printf("596\n");
					var = ft_substr(str_split[i], 1, ft_strlen(str_split[i]));
					if (ft_strnstr(var, "$", ft_strlen(var)))
					{
						printf("600\n");
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
						new_str = simple_v(var, new_str);
				}
			}
		}
		else if (ft_strnstr(str_split[i], "\"", 1) && ft_strnstr(str_split[i], "$", 2))
		{
			printf("616\n");
			var = ft_strchr(str_split[i], '$');
			if (ft_strnstr(var, "$", ft_strlen(var)))
			{
				printf("620");
				str_split[i] = ft_strtrim(str_split[i], "\"");
				new_str = split_dollar(new_str, str_split[i]);
			}
			else
			{
				free(var);
				var = NULL;
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
		}
		else if (ft_strnstr(str_split[i], "\'", 1) && ft_strnstr(str_split[i], "$", 2))
		{
			printf("518\n");
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
			new_str = not_v(new_str, str_split[i]);
		i++;
	}
	return (new_str);
}


/**
 * ?casi gestiti:
 * * $$         	✔ echo $USER$USER
 * * $ $ $ $ $  	✔ echo $USER $USER $USER $USER $USER
 * * "$"        	✔ echo "$USER"
 * * $ "$" $    	✔ echo $USER "$USER" $USER
 * * $ "$ $" $  	✔ echo $USER "$USER $USER" $USER
 * * $ " $ "    	✔ echo " $USER "
 * * $ " $ $ "  	✔ echo " $USER $USER "
 * * '$'        	✔ echo '$USER'
 * * $ '$' $    	✔ echo $USER '$USER' $USER
 * * $ '$ $' $  	✔ echo $USER '$USER $USER' $USER
 * * ' $ '      	✔ //! error
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
 * * '"$"'
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
 * * $ ' "$ $ " '
 * * $ ' " $$ " '
 * * $ $ "$$"
 * * '$"$"'
 * * "$'$'"
 * 
 * TODO: da gestire
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