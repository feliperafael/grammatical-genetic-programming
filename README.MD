
# UFJF genetic programming

Este repositório contém um código em C++ para um algoritmo de programação genética. 


<b>Requerimentos</b>: 
- C++ 11 ou superior
- Cmake

<b>Como compilar?</b> 
- crie e entre em uma pasta chama build (você pode usar outro nome de sua preferência) dentro da raiz do projeto.

```shell
mkdir build
cd build
```
- Compile o código fonte utilizando o comando
```shell
cmake ..
make
```

<br>
<b>Como rodar?</b> 
Após compilar abra o terminal na raiz do projeto e rode o seguinte comando no seu terminal:

```shell
./build/pgufjf config_reg.xml
```
<br>
O arquivo config_reg.xml está configurado para o problema da função horária do espaço S = So + Vot + at²/2  

# <b>Arquivo de configuração</b>
O arquivo de configuração `config.xml ` deve ser adaptado com os caminhos para os dados de entrada do seu problema, assim como os hiperparametros escolhidos para seu problema.

## Configurações Gerais
- `<operators_rate>`: Especifica as taxas de mutação, cruzamento e elitismo. Ajuste os valores dos atributos mutation, crossover e elitism de acordo com suas preferências.

- `<search>`: Define o tamanho da população e o número de gerações para a execução do algoritmo. Ajuste os valores dos atributos population e generation de acordo com suas necessidades.

- `<model>`: Define a profundidade máxima para as árvores geradas pelo algoritmo. Ajuste o valor do atributo maxdeep de acordo com as restrições do seu problema.

- `<seed>`: Define a semente para a geração de números aleatórios. Ajuste o valor do atributo value de acordo com suas preferências.

- `<num_threads>`: Define o número de threads a serem utilizadas pelo algoritmo. Ajuste o valor do atributo value de acordo com a capacidade do seu sistema.

## Configurações de Entrada de Dados
As configurações de entrada de dados especificam os caminhos para os arquivos de dados do seu problema. Ajuste os valores dos atributos file para corresponder aos caminhos corretos dos arquivos de entrada.

- `<data>`: Especifica o arquivo de dados principal. Ajuste o valor do atributo file para o caminho correto do arquivo de dados.

- `<datagroup>`: Especifica a divisão dos dados de treino, validação e teste.

- `<grammatic>`: Especifica o arquivo de gramática. Ajuste o valor do atributo file para o caminho correto do arquivo de gramática.

```xml
<?xml version="1.0"?>
<genetic_programming>
	<config>
		<operators_rate mutation="0.1" crossover="0.9" elitism="0.1" >
			
		</operators_rate>
		<search population="100" generation="500" />
		<model maxdeep="5" />
		<seed value="42" />
		<num_threads value="4" />
	</config>
	<input>	  
		<data file="input/data/data_vst.dat"/>
		<datagroup file="input/data/data_knn_60.grp"/>
		<grammatic file="input/grammar/vst.dat"/>
	</input>
</genetic_programming>
```
# Gramatica


    
    # Grammar Dictionary
     1. Non Terminals = <x>
     2. Terminals
    	 2.1. Numbers = 1, 1.1, 11.11
    	    2.2 - Variables = x, x1, name **** mesmo escrito na base de dados ****
    	    2.3 - Operators and Constants
    	        2.3.1 Constants
    	            2.3.1.1 PI_
    	            ......
    	        2.3.2 Operators
    	            2.3.2.1 Sum = +
    	            2.3.2.1 Sub = -
    	            2.3.2.1 Times = *
    	            2.3.2.1 Division = /
    	            2.3.2.1 Pow = ^
    	            2.3.2.1 Square Root = sqrt
    	            2.3.2.1 Exponential = exp
    	            2.3.2.1 Natural Logarithm = log
    

<br>
<b>Como o código está organizado?</b><br>
<p>O diretório /src é onde estão todos os códigos-fonte básicos da programação genética, incluindo classes abstratas e implementações padrão.</p>
<p>O diretório /input é onde os arquivos de entrada dependem do problema em questão.</p>
<p>No diretório /include devem estar todos os arquivos adicionados ao código-fonte básico em /src ou todas as classes derivadas implementadas.</p>
<b>Como adaptar o código para um novo problema?</b>
Em breve

----------


<b>Como está organizado o código?</b>
<br>
<b>Configures.h</b>
Contém todas configurações e parâmetros necessários no código. Pode ser acessado de qualquer classe.

<b>Crossover.h</b><br>
Classe abstrata responsável pelo cruzamento dos indivíduos. Você deve estender essa classe e implementar sua função de cruzamento, a qual recebe um vetor de indivíduos e seu tamanho.<br><br>

<pre>void cross(Individual ** vec_individuos, int num_individuos);</pre>
<br>
<b>Database.h</b>
Classe abstrata de dados responsável pelos dados utilizados pelo AG. caso você use leitura de arquivos diferentes do formato padrão você deve estender a função loadBase conforme sua necessidade.<br><br>
 
<pre>void loadBase(string base_name);</pre><br>

onde base_name é o nome do arquivo de entrada<br><br>

<b>Individual.h</b><br>
Classe abstrata com a representação do indivíduo. Possui atributo aptidão, o qual indica o quão apto está minha solução/individuo. Essa classe deve ser estendida conforme a necessidade do problema a ser resolvido.<br><br>

<b>IndividualBuilder.h</b><br>
Classe abstrata responsável pela criação de um indivíduo. Quando criado um novo indivíduo também deve ser criado um individuoBuilder responsável pela sua geração.<br><br>

<pre>Individual * generateIndividuo();</pre>

<b>IndividualSelector.h</b><br>
Classe abstrata responsável pela seleção dos indivíduos da população para cruzamento e mutação.<br>

Individual * selects(Individual ** pop);<br><br>

<b>LocalSearch.h</b><br>
Classe abstrata responsável por realizar busca local/ ajuste de parâmetros em um dado indivíduo. Deve ser estendida conforme o tipo de indivíduo do problema.
<br><br>
<b>Mutation.h</b><br><br>
Classe abstrata responsável pela mutação de um dado indivíduo.  Deve ser estendida conforme o tipo de indivíduo do problema.<br><br>
<b>Parser.h</b><br>
Classe abstrata responsável por avaliar a qualidade de uma solução/individuo. Também  deve ser estendida conforme o tipo de indivíduo do problema.
<br><br>

<b>PopulationReplacement.h</b><br>
Classe abstrata responsável pela junção dos indivíduos da antiga população com a nova população do AG. Pode ser estendida conforme características do problema.<br><br>

<b>SearchEngine.h</b><br>
Parte central do Algoritmo Genético, essa classe é responsável por fazer as chamadas dos operadores genéticos e por guiar todo o processo de busca.O método void Evolve(); é responsável por evoluir uma população de soluções com as características setadas em SearchEngine e com os parâmetros setados no arquivo de configuração Configures.h. Essa classe possui diversos métodos sets para setar classes que foram estendidas segundo características do problema:<br><br>
<pre>
void setCrossover(Crossover * opCrossover);
void setMutation(Mutation * opMutation);
void setIndividualBuilder(IndividualBuilder * indBuilder);
void setPopulationReplace(PopulationReplacement * popReplace);
void setParser(Parser * parser);
void setSelection(IndividualSelector * seletor);
void setLocalSearch(LocalSearch * localSearch);
</pre>

## License

MIT

**Free Software, :D!**

