/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 21:13:23 by samajat           #+#    #+#             */
/*   Updated: 2022/05/23 22:50:28 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void     close_fd (t_cmd *cmd,int    close_all)
{
    t_list *temp;

    if (!close_all)
    {
        if (cmd->input.fd != STDIN_FILENO)
            close (cmd->input.fd);
        if (cmd->output.fd != STDOUT_FILENO)
            close (cmd->output.fd);
    }
    else
    {
        temp = data.fds;
        while (temp)
        {
            if (*((int *)temp->content) > 2)
                close(*((int *)temp->content));
            temp =temp->next;
        }
    }
}

void    exec_cmd_in_child_process(t_cmd *cmd, int cmd_type)
{
    // (*data.status.exit_code) = 0;
    if (cmd->input.fd != STDIN_FILENO)
        dup2 (cmd->input.fd, STDIN_FILENO);
    if (cmd->output.fd != STDOUT_FILENO)
        dup2 (cmd->output.fd, STDOUT_FILENO);
    close_fd(cmd, 1);
    if (!cmd_type) 
        execve (cmd->f_cmd[0], cmd->f_cmd, data.env);
    else
        exec_built_cmd(cmd, cmd_type);
    ((*data.status.exit_code)) = 1;
    exit(1);
}

void    exec_cmd (t_cmd *cmd)
{
    int         id;
    int         cmd_type;

    cmd_type = is_built_cmd(cmd);
    id = fork();
    if (id < 0)
        return ;
    //mind the exit!!!!!!!!!
    if (id == 0 && cmd_type <3)
        exec_cmd_in_child_process(cmd, cmd_type);
    if (!id)
        exit(1);
    if (cmd_type >=3 && !data.input_piped)
        exec_built_cmd(cmd, cmd_type);
    close_fd(cmd, 0);
}

// void    exec_cmd (t_cmd *cmd)
// {
//     int         id;

//     id = fork();
//     if (id < 0)
//         return ;
//     //mind the exit!!!!!!!!!
//     if (id == 0)
//     {
//         ((*data.status.exit_code)) = 0;
//         if (cmd->input.fd != STDIN_FILENO)
//             dup2 (cmd->input.fd, STDIN_FILENO);
//         if (cmd->output.fd != STDOUT_FILENO)
//             dup2 (cmd->output.fd, STDOUT_FILENO);
//         close_fd(cmd, 1);
//         execve (cmd->f_cmd[0], cmd->f_cmd, data.env);
//         ((*data.status.exit_code)) = 1;
//         exit(1);
//     }
//     close_fd(cmd, 0);
// }
// // 