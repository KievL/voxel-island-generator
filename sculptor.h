#ifndef SCULPTOR_HPP
#define SCULPTOR_HPP

#include <iostream>

/**
  @brief Struct que representa um pixel em 3d
*/

struct Voxel {
  /**
    @brief Atributo que representa a intensidade de cor vermelha do Voxel.
    @details Varia de 0 a 1.
  */
  float r;

  /**
    @brief Atributo que representa a intensidade de cor verde do Voxel.
    @details Varia de 0 a 1.
  */
  float g;

  /**
    @brief Atributo que representa a intensidade de cor azul do Voxel.
    @details Varia de 0 a 1.
  */
  float b;

  /**
    @brief Atributo que representa a opacidade do Voxel.
    @details Varia de 0 a 1.
  */
  float a;

  /**
    @brief Atributo que representa se o Voxel está ativo ou não.
  */
  bool show;
};

/**
  @brief Classe que representa uma escultura em 3D.
  @details A classe Sculptor é responsável por criar uma escultura em 3D,
  utilizando Voxel's.
*/
class Sculptor {
private:
  /**
    @brief Matriz que representa a posição de cada Voxel da escultura.
  */
  Voxel ***v; // 3D matrix

  /**
    @brief Variável que representa o tamanho da dimensão x da matriz em que se
    encontra a escultura.
  */
  int nx;

  /**
    @brief Variável que representa o tamanho da dimensão y da matriz em que se
    encontra a escultura.
  */
  int ny;

  /**
    @brief Variável que representa o tamanho da dimensão z da matriz em que se
    encontra a escultura.
  */
  int nz;

  /**
    @brief Intensidade de cor vermelha do Sculptor.
    @details Varia de 0 a 1. Os Voxel's criados possuirão o valor desta variável para sua intensidade de vermelho.
  */
  float r;

  /**
    @brief Intensidade de cor verde do Sculptor.
    @details Varia de 0 a 1. Os Voxel's criados possuirão o valor desta variável para sua intensidade de verde.
  */
  float g;

  /**
    @brief Intensidade de cor azul do Sculptor.
    @details Varia de 0 a 1. Os Voxel's criados possuirão o valor desta variável para sua intensidade de azul.
  */
  float b;

  /**
    @brief Opacidade do Sculptor.
    @details Varia de 0 a 1. Os Voxel's criados possuirão o valor desta variável para sua opacidade.
  */
  float a;

public:
  /**
    @brief Construtor da classe Sculptor.
    @details Este construtor é responsável por inicializar a matriz v alocando
    dinâmicamente a memória necessária para armazenar os Voxel's.
    @param _nx é a dimensão x da matriz.
    @param _ny é a dimensão y da matriz.
    @param _nz é a dimensão z da matriz.
  */
  Sculptor(int _nx, int _ny, int _nz);

  /**
    @brief Destrutor da classe Sculptor.
    @details Este destrutor é responsável por liberar a memória alocada para a
    matriz
  */
  ~Sculptor();

  /**
    @brief Função que define a cor dos próximos Voxel's a serem criados.
    @details Essa função é responsável por alterar os atributos r, g, b e a da
    classe escultor os quais seram repassados para o Voxel.
    @param r é a intensidade da cor vermelha.
    @param g é a intensidade da cor verde.
    @param b é a intensidade da cor azul.
    @param a é a intensidade da transparência.
  */
  void setColor(float r, float g, float b, float a);

  /**
    @brief Função que adiciona um Voxel na escultura.
    @details Essa função é responsável por criar um Voxel em uma posição
    específica da matriz v. O Voxel é criado com as cores e transparência
    definidas pela função setColor.
    @param x é a posição x do Voxel que será colocado.
    @param y é a posição y do Voxel que será colocado.
    @param z é a posição z do Voxel que será colocado.
  */
  void putVoxel(int x, int y, int z);

  /**
    @brief Função que remove um Voxel da escultura.
    @details Essa função é responsável por remover um Voxel de uma posição
    específica da matriz v. O Voxel é considerado removido quando seu atributo
    show é igual a false.
    @param x é a posição x do Voxel que será removido.
    @param y é a posição y do Voxel que será removido.
    @param z é a posição z do Voxel que será removido.
  */
  void cutVoxel(int x, int y, int z);

