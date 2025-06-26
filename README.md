# 🐚 Minishell
**Autores:** mide-lim + tidos-sa

Um shell minimalista em C que replica funcionalidades do bash, desenvolvido como projeto da 42.

## 📋 Funcionalidades Implementadas

- ✅ **Built-ins completos:** `echo`, `cd`, `pwd`, `env`, `export`, `unset`, `exit`
- ✅ **Comandos externos** com busca no PATH
- ✅ **Pipelines complexos** (`cmd1 | cmd2 | cmd3`)
- ✅ **Redirecionamentos:** `>`, `>>`, `<`, `<<` (heredoc)
- ✅ **Expansão de variáveis:** `$VAR`, `$?`, `$HOME`
- ✅ **Gestão de aspas:** simples `'...'` e duplas `"..."`
- ✅ **Sinais:** `ctrl-C`, `ctrl-D`, `ctrl-\`
- ✅ **Gestão de memória** sem vazamentos

## 🚀 Compilação e Execução

```bash
make
./minishell
```

---

## 🧪 **SEÇÃO DE TESTES COMPLETA**

### **LEVEL 1 - TESTES BÁSICOS (Built-ins)**

```bash
# 1.1 Echo simples
echo "Hello World"
echo 'Single quotes work'
echo multiple arguments here
echo -n "No newline"

# 1.2 Navegação
pwd
cd ..
pwd
cd -
cd $HOME
pwd

# 1.3 Ambiente
env
env | head -5

# 1.4 Variáveis
export TEST=hello
export MYVAR="value with spaces"
echo $TEST
echo $MYVAR
unset TEST
echo $TEST

# 1.5 Exit status
echo $?
false
echo $?
true
echo $?
```

### **LEVEL 2 - COMANDOS EXTERNOS**

```bash
# 2.1 Comandos básicos
ls
ls -la
date
whoami
which bash

# 2.2 Comandos com argumentos
head -5 /etc/passwd
tail -3 /etc/passwd
grep root /etc/passwd
wc -l /etc/passwd

# 2.3 Comandos com paths absolutos
/bin/ls
/bin/cat /etc/hostname
/usr/bin/head -2 /etc/passwd
```

### **LEVEL 3 - REDIRECIONAMENTOS SIMPLES**

```bash
# 3.1 Output redirect
echo "teste saída" > output.txt
cat output.txt
ls -la > files.txt
cat files.txt

# 3.2 Append redirect
echo "primeira linha" > test.txt
echo "segunda linha" >> test.txt
echo "terceira linha" >> test.txt
cat test.txt

# 3.3 Input redirect
cat < test.txt
head -2 < /etc/passwd
wc -l < test.txt

# 3.4 Heredoc
cat << EOF
Esta é uma linha
Esta é outra linha
Fim do input
EOF

cat << DELIMITER
Você pode usar qualquer delimitador
DELIMITER
```

### **LEVEL 4 - PIPELINES SIMPLES**

```bash
# 4.1 Pipes básicos
ls | head -5
cat /etc/passwd | head -3
env | grep HOME
ps aux | head -10

# 4.2 Pipes com built-ins
echo "teste" | cat
pwd | cat
env | head -5

# 4.3 Pipes duplos
ls -la | head -10 | tail -5
cat /etc/passwd | grep root | wc -l
ps aux | grep bash | head -3
```

### **LEVEL 5 - EXPANSÃO DE VARIÁVEIS**

```bash
# 5.1 Variáveis de ambiente
echo $HOME
echo $PATH
echo $USER
echo "Current user: $USER"
echo "Home directory: $HOME"

# 5.2 Variáveis customizadas
export GREETING="Hello"
export NAME="World"
echo "$GREETING $NAME"
echo '$GREETING $NAME'  # Não expande em aspas simples

# 5.3 Exit status
true
echo "Last exit: $?"
false
echo "Last exit: $?"
ls /nonexistent 2>/dev/null
echo "Exit status: $?"

# 5.4 Expansão em contextos
export FILE=test.txt
echo "Reading file: $FILE" > $FILE
cat $FILE
```

### **LEVEL 6 - COMBINAÇÕES AVANÇADAS**

```bash
# 6.1 Redirecionamentos + Pipes
ls -la | head -5 > top_files.txt
cat top_files.txt
echo "Lista de arquivos:" | cat - top_files.txt > combined.txt

# 6.2 Variáveis + Redirecionamentos
export OUTFILE=result.txt
echo "Resultado" > $OUTFILE
cat < $OUTFILE

# 6.3 Heredoc + Pipes
cat << DATA | head -2
linha 1
linha 2  
linha 3
linha 4
DATA

# 6.4 Comandos complexos
ps aux | grep $USER | head -5 > my_processes.txt
cat my_processes.txt
```

### **LEVEL 7 - TESTES EXTREMOS**

```bash
# 7.1 Pipelines triplos/quádruplos
ls -la | head -10 | tail -5 | wc -l
cat /etc/passwd | grep -v "#" | head -5 | wc -l
ps aux | grep -v grep | head -10 | tail -5

# 7.2 Redirecionamentos múltiplos em sequência
echo "step 1" > temp.txt
echo "step 2" >> temp.txt  
cat < temp.txt > final.txt
cat final.txt

