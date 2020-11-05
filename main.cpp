#include "fila-aviao.hpp"
#include "aeroporto.hpp"
#include "utilitario.hpp"

int main() {
	// Seed do gerador de números aleatórios
	srand(time(NULL));
	
	// Execução dos turnos
	for(int ut = 0; ut < 10000; ut++) {
		// Limpar a tela ao início de cada turno (opcional)
		//system("cls");

		// Gera novos aviões para as filas com reserva de combustível aleatório
		gerarNovosAvioes(novosAvioesPouso, novosAvioesDecolagem, &numAvioesPouso, &numAvioesDecolagem, ut);
		
		// Normalizar operações das filas
		normalizarOperacoes(filas);

		// Enfileira os novos aviões alternadamente nas pistas, buscando mantê-las com o mesmo tamanho
		enfileirarNovosAvioes(novosAvioesPouso, novosAvioesDecolagem, filas, numAvioesPouso, numAvioesDecolagem);

		// Mostrar o conteúdo das filas (opcional)
		//mostrarFilas(filas);

		// Aterrisa e decola os aviões nas filas
		aterrisaDecolaAvioes(filas, ut);

		// Decrementa o combustível de todos os aviões no ar
		decrementarCombustivel(filas);

		// Pausa entre os turnos (opcional)
		//system("pause");
	}

	// Estatísticas (fin da execução)
	printf("\n\tRESULTADOS DA EXECUCAO\n");
	printf("Tempo medio de espera para aterrisagem: %d turnos\n", (somaTempoAterrisagem / numPousados));
	printf("Tempo medio de espera para decolagem: %d turnos\n", (somaTempoDecolagem / numDecolados));
	printf("Um total de %d avioes pousaram em seguranca\n", numPousados + numPousosEmergencia);
	printf("Um total de %d avioes decolaram\n", numDecolados);
	printf("Um total de %d avioes precisaram realizar um pouso de emergencia\n", numPousosEmergencia);
	printf("Um total de %d avioes nao conseguiram pousar em seguranca e cairam\n", numQuedas);

	return 0;
}
