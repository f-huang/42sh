# Test for 42sh

## table of content
- [env](#env)


### env
```
$> env -i
```
```
$> env --ignore-environment
```
```
$> env -
```
```
$> env -i "coucou===tata"
coucou==tata
```
```
$> env -i env
```
```
$> env -i "toto=tata" "titi=toto"
toto=tata
titi=toto
```
```
$> env MAIL=123
...
MAIL=123
...
```
```
$> env caca
env: caca: No such file or directory
```
```
$> env caca
env: caca: No such file or directory
```
```
$> env -i caca
env: caca: No such file or directory
```
```
$> env -i coucou=caca caca
env: caca: No such file or directory
```
```
$> env caca popo
env: caca: No such file or directory
```
```
$> env ls
Makefile	auteur		bin		include		libft		obj		src
```
```
$> env ls -a
.		.cache_exists	.gitignore	auteur		include		obj
..		.git		Makefile	bin		libft		src
```

```
$> env -i ls
Makefile	auteur		bin		include		libft		obj		src
```
```
$> env -i PATH=caca ls
env: ls: No such file or directory
```