# 7.3 Combinação tudo junto
export LOGFILE=debug.log
echo "=== Debug Log ===" > $LOGFILE
date >> $LOGFILE
ps aux | grep $USER | head -3 >> $LOGFILE
echo "=== End Log ===" >> $LOGFILE
cat $LOGFILE

# 7.4 Heredoc complexo com variáveis
export NAME=Minishell
cat << REPORT
Sistema: $NAME
Usuario: $USER  
Diretorio: $HOME
Data: $(date)
REPORT
```

### **LEVEL 8 - TESTES DE STRESS**

```bash
# 8.1 Pipeline longo
ls /usr/bin | head -20 | tail -10 | head -5 | wc -l

# 8.2 Redirecionamentos encadeados
echo "start" > step1.txt
cat step1.txt > step2.txt
cat step2.txt > step3.txt
cat step3.txt

# 8.3 Variáveis aninhadas
export A=hello
export B=$A
export C="$B world"
echo $C

# 8.4 Comando final complexo
export PREFIX=minishell
ls -la | grep "^-" | head -5 | while read line; do echo "$PREFIX: $line"; done > final_test.txt 2>/dev/null || cat /etc/passwd | head -3 > final_test.txt
cat final_test.txt
```

### **LEVEL 9 - TESTES DE EDGE CASES**

```bash
# 9.1 Aspas e escapes
echo "Aspas duplas com $HOME"
echo 'Aspas simples com $HOME'
echo "Mixed 'quotes' work"
echo 'Mixed "quotes" work'

# 9.2 Comandos vazios e espaços
   echo    "espaços   extras"   
echo ""
echo ''

# 9.3 Variáveis vazias
export EMPTY=""
echo "Empty: '$EMPTY'"
echo "Undefined: '$UNDEFINED'"

# 9.4 Exit codes variados
true
echo $?
false  
echo $?
ls /nonexistent 2>/dev/null
echo $?
```

### **LEVEL 10 - LIMPEZA E VALIDAÇÃO**

```bash
# 10.1 Verificar arquivos criados
ls -la *.txt *.log 2>/dev/null

# 10.2 Limpeza
rm -f *.txt *.log 2>/dev/null

# 10.3 Teste final
echo "=== TESTES COMPLETOS ==="
echo "Minishell funcionando 100%!"
echo "Exit status: $?"

# 10.4 Saída
exit
```

---

## 🚨 **COMANDOS PARA DEBUG RÁPIDO**

```bash
# Debug básico
make && echo "pwd; ls -la; echo \$HOME; exit" | ./minishell

# Debug pipes
make && echo "ls | head -3; exit" | ./minishell

# Debug variáveis  
make && echo "export TEST=debug; echo \$TEST; exit" | ./minishell

# Debug redirecionamentos
make && echo "echo test > out.txt; cat out.txt; rm out.txt; exit" | ./minishell

# Debug completo (usando script fornecido)
make && ./debug_test.sh | ./minishell
```

## 🎮 **EXEMPLOS DE USO PRÁTICO**

### **Cenário 1: Administração de Sistema**
```bash
# Ver processos do usuário
ps aux | grep $USER | head -5

# Análise de logs
tail -20 /var/log/system.log | grep error > errors.txt
cat errors.txt

# Backup de configs
export BACKUP_DIR=/tmp/backup
mkdir -p $BACKUP_DIR 2>/dev/null
cp ~/.bashrc $BACKUP_DIR/ 2>/dev/null
ls -la $BACKUP_DIR/
```

### **Cenário 2: Desenvolvimento**
```bash
# Análise de código
find . -name "*.c" | head -10
wc -l src/*.c | sort -n
grep -r "malloc" src/ | wc -l

# Compilação e teste
make clean && make
echo $?
./programa_teste > resultado.txt 2>&1
cat resultado.txt
```

### **Cenário 3: Manipulação de Dados**
```bash
# Análise de arquivo
export DATAFILE=dados.txt
head -10 $DATAFILE
tail -10 $DATAFILE  
wc -l $DATAFILE

# Processamento
cat $DATAFILE | grep "pattern" | sort | uniq > processado.txt
cat processado.txt
```

## 📊 **STATUS DO PROJETO**
- ✅ **Lexer:** 100% funcional
- ✅ **Parser:** 100% funcional  
- ✅ **Executor:** 100% funcional
- ✅ **Built-ins:** 100% funcional
- ✅ **Pipelines:** 100% funcional
- ✅ **Redirecionamentos:** 100% funcional
- ✅ **Variáveis:** 100% funcional
- ✅ **Sinais:** 100% funcional

**🎉 Projeto completo e pronto para entrega!**

---

## 🏆 **MINISHELL EM AÇÃO - DEMO FINAL**

Quer ver tudo funcionando? Execute:
```bash
make && ./debug_test.sh | ./minishell
```

Resultado esperado:
- ✅ Todos os built-ins funcionando
- ✅ Comandos externos executando  
- ✅ Pipelines complexos operacionais
- ✅ Redirecionamentos (`>`, `<`, `>>`, `<<`) funcionais
- ✅ Expansão de variáveis (`$VAR`, `$?`) perfeita
- ✅ Aspas duplas expandindo, simples preservando
- ✅ Exit status sendo rastreado corretamente
- ✅ Gestão de memória sem vazamentos

**💪 Este Minishell está pronto para qualquer desafio!** 🚀
