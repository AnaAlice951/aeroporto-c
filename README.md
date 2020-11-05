# aeroposto-c

O objetivo deste trabalho é simular os padrões de aterrissagem e decolagem em um
aeroporto. Suponha um aeroporto que possui três pistas, numeradas como 1, 2 e 3. Existem quatro “prateleiras” de espera para aterrissagem, duas para cada uma das
pistas 1 e 2. Aeronaves que se aproximam do aeroporto devem integrar-se a uma das
prateleiras (filas) de espera, sendo que estas filas devem procurar manter o mesmo
tamanho. Assim que um avião entra em uma fila de aterrissagem, ele recebe um
número de identificação ID e outro número inteiro que indica a quantidade de
unidades de tempo que o avião pode permanecer na fila antes que ele tenha de descer
(do contrário, seu combustível termina e ele cai).

Existem também filas para decolagem, uma para cada pista. Os aviões que chegam
nessas filas também recebem uma identificação ID. Essas filas também devem
procurar manter o mesmo tamanho. A cada unidade de tempo, de zero a três
aeronaves podem chegar nas filas de decolagem e de zero a três aeronaves podem
chegar nas prateleiras. A cada unidade de tempo, cada pista pode ser usada para um
pouso ou uma decolagem.

A pista 3 em geral só é usada para decolagens, a não ser que um dos aviões nas
prateleiras fique sem combustível, quando então ela deve ser imediatamente usada
para pouso. Se apenas uma aeronave está com falta de combustível, ela pousará na
pista 3; se mais de um avião estiver nesta situação, as outras pistas poderão ser
utilizadas. Utilize inteiros pares (ímpares) sucessivos para os IDs dos aviões chegando
nas filas de decolagem (aterrissagem).

A cada unidade de tempo assuma que os aviões entram nas filas antes que
aterrissagens ou decolagens ocorram. Tente projetar um algoritmo que não permita o
crescimento excessivo das filas de aterrissagem ou decolagem. Coloque os aviões
sempre no final das filas, que não devem ser reordenadas. A saída do programa deverá
indicar o que ocorre a cada unidade de tempo. Periodicamente, imprima:


**a) o conteúdo de cada fila;**

**b) o tempo médio de espera para decolagem;**

**c) o tempo médio de espera para aterrissagem;**

**d) o número de aviões que aterrissaram sem reserva de combustível.**

Os itens b e c acima devem ser calculados para os aviões que já decolaram ou
pousaram, respectivamente. A saída do programa deve ser auto-explicativa e facil de
entender. A entrada deve ser criada utilizando um gerador de números aleatórios . Para cada unidade de tempo, a entrada deve ter as seguintes informações: 

**a) número de aviões (zero a três) chegando nas filas de aterrissagem com respectivas reservas de
combustível (de 1 a 20 em unidades de tempo);**

**b) número de aviões (zero a três) chegando nas filas de decolagem.**

---
* Para atualizar o seu repositório local

```console
git pull
```

* Para atualizar o repositório remoto com as suas modificações

```console
cd diretorio_do_projeto
git add .
git commit -m "insira aqui um resumo breve das modificações realizadas"
git push
```

Obs: confira se você está com a sua conta do Github devidamente configurada na máquina local.