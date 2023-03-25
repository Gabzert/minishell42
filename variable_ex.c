/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_ex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:55:54 by naal-jen          #+#    #+#             */
/*   Updated: 2023/03/25 20:48:28 by naal-jen         ###   ########.fr       */
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
	int		case_qdq;
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
	case_qdq = 0;
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
		printf("\033[0;32m");
		printf("143\n");
		printf("\033[0m");
		while (str_split[i])
		{
			if (ft_strnstr(str_split[i], "\'", ft_strlen(str_split[i])) && (!(ft_strnstr(str_split[i], "$", ft_strlen(str_split[i])))))
			{
				printf("\033[0;32m");
				printf("150\n");
				printf("-------\n");
				printf("\033[0m");
				new_str = ft_strjoin(new_str, "\1'");
				new_str = ft_strjoin(new_str, " ");
			}
			else if (ft_strnstr(str_split[i], "$", ft_strlen(str_split[i])))
			{
				if (ft_strnstr(str_split[i], "\'", 1) || ft_strnstr(str_split[i], "\'", 2))
					case_3 = 3;
				else if (ft_strnstr(str_split[i], "$", ft_strlen(str_split[i])) && (ft_strnstr(str_split[i], "\'", ft_strlen(str_split[i]) - 1) || ft_strnstr(str_split[i], "\'", ft_strlen(str_split[i]) - 2)))
					case_3 = 6;
				var = ft_strchr(str_split[i], '$');
				var++;
				j = ft_strlen(var);
				if (var[j - 1] == '\'')
				{
					printf("\033[0;32m");
					printf("168\n");
					printf("----------\n");
					printf("\033[0m");
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
					printf("\033[0;32m");
					printf("183\n");
					printf("----------\n");
					printf("\033[0m");
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
					printf("\033[0;32m");
					printf("200\n");
					printf("-------\n");
					printf("\033[0m");
					new_str = begin_with_quote(new_str, var);
					case_3 = 0;
				}
				else if (case_3 == 6)
				{
					printf("\033[0;32m");
					printf("209\n");
					printf("-------\n");
					printf("\033[0m");
					cmd = getenv(var);
					if (!cmd)
					{
						printf("blabalbla\n");
					}
					else
					{
						new_str = ft_strjoin(new_str, cmd);
						new_str = ft_strjoin(new_str, "' ");
						case_3 = 0;
					}

				}
			}
			i++;
		}
	}
	else if (case_1 == 1)
	{
		while (str_split[i] && (!((ft_strnstr(str_split[i], "\"", ft_strlen(str_split[i]))) || (ft_strnstr(str_split[i], "\'", ft_strlen(str_split[i]))))))
		{
			printf("hihi good good\n");
			if (ft_strnstr(str_split[i], "$", 1))
			{
				var = ft_strchr(str_split[i], '$');
				var++;
				cmd = getenv(var);
				if (!cmd)
				{
					printf("272");
				}
				else
				{
					new_str = ft_strjoin(new_str, cmd);
					new_str = ft_strjoin(new_str, " ");
				}
			}
			i++;
		}
		
		while (str_split[i])
		{
			if (ft_strnstr(str_split[i], "\"", ft_strlen(str_split[i])) && (!(ft_strnstr(str_split[i], "$", ft_strlen(str_split[i])))))
			{
				new_str = ft_strjoin(new_str, "\1\"");
				new_str = ft_strjoin(new_str, " ");
			}
			else if (ft_strnstr(str_split[i], "$", ft_strlen(str_split[i])))
			{
				printf("i go into here\n");
				if (ft_strnstr(str_split[i], "\"", 1) || ft_strnstr(str_split[i], "\"", 2))
					case_3 = 3;
				else if (ft_strnstr(str_split[i], "$", ft_strlen(str_split[i])) && (ft_strnstr(str_split[i], "\"", ft_strlen(str_split[i]) - 1) || ft_strnstr(str_split[i], "\'", ft_strlen(str_split[i]) - 2)))
					case_3 = 6;
				var = ft_strchr(str_split[i], '$');
				j = ft_strlen(var);
				if (var[j - 1] == '\"')
				{
					printf("i dont go inside herer good good\n");
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
				{ //? ok
					new_str = ft_strjoin(new_str, "\1\"");
					new_str = ft_strjoin(new_str, var);
					new_str = ft_strjoin(new_str, " ");
					case_3 = 0;
				}
				else if (case_3 != 2)
				{
					printf(" i wen theregood good\n");
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
				if (str_split[i][j] == '$' && str_split[i][ft_strlen(str_split[i]) - 2] == '\'' && str_split[i][ft_strlen(str_split[i]) - 1] == '\"')
				{
					new_str = end_with_quote(new_str, str_split[i]);
					i++;
					break ;
				}
				else if (str_split[i][j] == '$' && str_split[i][ft_strlen(str_split[i]) - 2] == '\"' && str_split[i][ft_strlen(str_split[i]) - 1] == '\'')
				{
					printf("youlu\n");
					new_str = end_with_dquote(new_str, str_split[i]);
					i++;
					break ;
				}
				if (start == 0 && ft_strlen(str_split[i]) == 2 && str_split[i][j] == '\"' && str_split[i][j + 1] == '\'')
				{
					printf("first i got here\n");
					new_str = ft_strjoin(new_str, "\1\' ");
					start = 1;
				}
				else if (start == 1 && ft_strlen(str_split[i]) == 2 && str_split[i][j] == '\'' && str_split[i][j + 1] == '\"')
				{
					printf("did i go here\n");
					new_str = ft_strjoin(new_str, "\1\' ");
					start = 0;
				}
				else if (start == 0 && ft_strlen(str_split[i]) == 2 && str_split[i][j] == '\'' && str_split[i][j + 1] == '\"')
				{
					printf("i started here\n");
					new_str = ft_strjoin(new_str, "\1\" ");
					start = 1;
					case_qdq = 1;
				}
				else if (start == 1 && ft_strlen(str_split[i]) == 2 && str_split[i][j] == '\"' && str_split[i][j + 1] == '\'')
				{
					printf("and then ended here\n");
					new_str = ft_strjoin(new_str, "\1\" ");
					start = 0;
					case_qdq = 0;
				}
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
						printf("\033[0;32m");
						printf("371\n");
						printf("-------\n");
						printf("\033[0m");
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
					// start = 1;
					// if (start)
					// {
					// 	//! you started with a "
					// }
					case_2 = 1;
					j++;
					if (str_split[i][j] == '\"' && str_split[i][j - 1] != '\'' && strlen(str_split[i]) == 2)
					{ //! maybe cancelable
						printf("\033[0;31m");
						printf("5\n");
						printf("\033[0m");
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
								{ //! maybe cancelable
									printf("\033[0;31m");
									printf("4\n");
									printf("\033[0m");
									//! it means you have more than one variable and no spaces
								}
								if (var[ft_strlen(var) - 2] == '\'' || var[ft_strlen(var) - 2] == '\"')
								{ //! maybe cancelable
									printf("\033[0;31m");
									printf("3\n");
									printf("\033[0m");
									var[ft_strlen(var) - 2] = '\0';
									case_5 = 1;
								}
								else if (var[ft_strlen(var) - 1] == '\'' || var[ft_strlen(var) - 1] == '\"')
								{ //! maybe cancelable
									printf("\033[0;31m");
									printf("2\n");
									printf("\033[0m");
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
							{ //! maybe cancelable
								printf("\033[0;31m");
								printf("1\n");
								printf("\033[0m");
								new_str = ft_strjoin(new_str, "\1\"");
							}
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
						printf("\033[0;32m");
						printf("457\n");
						printf("-------\n");
						printf("\033[0m");
						new_str = ft_strjoin(new_str, "\1\"");
						new_str = ft_strjoin(new_str, var);
						if (str_split[i] && case_5 == 1)
						{
							printf("\033[0;32m");
							printf("465\n");
							printf("-------\n");
							printf("\033[0m");
							new_str = ft_strjoin(new_str, "\"");
						}
						i++;
						if (str_split[i] && ft_strnstr(str_split[i], "\"", 1) && ft_strnstr(str_split[i], "\'", 2))
						{
							printf("\033[0;32m");
							printf("477\n");
							printf("-------\n");
							printf("\033[0m");
							new_str = ft_strjoin(new_str, " ");
							new_str = ft_strjoin(new_str, "\1\"");
						}
						if (str_split[i])
						{
							printf("\033[0;32m");
							printf("486\n");
							printf("\033[0m");
							while (str_split[i]) //! hey
							{
								if (ft_strnstr(str_split[i], "$", 1))
								{
									printf("\033[0;32m");
									printf("493\n");
									printf("-------------\n");
									printf("\033[0m");
									var = ft_strchr(str_split[i], '$');
									// var++;
									if (ft_strnstr(var, "$", 1))
									{
										//! it means you have more than one variable and no spaces i think i can cancel it
									}
									if (var[ft_strlen(var) - 2] == '\'' || var[ft_strlen(var) - 2] == '\"')
									{
										//? ok
										var[ft_strlen(var) - 2] = '\0';
										case_5 = 1;
									}
									else if (var[ft_strlen(var) - 1] == '\'' || var[ft_strlen(var) - 1] == '\"')
									{ //! maybe cancelable
										printf("\033[0;31m");
										printf("i\n");
										printf("\033[0m");
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
								 //! bcs there is the case_qdq it might not be needed
								// if (case_qdq == 0 && ft_strnstr(str_split[i], "\"\'", 2))
								// {
								// 	printf("404\n");
								// 	new_str = ft_strjoin(new_str, "\1\"");
								// }
								i++;
							}
							i--;
							break ;
						}
						if (str_split[i] == NULL)
							return (new_str);
					}
				}
				j++;
			}
			j = 0;
			if (str_split[i] && case_1 && ft_strnstr(str_split[i], "$", ft_strlen(str_split[i])))
			{ //! START -------------------------------
				printf("\033[0;32m");
				printf("509\n");
				printf("\033[0m");
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
				if (ft_strnstr(var, "\'", ft_strlen(var)))
				{ //? okok
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
				if (cmd == NULL)
				{
					printf("i have a problem with the cmd man help!! case_1\n");
					new_str = ft_strjoin(new_str, " ");
				}
				else if (case_1 == 1)
				{
					printf("\033[0;32m");
					printf("565\n");
					printf("-------------\n");
					printf("\033[0m");
					new_str = ft_strjoin(new_str, "\1'");
					new_str = ft_strjoin(new_str, cmd);
					new_str = ft_strjoin(new_str, " ");
					start = 1;
					help_me_man = 1;
				}
				else if (case_1 == 2 && help_me_man == 1)
				{ //! maybe cancelable
					printf("\033[0;31m");
					printf("g\n");
					printf("\033[0m");
					new_str = ft_strjoin(new_str, cmd);
					new_str = ft_strjoin(new_str, "\' ");
					case_1 = 1;

				}
				else if (case_2 == 1)
				{ //! maybe cancelable
					printf("\033[0;31m");
					printf("f\n");
					printf("\033[0m");
					//! you need this condition when you need a ' at the end of your join
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
					printf("\033[0;32m");
					printf("584\n");
					printf("--------\n");
					printf("\033[0m");
					new_str = begin_and_end_with_quote(new_str, cmd);
				}
				j = 0;
			} //! END --------------------------------
			else if (str_split[i] && case_2 != 1 && done != 1)
			{ //! maybe cancelable
				printf("\033[0;31m");
				printf("f\n");
				printf("\033[0m");
				new_str = ft_strjoin(new_str, "\1'");
				new_str = ft_strjoin(new_str, " ");
			}
		}
		else if (str_split[i] && ft_strnstr(str_split[i], "\'", ft_strlen(str_split[i])))
		{
			printf("\033[0;32m");
			printf("593\n");
			printf("\033[0m");
			if (ft_strnstr(str_split[i], "\'", 1) && str_split[i][ft_strlen(str_split[i]) - 1] == '\'')
			{
				printf("\033[0;32m");
				printf("598\n");
				printf("-------\n");
				printf("\033[0m");
				new_str = not_v(new_str, str_split[i]);
				
				if (str_split[i][0] == '\'' && ft_strnstr(str_split[i], "$", ft_strlen(str_split[i])) && str_split[i][ft_strlen(str_split[i]) - 1] == '\'')
					case_4 = 0;
				else if (case_4 == 0)
					case_4 = 1;
				else if (case_4 == 1)
					case_4 = 0;
				
			}
			else if (ft_strnstr(str_split[i], "$", 2) && (ft_strnstr(str_split[i], "\'", 1) || str_split[i][ft_strlen(str_split[i]) - 1] == '\''))
			{
				printf("\033[0;32m");
				printf("614\n");
				printf("-------\n");
				printf("\033[0m");
				new_str = not_v(new_str, str_split[i]);
				// if (case_4 == 0)
				// 	case_4 = 1;
				// else if (case_4 == 1)
				// 	case_4 = 0;
			}
			else
			{ //! maybe cancelable
				printf("\033[0;31m");
				printf("7\n");
				printf("\033[0m");
				i++;
				new_str = ft_strjoin(new_str, "\1'");
				while ((ft_strnstr(str_split[i], "\'", ft_strlen(str_split[i]))) == NULL)
				{
					
					i++;
				}
			}
		}
		else if (str_split[i] && ft_strnstr(str_split[i], "$", 1)) //! here it was an else if statment
		{
			printf("\033[0;32m");
			printf("630\n");
			printf("\033[0m");
			if (ft_strnstr(str_split[i], "\"", ft_strlen(str_split[i])) && ft_strnstr(str_split[i], "\'", ft_strlen(str_split[i])))
			{ //! maybe cancelable
				printf("\033[0;31m");
				printf("d\n");
				printf("\033[0m");
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
				printf("\033[0;32m");
				printf("652\n");
				printf("\033[0m");
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
			{ //! maybe cancelable
				printf("\033[0;31m");
				printf("c\n");
				printf("\033[0m");
				var = ft_substr(str_split[i], 0, ft_strlen(str_split[i]) - 1);
				new_str = ft_strjoin(new_str, var);
				new_str = ft_strjoin(new_str, " ");
			}
			else
			{
				printf("\033[0;32m");
				printf("569\n");
				printf("--------\n");
				printf("\033[0m");
				var = ft_substr(str_split[i], 1, ft_strlen(str_split[i]));
				if (case_4 == 1 || case_qdq == 1)
					new_str = not_v(new_str, str_split[i]);
				else
					new_str = simple_v(var, new_str);
			}
		
		}
		else if (str_split[i] && ft_strnstr(str_split[i], "\"", 1) && ft_strnstr(str_split[i], "$", 2))
		{
			printf("\033[0;32m");
			printf(">688\n");
			printf("\033[0m");
			var = ft_strchr(str_split[i], '$');
			var++; //! modified
			if (ft_strnstr(var, "$", ft_strlen(var)))
			{
				printf("\033[0;32m");
				printf("694\n");
				printf("------\n");
				printf("\033[0m");
				str_split[i] = ft_strtrim(str_split[i], "\"");
				new_str = split_dollar(new_str, str_split[i]);
			}
			else
			{
				printf("\033[0;32m");
				printf("704\n");
				printf("------\n");
				printf("\033[0m");
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
		}
		else if (str_split[i] && ft_strnstr(str_split[i], "\'", 1) && ft_strnstr(str_split[i], "$", 2))
		{ //! all red may be cancelable
			printf("\033[0;31m");
			printf("730\n");
			printf("\033[0m");
			if (str_split[i][ft_strlen(str_split[i]) - 1] == '\'')
			{
				printf("\033[0;31m");
				printf("i never go here a\n");
				printf("\033[0m");
				var = ft_substr(str_split[i], 1, ft_strlen(str_split[i]) - 2);
				new_str = ft_strjoin(new_str, var);
				new_str = ft_strjoin(new_str, " ");
			}
			else
			{
				printf("\033[0;31m");
				printf("i never go here b\n");
				printf("\033[0m");
				var = ft_substr(str_split[i], 1, ft_strlen(str_split[i]) - 1);
				new_str = ft_strjoin(new_str, var);
				new_str = ft_strjoin(new_str, " ");
			}
		}
		else if (str_split[i])
			new_str = not_v(new_str, str_split[i]);
		if (str_split[i] == NULL)
			break ;
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
 * * $ "$ $" $  	✔ echo $USER "$USER $USER" $USER //
 * * $ " $ "    	✔ echo " $USER "
 * * $ " $ $ "  	✔ echo " $USER $USER "
 * * '$'        	✔ echo '$USER'
 * * $ '$' $    	✔ echo $USER '$USER' $USER
 * * $ '$ $' $  	✔ echo $USER '$USER $USER' $USER
 * * ' $ '      	✔ echo ' $USER '
 * * $ ' $ '    	✔ echo $USER ' $USER '
 * * $ ' $ ' $  	✔ echo $USER ' $USER ' $USER
 * * $ ' $ $ '  	✔ echo $USER ' $USER $USER '
 * * "'$'"      	✔ echo "'$USER'"
 * * $ "'$'"    	✔ echo $USER "'$USER'"
 * * $ "'$ $'" $	✔ echo $USER "'$USER $USER'" $USER
 * * $ "' $ '"  	✔ echo $USER "' $USER '"
 * * $ "' $'"   	✔ echo $USER "' $USER'"
 * * $ "'$ '"   	✔ echo $USER "'$USER '"
 * * $ "' $ $ '" 	✔ echo "' $USER $USER '"
 * * $ "' $ $'"  	✔ echo "' $USER $USER'"
 * * $ "'$ $ '"  	✔ echo "'$USER $USER '"
 * * $ " ' $ ' " 	✔ echo $USER " ' $USER ' "
 * * $ " ' $' "  	✔ echo $USER " ' $USER' "
 * * $ " '$ ' "  	✔ echo $USER " '$USER ' "
 * * $ " ' $  $ ' "	✔ echo $USER " ' $USER $USER ' "
 * * $ " ' $  $' "	✔ echo $USER " ' $USER $USER' "
 * * $ " '$  $ ' "	✔ echo $USER " '$USER $USER ' "
 * * " $ "        	✔ echo " $USER "
 * * '"$"'        	✔ echo '"$USER"'
 * * $ '"$"'      	✔ echo $USER '"$USER"'
 * * $ '" $ "'    	✔ echo $USER '" $USER "'
 * * $ '"$ "'     	✔ echo $USER '"$USER "'
 * * $ '" $"'     	✔ echo $USER '" $USER"'
 * * $ '" $ $ "'  	✔ echo $USER '" $USER $USER "'
 * * $ '" $ $"'   	✔ echo $USER '" $USER $USER"'
 * * $ '"$ $"'    	✔ echo $USER '"$USER $USER"'
 * * $ '" $$ "'   	✔ echo $USER '" $USER$USER "'
 * * $ ' "$" '    	✔ echo $USER ' "$USER" '
 * * $ ' "$ " '   	✔ echo $USER ' "$USER " '
 * * $ ' " $" '   	✔ echo $USER ' " $USER" '
 * * $ ' " $ $ " '	✔ echo $USER ' " $USER $USER " '
 * * $ ' " $ $" ' 	✔ echo $USER ' " $USER $USER" '
 * * $ ' "$ $" '  	✔ echo $USER ' "$USER $USER" '
 * * $ ' "$ $ " ' 	✔ echo $USER ' "$USER $USER " '
 * * $ ' " $$ " ' 	✔ echo $USER ' " $USER$USER " '
 * * $ $ "$$"     	✔ echo $USER ' "$USER$USER" '
 * * '$"$"'       	✔ echo '$USER"$USER"'
 * * "$'$'"       	✔ echo "$USER'$USER'"
 * 
 * TODO: da gestire
 * 
 * !casi che non devono essere gestiti
 * * $ "' $ $ "' -> quote
 * * $ "' $ $ "" -> dquote
 * * $ ' $ " $ " -> quote
 * * $ ' $ $ "   -> quote
*/