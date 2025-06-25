#include "../../includes/minishell.h"
#include <glob.h>

static int has_wildcards(const char *s)
{
    while (*s)
    {
        if (*s == '*' || *s == '?')
            return (1);
        s++;
    }
    return (0);
}

static int add_glob_results(Command *cmd, glob_t *gl)
{
    char    **new_args;
    size_t  new_count = (size_t)cmd->arg_count + gl->gl_pathc - 1;
    size_t  i;

    new_args = malloc(sizeof(char *) * (new_count));
    if (!new_args)
        return (0);
    for (i = 0; i < (size_t)(cmd->arg_count - 1); i++)
        new_args[i] = cmd->args[i];
    for (size_t j = 0; j < gl->gl_pathc; j++)
        new_args[i++] = ft_strdup(gl->gl_pathv[j]);
    free(cmd->args[cmd->arg_count - 1]);
    free(cmd->args);
    cmd->args = new_args;
    cmd->arg_count = new_count;
    return (1);
}

static void expand_command(Command *cmd)
{
    size_t i = 0;
    while (i < (size_t)cmd->arg_count)
    {
        if (has_wildcards(cmd->args[i]))
        {
            glob_t gl;
            if (glob(cmd->args[i], 0, NULL, &gl) == 0 && gl.gl_pathc > 0)
            {
                if (add_glob_results(cmd, &gl))
                {
                    i += gl.gl_pathc;
                    globfree(&gl);
                    continue;
                }
            }
            globfree(&gl);
        }
        i++;
    }
}

void    expand_wildcards(Command *commands, int cmd_count)
{
    int i = 0;
    while (i < cmd_count)
    {
        expand_command(&commands[i]);
        i++;
    }
}


