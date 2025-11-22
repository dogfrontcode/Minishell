#!/bin/bash

HEADER="/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_group.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidos-sa <tidos-sa@student.42.fr>          +#+  +:+      +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 19:26:48 by tidos-sa          #+#    #+#             */
/*   Updated: 2025/11/21 19:26:49 by tidos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */"

find . -type f \( -name "*.c" -o -name "*.h" \) | while read -r file; do
    tmpfile=$(mktemp)

    # escreve o cabeçalho
    printf "%s\n\n" "$HEADER" > "$tmpfile"

    # concatena o arquivo original
    cat "$file" >> "$tmpfile"

    # substitui o arquivo
    mv "$tmpfile" "$file"

    echo "Cabeçalho adicionado em: $file"
done

