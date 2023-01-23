
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <iostream>

__global__ // Decoradores (igual que en ts). Por defecto, cualquier cosa no decorada, se delcara como __host__.
void suma_vectores_gpu(float* pA, float* pB, float* pC, const int cN) {
	int idX_ = blockIdx.x * blockDim.x + threadIdx.x ; // La formula para atacar memorias = blockIdx.x * blockDim.x + threadIdx.x (la x es para porque es unidimensional (viene de un struct interno)).
	pC[idX_] = pA[idX_] + pB[idX_];
}

void suma_vectores(float* pA, float* pB, float* pC, const int cN) { // Funcion que suma vectores.
	for (unsigned int i = 0; i < cN; i++) {
		pC[i] = pA[i] + pB[i];
	}
}

int main(void) {
	const int kNumElemets = 25600;
	const size_t kNumBytes = kNumElemets * sizeof(float);

	// PASO 0: Seleccionar el dispositivo (tarjeta grafica).
	cudaSetDevice(0); // Tarjeta 0, primera tarjeta que usa el dispositivo.

	// PASO 1: Declaracion de memoria en la GPU.
	float* d_a_ = NULL; // Por convencion se inicializa a NULL.
	float* d_b_ = NULL; // La d_ especifica que la variable se alojará en la GPU (es un convenio en CUDA).
	float* d_c_ = NULL;

	cudaMalloc((void **)&d_a_, kNumBytes); // La GPU no entiende de tipos, por ello hay que castear a void, usamos & para pasar el puntero.
	cudaMalloc((void **)&d_b_, kNumBytes); // cudaMalloc es igual que malloc pero en la RAM de la GPU (VRAM).
	cudaMalloc((void **)&d_c_, kNumBytes); 

	float* h_a_ = (float *)malloc(kNumBytes); // La h_ especifica que la variable se alojará en la CPU (es un convenio en CUDA).
	float* h_b_ = (float *)malloc(kNumBytes); // malloc allocates the requested memory and returns a pointer to it.
	float* h_c_ = (float *)malloc(kNumBytes);

	if (h_a_ == NULL || h_b_ == NULL || h_c_ == NULL) { // Comprobamos que el ordenador tiene memoria suficiente par alojar las variables.
		std::cerr << "Fallo al reservar la memoria \n";
		getchar(); // Para que no se cierre la ventana nada mas mostrar el mensaje de error.
		exit(-1); // Codigo de salida de error predefinido.
	}

	for (unsigned int i = 0; i < kNumElemets; i++) { // Rellenamos los vectores con datos aleatorios.
		h_a_[i] = rand() / (float)RAND_MAX;
		h_b_[i] = rand() / (float)RAND_MAX;
	}

	// PASO 2: Copia de datos CPU a GPU.
	cudaMemcpy(d_a_, h_a_, kNumBytes, cudaMemcpyHostToDevice); // Mandamos los datos a la VRAM.
	cudaMemcpy(d_b_, h_b_, kNumBytes, cudaMemcpyHostToDevice); // Destino, Origen, Cantidad de bytes a copiar, flag que especifica en que direccion (de CPU a GPU).

	// PASO 3: Lanzar kernel (ejecutar computo).

	// suma_vectores(h_a_, h_b_, h_c_, kNumElemets);

	const int thread_per_block_ = 256;
	const int blocks_per_grid_ = kNumElemets / thread_per_block_;

	dim3 tpb_(thread_per_block_, 1, 1);
	dim3 bpg_(blocks_per_grid_, 1, 1);

	suma_vectores_gpu<<<bpg_, tpb_>>>(d_a_, d_b_, d_c_, kNumElemets);
	cudaError error_ = cudaGetLastError(); // Si hay un error, se guarda en una porcion de memoria de la GPU, esta funcion te devuelve este valor.

	if (error_ != cudaSuccess) {
		std::cerr << "Fallo en el kernel" << cudaGetErrorString(error_) << "\n";
		getchar(); // Para que no se cierre la ventana nada mas mostrar el mensaje de error.
		exit(-1); // Codigo de salida de error predefinido.
	}

	cudaMemcpy(h_c_, d_c_, kNumBytes, cudaMemcpyDeviceToHost); // Nos traemos los datos de vuelta de la VRAM.

	// Comprobamos que los datos son los mismos.
	for (unsigned int i = 0; i < kNumElemets; i++) {
		if (fabs(h_a_[i] + h_b_[i] - h_c_[i]) > 1e-5) { // Si el valor rendondeado tiene un error mayor a un umbral (en este caso 1e-5), se ha calculado mal.
			std::cerr << "Fallo en la posicion: " << i << "\n";
			std::cerr << "Resultado es: " << h_c_[i] << "\n";
			std::cerr << "Se esperaba: " << h_a_[i] + h_b_[i] << "\n";
			getchar();
			exit(-1);
		}
	}

	// PASO 4: Librerar recursos. (destruir).
	free(h_a_);
	free(h_b_);
	free(h_c_);

	cudaFree(d_a_);
	cudaFree(d_b_);
	cudaFree(d_c_);

	cudaDeviceReset(); // Elibera y resetea el dispositivo.

	std::cout << "Optimo \n"; // Mensaje de exito.
	getchar();

}
