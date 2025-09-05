<!-- ===================== BANNER ===================== -->
<p align="center">
  <img src="https://raw.githubusercontent.com/NanoHtz/Assets/main/pipex/banner.svg" alt="Pipex banner">
</p>

<p align="center"><i>🧵 Pipex — Replica del pipeline de shell <code>&lt; infile cmd1 | cmd2 &gt; outfile</code> usando <b>pipe</b>/<b>fork</b>/<b>dup2</b>/<b>execve</b>.
---

## Índice
- [Resumen](#resumen)
- [¿Para qué?](#para-que)
- [Explicación](#explicacion)
- [Compilación](#compilacion)
- [Uso](#uso)
- [Salida esperada y pruebas](#salida)

---
<a id="resumen"></a>
## ✅ Resumen del proyecto<br>

**Pipex** reproduce, en C, el comportamiento básico de un **pipeline** de la shell:
```bash
./pipex infile "cmd1" "cmd2" outfile
```
Se realiza la **resolución de rutas** con `PATH`, la **creación de procesos** con `fork`, la **conexión** entre procesos con `pipe`, el **redireccionamiento** con `dup2` y la **ejecución** con `execve`, controlando errores y cerrando correctamente los descriptores.
<a id="para-que"></a>
## 🧩 ¿Para qué?

**¿Qué se aprende?**
- **Procesos**: `fork`, sincronización con `wait`/`waitpid`.
- **Descriptores y tuberías**: `pipe`, extremos de lectura/escritura, cierre selectivo.
- **Redirecciones**: `dup2` para reenviar `STDIN`/`STDOUT`.
- **Ejecución de programas**: `execve`, construcción de `argv`/`envp`.
- **Resolución de comandos**: lectura de `PATH`, prueba de ejecutables (`access(X_OK)`).
- **Manejo de errores**: `perror`, códigos de salida, permisos/archivos inexistentes.
- **Diseño escalable**: generalizar de 2 comandos → N comandos (`bonus`) y `here_doc`.

---

<a id="explicacion"></a>
<details>
  <summary><h3>📝 Explicación</h3></summary>

### 🔌 Tuberías y duplicación de FDs
- `pipe(fd)` crea dos extremos: `fd[0]` (lectura) y `fd[1]` (escritura).
- `dup2(old, new)` redirige `new` hacia `old`. Tras duplicar, puedes **cerrar** el original.
- Cada proceso debe **cerrar** todos los FDs que **no usa** para evitar bloqueos (lectores que nunca ven EOF).

### 🧭 Flujo
Equivalente a: `< infile cmd1 | cmd2 > outfile`

1) **Abrir** ficheros  
   - `infile`: `open(..., O_RDONLY)`  
   - `outfile`: `open(..., O_CREAT|O_TRUNC|O_WRONLY, 0644)`

2) **Crear** `pipe(p)`  

3) **fork #1 (hijo A → cmd1)**  
   - `dup2(infile, STDIN_FILENO)`  
   - `dup2(p[1], STDOUT_FILENO)`  
   - **Cerrar**: `infile`, ambos `p[]`, `outfile` (no lo usa)  
   - **execve** de `cmd1` (tras resolver PATH)  

4) **fork #2 (hijo B → cmd2)**  
   - `dup2(p[0], STDIN_FILENO)`  
   - `dup2(outfile, STDOUT_FILENO)`  
   - **Cerrar**: `outfile`, ambos `p[]`, `infile`  
   - **execve** de `cmd2`  

5) **Padre**  
   - Cierra **todos** los FDs (`infile`, `outfile`, `p[0]`, `p[1]`)  
   - `waitpid` a los hijos y propaga un código de salida coherente (p. ej. el del último comando)

<a id="compilacion"></a>
## 🛠️ Compilación
⬇️ Descarga

```bash
git clone https://github.com/NanoHtz/Pipex.git
```
🏗️ Makefile
```bash
make          # produce ./pipex  (mandatory)
make bonus    # produce ./pipex_bonus (N comandos + here_doc)
make clean    # borra objetos
make fclean   # borra objetos y binarios
make re       # limpia y recompila
```

