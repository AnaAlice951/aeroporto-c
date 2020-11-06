#include "fila-aviao.hpp"
#include "aeroporto.hpp"
#include "utilitario.hpp"

int main() {
	// Seed do gerador de números aleatórios
	srand(time(NULL));
	
	// Execução dos turnos
	for(int ut = 0; ut < 10000; ut++) {
		// Limpa a tela ao início de cada turno 
		system("cls");

		// Gera novos aviões para as filas
		gerarNovosAvioes(novosAvioesPouso, novosAvioesDecolagem, &numAvioesPouso, &numAvioesDecolagem, ut);
		
		// Normalizar operações das filas
		normalizarOperacoes(filas);

		// Enfileira os novos aviões nas pistas buscando manter as filas com o mesmo tamanho
		enfileirarNovosAvioes(novosAvioesPouso, novosAvioesDecolagem, filas, numAvioesPouso, numAvioesDecolagem);

		// Mostrar o conteúdo das filas
		mostrarFilas(filas);

		// Aterrisa e decola os aviões nas filas
		aterrisaDecolaAvioes(filas, ut);

		// Decrementa o combustível de todos os aviões no ar
		decrementarCombustivel(filas);

		// Estatísticas periódicas
		if(numPousados)
			printf("Tempo medio de espera para aterrisagem: %d turnos\n", (somaTempoAterrisagem / numPousados));
		if(numDecolados)
			printf("Tempo medio de espera para decolagem: %d turnos\n", (somaTempoDecolagem / numDecolados));
		printf("Quantidade de avioes que ja pousaram emergencialmente: %d\n\n\n", numPousosEmergencia);

		// Pausa entre os turnos 
		system("pause");
	}

	// Estatísticas (fim da execução)
	system("cls");
	printf("\n\tRESULTADOS DA EXECUCAO\n");
	printf("Tempo medio de espera para aterrisagem: %d turnos\n", (somaTempoAterrisagem / numPousados));
	printf("Tempo medio de espera para decolagem: %d turnos\n", (somaTempoDecolagem / numDecolados));
	printf("Um total de %d avioes pousaram em seguranca\n", numPousados + numPousosEmergencia);
	printf("Um total de %d avioes decolaram\n", numDecolados);
	printf("Um total de %d avioes precisaram realizar um pouso de emergencia\n", numPousosEmergencia);
	printf("Um total de %d avioes nao conseguiram pousar em seguranca e cairam\n", numQuedas);

	return 0;
}
