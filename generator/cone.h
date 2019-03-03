#ifndef GENERATOR_CONE_H
#define GENERATOR_CONE_H

/**
 * Esta função, dado um raio, uma altura, um número de slices e de stacks e
 * um nome de um ficheiro, gera todos os vértices necessários para a
 * formação de triângulos, que juntos formarão um cone. Os vértices gerados
 * serão guardados num ficheiro .3d
 * @param botRad Raio da base do cone;
 * @param slices Número de slices (cortes verticais) do cone;
 * @param stacks Número de stacks (cortes horizontais) do cone;
 * @param fname Nome do ficheiro onde serão guardados os vértices gerados;
 * O número de triângulos que serão usados para a
 * base do cone é proporcional ao número de slices fornecidas, enquanto
 * que o número de triângulos necessários para a superfície lateral é proporcional
 * ao número de stacks e slices
 */
int createCone(float botRad, float height, int slices, int stacks, char * fname);

#endif
