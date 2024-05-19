#include "FastNoiseLite.h"
#include "sculptor.h"
#include <cmath>
#include <iostream>

int main() {

  int seed;
  std::cout << "Seed: ";
  std::cin >> seed;

  FastNoiseLite myNoise;
  myNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
  myNoise.SetSeed(seed);
  myNoise.SetFrequency(0.08);

  Sculptor scp(80, 80, 80);

  scp.setColor(1.0, 1.0, 1.0, 1.0); // Branco

  int sea_level = 8;

  //bool eli = true;
  bool tree = true;

  for (float x = 0; x < 80; x++) {
    for (float z = 0; z < 80; z++) {

      float noise = myNoise.GetNoise(x, z);
      
      noise += 0.7;

      int multiplicador_noise = 22;

      int y_noise = (int)(noise * multiplicador_noise);
      float distance = std::sqrt(std::pow(x - 40, 2) + std::pow(z - 40, 2));

      int y_filter = 1 * distance;

      int y_height = y_noise - y_filter + 20;

      if (y_height < 0) {
        y_height = 0;
      };

      if (y_height < sea_level + 4) {
        scp.setColor(0.93, 0.80, 0.53, 1.0);

      } else if (y_height < sea_level + 8) {
        scp.setColor(0.67, 0.8, 0.47, 1.0);

      } else if (y_height < sea_level + 15) {
        scp.setColor(0.4, 0.8, 0.4, 1.0);

      } else if (y_height < sea_level + 18) {
        scp.setColor(0.32, 0.53, 0.31, 1.0);

      } else if (y_height < sea_level + 23) {
        scp.setColor(0.25, 0.26, 0.23, 1.0);

      } else if (y_height < sea_level + 27) {
        scp.setColor(0.63, 0.62, 0.61, 1.0);

      } else {
        scp.setColor(1.0, 0.98, 0.98, 1.0);
      }
            
      scp.putBox(x, x, 0, y_height, z, z);

      // Criar árvores
      if (y_height > sea_level + 15 && y_height < sea_level + 17 && tree) {
        tree = false;

        scp.setColor(0.59, 0.29, 0.0, 1.0);
        scp.putBox(x, x, sea_level + 17, sea_level + 20, z, z);

        scp.setColor(0.22, 0.39, 0.20, 1.0);
        scp.putSphere(x, sea_level + 20, z, 2);
      }
      /*
      if (y_height == sea_level) {
        if (eli) {
          eli = false;
          scp.setColor(0.0, 0.50, 0.50, 1.0);
          //scp.putEllipsoid(x, sea_level, z, 3, 1, 6);
        }
      }*/
    }
  }  

  scp.setColor(0.1, 0.5, 1.0, 1.0); // Azul
  scp.putBox(0, 79, 0, sea_level, 0, 79);

  scp.writeOFF("land.off");  

  //validação dos métodos
  Sculptor validacao(80, 80, 80);

  validacao.setColor(0.1, 0.5, 1.0, 1.0);
  validacao.putEllipsoid(40, 60, 40, 9,6,6);
  validacao.putSphere(40, 45, 40, 4);

  validacao.putSphere(40, 35, 40, 4);
  validacao.cutSphere(40, 35, 40, 4);

  validacao.putEllipsoid(40, 25, 40, 9,6,6);
  validacao.cutEllipsoid(40, 25, 40, 9,6,6);

  validacao.putBox(35, 45, 5, 15,35,45);
  validacao.cutBox(35, 45, 5, 15,35,45);

  validacao.writeOFF("validacao.off"); 

}