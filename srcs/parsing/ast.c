/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:56:37 by avalsang          #+#    #+#             */
/*   Updated: 2025/04/10 17:44:07 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_ast	*ast_new(t_token *token);
int		count_argc(t_token *node);
char	**parse_cmd_args(t_token *node, int argc);
t_ast	*parse_cmd(t_token **node);
t_ast	*parse_logical(t_token **token);
t_ast	*parse_pipe(t_token **token);
t_ast	*parse_redir(t_token **token);

t_ast	*ast_new(t_token *token)
{
	t_ast *new;

	new = (t_ast *)malloc(sizeof(t_ast));
	new->left = NULL;
	new->right = NULL;
	new->literal = NULL;
	new->parent = NULL;
	new->token = token;
	new->type = token->type;
	return (new);
}

int	count_argc(t_token *node)
{
	t_token *temp;
	int		count;

	count = 0; // start counting at 1?
	temp = node;
	while (temp && temp->type == COMMAND)
	{
		temp = temp->next;
		count++;
	}
	return (count);
}

char	**parse_cmd_args(t_token *node, int argc)
{
	t_token	*current;
	char	**result;
	int		i;

	result = (char **) malloc(sizeof(char *) * (argc + 1));
	i = 0;
	current = node;
	while (i < argc)
	{
		result[i++] = ft_strdup(current->literal);
		current = current->next;
	}
	return (result);
}

void	print_ast(t_ast *ast)
{
	if (ast == NULL)
		return ;
	printf("%s\n", ast->token->literal);
	if (ast != NULL)
		printf("	");
	print_ast(ast->left);
	print_ast(ast->right);
}

t_ast	*parse_cmd(t_token **node)
{
	t_ast	*cmd;
	int		argc;
	
	if (node == NULL || *node == NULL)
		return (NULL);

	cmd = ast_new(*node);
	argc = count_argc(*node);
	
	cmd->literal = parse_cmd_args(*node, argc);
	if (cmd->literal == NULL)
		return (NULL); // free cmd now, or in a catch-all function later?
	return (cmd);
}
// cmd1 && cmd2 | cmd3
t_ast	*parse_logical(t_token **token)
{
	t_token	*start;
	t_token	*cut_off;
	t_ast	*logical;

	start = *token;
	while ((*token) && (*token)->next)
	{
		cut_off = (*token)->next;
		if ((*token)->type == LOGICAL_AND || (*token)->type == LOGICAL_OR)
		{
			logical = ast_new(*token);			
			(*token)->next = NULL;
			logical->left = parse_pipe(&start);
			logical->right = parse_logical(&cut_off);
			return (logical);
		}
		(*token) = cut_off;
	}
	return (parse_pipe(&start));
}

t_ast	*parse_pipe(t_token **token)
{
	t_token	*start;
	t_ast	*pipe;

	start = *token;
	while ((*token) && (*token)->next)
	{
		if ((*token)->type == PIPE)
		{
			pipe = ast_new(*token);
			pipe->left = parse_redir(&start);
			pipe->right = parse_pipe(&((*token)->next));
			return (pipe);
		}
		(*token) = (*token)->next;
	}
	return (parse_redir(&start));
}

t_ast	*parse_path(t_token **token)
{
	t_ast	*path;

	path = ast_new(*token);
	// path->literal = ft_strdup((*token)->literal);
	path->type = PATH;
	return (path);
}

t_ast	*parse_redir(t_token **token)
{
	t_token	*start;
	t_ast	*redir;

	start = *token;
	while ((*token) && (*token)->next)
	{
		if ((*token)->type == REDIRECT_IN || (*token)->type == REDIRECT_HEREDOC)
		{
			redir = ast_new((*token));
			redir->left = parse_cmd(&(*token)->next->next);
			redir->right = parse_path(&((*token)->next));
			return (redir);
		}
		else if ((*token)->type == REDIRECT_OUT || (*token)->type == REDIRECT_APPEND)
		{
			redir = ast_new((*token));
			redir->left = parse_cmd(&(*token)->prev);
			redir->right = parse_path(&((*token)->next));
			return (redir);
		}
		(*token) = (*token)->next;
	}
	return (parse_cmd(&start));
}

t_ast	*parse_tokens(t_token **head)
{
	t_ast	*ast_head;
	t_token	*start;

	if (head == NULL)
	{
		printf("error, no tokens\n");
		return (NULL);
	}
	start = *head;
	ast_head = parse_logical(&start);
	return (ast_head);
}

// leaving off here, next steps: add code for logical, pipes, and redir, in that order
// https://www.chidiwilliams.com/posts/on-recursive-descent-and-pratt-parsing
// use recursive descent, find the first logical node, then look for more. If you don't find one,
// start looking for pipes, and so on, like this:
// ast->left = parse_redir(), ast->right = parse_logical()
// or perhaps the other way around
// The last step is command, which I think is done