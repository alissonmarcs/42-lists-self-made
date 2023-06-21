## Por que tem dois arquivos? atoi.c e ft_atoi.c
O exercício pede um "extra" na função `ft_atoi()`. Caso a string tenha um número ímpar de sinais `-`, a função deve retornar um valor negativo, caso contrário ela deve retornar um valor positivo. O arquivo `ft_atoi.c` tem esse tratamento extra.

Você pode passar a string de teste na invocação do programa.

## A função atoi()
A função `atoi()`recebe uma string e converte a primeira parte que contém dígitos para inteiro. Caso tenha algum caractere `ìsspace()`, ela ignora.

```c
printf("%d\n", atoi("  -234e45"));
// -234 no terminal
```

## Minha implementação

```c
int ft_atoi(const char *str)
{
	int result;
	int signal;
	int i;

	result = 0;
	signal = 1;
	i = 0;

	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;

	if (str[i] == '-' || str[i] == '+')
		signal = 1 - 2 * (str[i++] == '-');

	while (str[i] >= '0' && str[i] <= '9')
		result = 10 * result + (str[i++] - '0');

	return (result * signal);
}
```

### Cálculo do sinal

```c
	if (str[i] == '-' || str[i] == '+')
		signal = 1 - 2 * (str[i++] == '-');
```
Precisamos guardar `1` ou `-1` no `signal` a depender do sinal encontrado (`1` para `+` ou `-1` para `-`) . Lá no fim vamos retornar a multiplicação `result * signal` e teremos o resultado esperado.

Caso o ```(str[i++] == '-')``` seja verdadeiro, temos:

```c
signal = 1 - 2 * (str[i++] == '-');
signal = 1 - 2 * 1;
signal = 1 - 2;
signal = -1;
```

Caso o ```(str[i++] == '-')```seja falso, temos:

```c
signal = 1 - 2 * (str[i++] == '-');
signal = 1 - 2 * 0;
signal = 1 - 0;
signal = 1;
```

## Cálculo do resultado
Cada dígito em um número tem um "peso". Multiplicando o dígito pelo "peso" da "casa" que ele ocupa, fazendo isso para os demais digitos do número e, ao fim, somanto os resultados encontrados, temos o valor do número:

200 + 30 + 4 = 234
(2 * 100) + (3 * 10) + (4 * 1) = 234

Vamos chamar a forma acima de "forma tradicional".

O código a seguir vai fazer a mesma coisa mas de uma forma diferente. Importante notar que iniciamos o `result` com zero.

```c
while (str[i] >= '0' && str[i] <= '9')
	result = 10 * result + (str[i++] - '0');
```

Considere `ft_atoi("234")`. O cálculo funciona da seguinte forma:
1. Pegue o primeiro dígito do número.
2. Multiplique o valor prévio por 10 para ter a dezena, e some com o valor do dígito atual.
3. Multiplique o valor prévio por 10 para ter a centena, e some com o valor do dígito atual.
4. E assim vai... 

Perceba que, na primeira iteração, o `result` guardará o valor do primeiro dígito, visto que `10 * result` resultará`0` (`result` inicia com `0`).  Ao fim da primeira iteração, `result = 2`.

Na segunda iteração, multiplicamos por 10 o valor prévio de `result` e somamos a este o valor do dígito atual: `result = 10 * result + (str[i++] - '0')`. Ao fim da segunda iteração, `result = 23`.

Na terceira iteração, multiplicamos por 10 o valor prévio de `result`e somamos a este o valor do dígito atual: `result = 10 * result + (str[i++] - '0')`. Ao fim da terceira iteração, `result = 234`.

Agora vamos comparar a "forma tradicional" com a solução em código.

(2 * 100) + (3 * 10) + (4 * 1) = 234
Não temos um equivalente na forma tradicional para o "pegue o primeiro dígito do número", então vamos pular.

(3 * 10) é equivalente a segunda iteração, ambas vão nos dar a dezena do número.

(2 * 100) é  equivalente a terceita iteração, ambas vão nos dar a centena do número. No caso da solução em código, esse passo vai nos dar também, além da centena, a unidade do número.