  /**
    @brief Função que adiciona uma caixa de Voxel's na escultura.
    @details Essa função é responsável por criar uma caixa de Voxel's em uma
    posição específica da matriz v. Os Voxel's da caixa são criados com as cores
    e transparência definidas pela função setColor.
    @param x0 é a posição x do início da caixa que será colocado.
    @param x1 é a posição x do fim da caixa que será colocado.
    @param y0 é a posição y do início da caixa que será colocado.
    @param y1 é a posição y do fim da caixa que será colocado.
    @param z0 é a posição z do início da caixa que será colocado.
    @param z1 é a posição z do fim da caixa que será colocado.
  */
  void putBox(int x0, int x1, int y0, int y1, int z0, int z1);

  /**
    @brief: Função que remove uma caixa de Voxel's da escultura.
    @details: Essa função é responsável por remover uma caixa de Voxel's de uma
    posição específica da matriz v. Os Voxel's da caixa são removidos quando o
    atributo show de cada um deles recebe false.
    @param x0 é a posição x do início da caixa que será removida.
    @param x1 é a posição x do fim da caixa que será removida.
    @param y0 é a posição y do início da caixa que será removida.
    @param y1 é a posição y do fim da caixa que será removida.
    @param z0 é a posição z do início da caixa que será removida.
    @param z1 é a posição z do fim da caixa que será removida.
  */
  void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);

  /**
    @brief: Função que adiciona uma esfera de Voxel's na escultura.
    @details: Essa função é responsável por criar uma esfera de Voxel's em uma
    posição específica da matriz v. Os Voxel's da esfera são criados com as cores
    e transparência definidas pela função setColor.
    @param xcenter é a posição x do centro da esfera que será colocada.
    @param ycenter é a posição y do centro da esfera que será colocada.
    @param zcenter é a posição z do centro da esfera que será colocada.
    @param radius é o raio da esfera que será colocada.
  */
  void putSphere(int xcenter, int ycenter, int zcenter, int radius);

  /**
    @brief: Função que remove uma esfera de Voxel's da escultura.
    @details: Essa função é responsável por remover uma esfera de Voxel's de uma
    posição específica da matriz v. Os Voxel's da esfera são removidos quando o
    atributo show de cada um deles recebe false.
    @param xcenter é a posição x do centro da esfera que será removida.
    @param ycenter é a posição y do centro da esfera que será removida.
    @param zcenter é a posição z do centro da esfera que será removida.
    @param radius é o raio da esfera que será removida.
  */
  void cutSphere(int xcenter, int ycenter, int zcenter, int radius);

  /**
    @brief: Função que adiciona um elipsóide de Voxel's na escultura.
    @details: Essa função é responsável por criar um elipisóide de Voxel's em uma
    posição específica da matriz v. Os Voxel's do elipsóide são criados com as
    cores e transparência definidas pela função setColor.
    @param xcenter é a posição x do centro do elipsóide que será colocado.
    @param ycenter é a posição y do centro do elipsóide que será colocado.
    @param zcenter é a posição z do centro do elipsóide que será colocado.
    @param rx é o raio da posição x do elipsóide que será colocado.
    @param ry é o raio da posição y do elipsóide que será colocado.
    @param rz é o raio da posição z do elipsóide que será colocado.
  */
  void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry,
                    int rz);

  /**
    @brief: Função que remove um elipsóide de Voxel's da escultura.
    @details: Essa função é responsável por remover um elipisóide de Voxel's de
    uma posição específica da matriz v. Os Voxel's do elipsóide são removidos
    quando o atributo show de cada um deles recebe false.
    @param xcenter é a posição x do centro do elipsóide que será colocado.
    @param ycenter é a posição y do centro do elipsóide que será colocado.
    @param zcenter é a posição z do centro do elipsóide que será colocado.
    @param rx é o raio da posição x do elipsóide que será removido.
    @param ry é o raio da posição y do elipsóide que será removido.
    @param rz é o raio da posição z do elipsóide que será removido.
  */
  void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry,
                    int rz);

  /**
    @brief: Função que escreve os dados da escultura em um arquivo.
    @details: Essa função é responsável por escrever as informações da escultura
    em um arquivo .OFF. Essas informações são: número de faces, número de
    vértices, declaração de cada vértice, declaração de cada face.
    @param filename é o nome do arquivo que será escrito.
  */
  void writeOFF(const char *filename);
};

#endif