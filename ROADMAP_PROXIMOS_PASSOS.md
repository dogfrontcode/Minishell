# 🗺️ Roadmap - Próximos Passos do Minishell

## 📊 **Status Atual (O que JÁ temos):**
- ✅ **Lexer Completo** (100%)
- ✅ **Parser Estruturado** (100%) 
- ✅ **Pipelines Funcionando** (100%)
- ✅ **Sinais Implementados** (100%)
- ✅ **Built-ins Básicos** (echo, pwd, env, exit)
- ✅ **Validação Sintática** (90%)
- ✅ **Gestão de Memória** (100%)

---

## 🎯 **FASE 1 - ALTA PRIORIDADE (Essencial para 42)**

### **1.1 Redirecionamentos** ⏰ *Estimativa: 2-3 horas*
```bash
# Implementar:
echo "hello" > file.txt     # Output redirect
cat < file.txt              # Input redirect  
echo "append" >> file.txt   # Append redirect
cat << EOF                  # Heredoc
```

**Arquivos para criar:**
- `src/executor/redirections.c`
- Atualizar `src/executor/pipeline.c`

### **1.2 Built-ins Obrigatórios** ⏰ *Estimativa: 2-3 horas*
```bash
# Implementar:
cd /path/to/directory       # Change directory
export VAR=value            # Set environment variable
unset VAR                   # Remove environment variable
```

**Arquivos para criar:**
- `src/builtins/builtin_cd.c`
- `src/builtins/builtin_export.c`
- `src/builtins/builtin_unset.c`

### **1.3 Expansão de Variáveis** ⏰ *Estimativa: 3-4 horas*
```bash
# Implementar:
echo $HOME                  # Environment variables
echo $?                     # Exit status
echo $USER                  # User variables
```

**Arquivos para criar:**
- `src/parser/expand.c`
- Atualizar `src/parser/tokenizer.c`

---

## 🚀 **FASE 2 - MÉDIA PRIORIDADE (Melhorias)**

### **2.1 PATH Lookup para Comandos Externos** ⏰ *Estimativa: 1-2 horas*
```bash
# Ao invés de procurar só em /bin:
ls                          # Encontrar em /bin/ls
cat                         # Encontrar em /bin/cat
grep                        # Encontrar em /usr/bin/grep
```

**Arquivos para modificar:**
- `src/executor/pipeline.c`

### **2.2 Exit Status Management** ⏰ *Estimativa: 1 hora*
```bash
# Implementar:
echo $?                     # Mostrar exit status do último comando
false; echo $?              # Deve mostrar 1
true; echo $?               # Deve mostrar 0
```

**Arquivos para modificar:**
- `src/main.c`
- `src/executor/pipeline.c`

### **2.3 Melhoria na Validação Sintática** ⏰ *Estimativa: 1 hora*
```bash
# Detectar mais erros:
echo "unclosed quotes       # Aspas não fechadas
echo $(command)             # Command substitution (não suportado)
```

---

## 🔧 **FASE 3 - BAIXA PRIORIDADE (Features Avançadas)**

### **3.1 Wildcards (Bonus)** ⏰ *Estimativa: 4-5 horas*
```bash
# Implementar:
ls *.c                      # Expand wildcards
echo file?.txt              # Pattern matching
```

### **3.2 Command History Avançado** ⏰ *Estimativa: 1-2 horas*
```bash
# Implementar:
history                     # Mostrar histórico
!!                          # Repetir último comando
```

### **3.3 Job Control (Muito Avançado)** ⏰ *Estimativa: 6+ horas*
```bash
# Implementar:
command &                   # Background jobs
fg                          # Foreground job
bg                          # Background job
jobs                        # List jobs
```

---

## 📅 **CRONOGRAMA SUGERIDO**

### **Semana 1 - Redirecionamentos**
- [ ] Dia 1: Implementar `>` e `<`
- [ ] Dia 2: Implementar `>>` e `<<` (heredoc)
- [ ] Dia 3: Testar e debugar redirecionamentos

### **Semana 2 - Built-ins**
- [ ] Dia 1: Implementar `cd`
- [ ] Dia 2: Implementar `export` e `unset`
- [ ] Dia 3: Testar built-ins

### **Semana 3 - Expansão de Variáveis**
- [ ] Dia 1: Implementar `$VAR`
- [ ] Dia 2: Implementar `$?`
- [ ] Dia 3: Testar expansão

### **Semana 4 - Polimento**
- [ ] PATH lookup
- [ ] Exit status
- [ ] Testes finais

---

## 🎯 **PRÓXIMO PASSO RECOMENDADO**

### **COMEÇAR COM: Redirecionamentos Simples**

**Por quê?**
1. ✅ **Mais impacto visual** - usuário vê resultados imediatos
2. ✅ **Base para outros features** - heredoc usa redirecionamentos
3. ✅ **Relativamente simples** - usar file descriptors
4. ✅ **Essencial para 42** - todos os testes vão usar

**Implementação sugerida:**
```c
// Exemplo de estrutura:
int setup_redirections(Command *cmd)
{
    int i = 0;
    while (i < cmd->redir_count)
    {
        if (cmd->redirs[i].type == OUT)
        {
            int fd = open(cmd->redirs[i].filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        i++;
    }
    return (0);
}
```

---

## 📊 **Estimativa de Completude**

| Após Fase 1 | Após Fase 2 | Após Fase 3 |
|--------------|-------------|-------------|
| **90%** ✅ | **95%** ✅ | **100%** 🎉 |

---

## 🚨 **DICAS IMPORTANTES**

### **1. Ordem de Implementação:**
- ❌ NÃO implemente tudo de uma vez
- ✅ Uma feature por vez, teste, depois próxima

### **2. Testes Frequentes:**
- ✅ Teste cada feature isoladamente
- ✅ Compare com bash real: `bash -c "comando"`

### **3. Git Commits:**
- ✅ Commit após cada feature funcional
- ✅ Mensagens descritivas: "feat: implement output redirection"

---

**🎯 RESUMO: Comece com redirecionamentos simples (>, <) - maior impacto em menos tempo!** 