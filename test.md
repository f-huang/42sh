# Test for 42sh

## table of content
- [env](#env)


### env
```shell
$> env -i
```
```
$> env --ignore-environment
```
```shell
$> env -
```
```shell
$> env -i -
```
```shell
$> env -i - ls
Makefile	auteur		bin		include		libft		obj		src
```
```shell
$> env "- "
env: illegal option --
usage: env [-iv] [-P utilpath] [-S string] [-u name]
           [name=value ...] [utility [argument ...]]
$> echo $?
1
```
```shell
$> env -z
env: illegal option -- z
usage: env [-iv] [-P utilpath] [-S string] [-u name]
           [name=value ...] [utility [argument ...]]
$> echo $?
1
```
```shell
$> env -i "coucou===tata"
coucou==tata
```
```shell
$> env -i env
```
```shell
$> env -i "toto=tata" "titi=toto"
toto=tata
titi=toto
```
```shell
$> env MAIL=123
...
MAIL=123
...
```
```shell
$> env caca
env: caca: No such file or directory
```
```shell
$> env caca
env: caca: No such file or directory
```
```shell
$> env -i caca
env: caca: No such file or directory
```
```shell
$> env -i coucou=caca caca
env: caca: No such file or directory
```
```shell
$> env caca popo
env: caca: No such file or directory
```
```shell
$> env ls
Makefile	auteur		bin		include		libft		obj		src
```
```shell
$> env ls -a
.		.cache_exists	.gitignore	auteur		include		obj
..		.git		Makefile	bin		libft		src
```

```shell
$> env -i ls
Makefile	auteur		bin		include		libft		obj		src
```
```shell
$> env -i PATH=caca ls
env: ls: No such file or directory
```
```shell
$> env -u MAIL=
unsetenv env: MAIL=: Invalid argument
```
