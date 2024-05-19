#include "sculptor.h"

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>

Sculptor::Sculptor(int _nx, int _ny, int _nz) {
  nx = _nx;
  ny = _ny;
  nz = _nz;

  v = new Voxel **[nx];
  v[0] = new Voxel *[nx * ny];
  v[0][0] = new Voxel[nx * ny * nz];

  for (int i = 0; i < nx; i++) {
    v[i] = v[0] + ny * i;

    for (int j = 0; j < ny; j++) {
      v[i][j] = v[0][0] + nz * i * ny + nz * j;
    }
  }
}

Sculptor::~Sculptor() {
  delete[] v[0][0];
  delete[] v[0];
  delete v;
}

void Sculptor::setColor(float r, float g, float b, float a) {
  this->r = r;
  this->g = g;
  this->b = b;
  this->a = a;
}

void Sculptor::putVoxel(int x, int y, int z) {
  v[x][y][z].r = r;
  v[x][y][z].g = g;
  v[x][y][z].b = b;
  v[x][y][z].a = a;
  v[x][y][z].show = true;
}

void Sculptor::cutVoxel(int x, int y, int z) { this->v[x][y][z].show = false; }

void Sculptor::writeOFF(const char *filename) {
  // Simplificar Matriz
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        if (i != 0 && i != nx - 1 && j != 0 && j != ny - 1 && k != 0 && k != nz - 1) {

          if (v[i][j][k + 1].show == true && v[i][j + 1][k + 1].show == true &&
              v[i][j - 1][k + 1].show == true &&

              v[i + 1][j][k + 1].show == true &&
              v[i + 1][j + 1][k + 1].show == true &&
              v[i + 1][j - 1][k + 1].show == true &&

              v[i - 1][j][k + 1].show == true &&
              v[i - 1][j + 1][k + 1].show == true &&
              v[i - 1][j - 1][k + 1].show == true &&

              v[i][j][k].show == true && v[i][j + 1][k].show == true &&
              v[i][j - 1][k].show == true &&

              v[i + 1][j][k].show == true && v[i + 1][j + 1][k].show == true &&
              v[i + 1][j - 1][k].show == true &&

              v[i - 1][j][k].show == true && v[i - 1][j + 1][k].show == true &&
              v[i - 1][j - 1][k].show == true &&

              v[i][j][k - 1].show == true && v[i][j + 1][k - 1].show == true &&
              v[i][j - 1][k - 1].show == true &&

              v[i + 1][j][k - 1].show == true &&
              v[i + 1][j + 1][k - 1].show == true &&
              v[i + 1][j - 1][k - 1].show == true &&

              v[i - 1][j][k - 1].show == true &&
              v[i - 1][j + 1][k - 1].show == true &&
              v[i - 1][j - 1][k - 1].show == true) {

            v[i][j][k].a = 0;
          }
        }
      }
    }
  }


  for(int i = 0; i < nx; i++){
    for(int j = 0; j < ny; j++){
      for(int k = 0; k < nz; k++){
        if(v[i][j][k].a == 0){
          v[i][j][k].show = false;
        }
      }
    }
  }

  std::ofstream fout;
  fout.open(filename);
  fout << "OFF" << std::endl;
  int cont = 0;
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        if (v[i][j][k].show == true) {
          cont++;
        }
      }
    }
  }

  fout << cont * 8 << " " << cont * 6 << " " << 0 << std::endl;

  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        if (v[i][j][k].show == true) {
          fout << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl;
          fout << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl;
          fout << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl;
          fout << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl;
          fout << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl;
          fout << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl;
          fout << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl;
          fout << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl;
        }
      }
    }
  }

  fout << std::fixed << std::setprecision(2);

  int t = 0, index;
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      for (int k = 0; k < nz; k++) {
        if (v[i][j][k].show) {
          index = t * 8;
          fout << "4 " << index << " " << index + 3 << " " << index + 2 << " "
               << index + 1 << " ";
          fout << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b
               << " " << v[i][j][k].a << std::endl;
          fout << "4 " << index + 4 << " " << index + 5 << " " << index + 6
               << " " << index + 7 << " ";
          fout << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b
               << " " << v[i][j][k].a << std::endl;
          fout << "4 " << index << " " << index + 1 << " " << index + 5 << " "
               << index + 4 << " ";
          fout << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b
               << " " << v[i][j][k].a << std::endl;
          fout << "4 " << index << " " << index + 4 << " " << index + 7 << " "
               << index + 3 << " ";
          fout << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b
               << " " << v[i][j][k].a << std::endl;
          fout << "4 " << index + 3 << " " << index + 7 << " " << index + 6
               << " " << index + 2 << " ";
          fout << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b
               << " " << v[i][j][k].a << std::endl;
          fout << "4 " << index + 1 << " " << index + 2 << " " << index + 6
               << " " << index + 5 << " ";
          fout << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b
               << " " << v[i][j][k].a << std::endl;
          t++;
        }
      }
    }
  }
  fout.close();
}



void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1) {

  if (x0 < 0) {
    x0 = 0;
  }

  if (y0 < 0) {
    y0 = 0;
  }

  if (z0 < 0) {
    z0 = 0;
  }

  if (x0 > this->nx - 1) {
    x0 = this->nx - 1;
  }

  if (y0 > this->ny - 1) {
    y0 = this->ny - 1;
  }

  if (z0 > this->nz - 1) {
    z0 = this->nz - 1;
  }

  if (x1 < 0) {
    x1 = 0;
  }

  if (y1 < 0) {
    y1 = 0;
  }

  if (z1 < 0) {
    z1 = 0;
  }

  if (x1 > this->nx - 1) {
    x1 = this->nx - 1;
  }

  if (y1 > this->ny - 1) {
    y1 = this->ny - 1;
  }

  if (z1 > this->nz - 1) {
    z1 = this->nz - 1;
  }

  for (int i = x0; i <= x1; i++) {
    for (int j = y0; j <= y1; j++) {
      for (int k = z0; k <= z1; k++) {
        putVoxel(i, j, k);
      }
    }
  }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1) {
  if (x0 < 0) {
    x0 = 0;
  }

  if (y0 < 0) {
    y0 = 0;
  }

  if (z0 < 0) {
    z0 = 0;
  }

  if (x0 > this->nx - 1) {
    x0 = this->nx - 1;
  }

  if (y0 > this->ny - 1) {
    y0 = this->ny - 1;
  }

  if (z0 > this->nz - 1) {
    z0 = this->nz - 1;
  }

  if (x1 < 0) {
    x1 = 0;
  }

  if (y1 < 0) {
    y1 = 0;
  }

  if (z1 < 0) {
    z1 = 0;
  }

  if (x1 > this->nx - 1) {
    x1 = this->nx - 1;
  }

  if (y1 > this->ny - 1) {
    y1 = this->ny - 1;
  }

  if (z1 > this->nz - 1) {
    z1 = this->nz - 1;
  }

  for (int i = x0; i <= x1; i++) {
    for (int j = y0; j <= y1; j++) {
      for (int k = z0; k <= z1; k++) {
        cutVoxel(i, j, k);
      }
    }
  }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius) {
  if (xcenter < 0) {
    xcenter = 0;
  }

  if (ycenter < 0) {
    ycenter = 0;
  }

  if (zcenter < 0) {
    zcenter = 0;
  }

  if (xcenter > this->nx - 1) {
    xcenter = this->nx - 1;
  }

  if (ycenter > this->ny - 1) {
    ycenter = this->ny - 1;
  }

  if (zcenter > this->nz - 1) {
    zcenter = this->nz - 1;
  }

  for (int i = xcenter - radius; i < xcenter + radius; i++) {
    for (int j = ycenter - radius; j < ycenter + radius; j++) {
      for (int k = zcenter - radius; k < zcenter + radius; k++) {
        if (std::pow(i - xcenter, 2) + std::pow(j - ycenter, 2) +
                std::pow(k - zcenter, 2) <
            std::pow(radius, 2)) {
          putVoxel(i, j, k);
        }
      }
    }
  }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius) {
  if (xcenter < 0) {
    xcenter = 0;
  }

  if (ycenter < 0) {
    ycenter = 0;
  }

  if (zcenter < 0) {
    zcenter = 0;
  }

  if (xcenter > this->nx - 1) {
    xcenter = this->nx - 1;
  }

  if (ycenter > this->ny - 1) {
    ycenter = this->ny - 1;
  }

  if (zcenter > this->nz - 1) {
    zcenter = this->nz - 1;
  }

  for (int i = xcenter - radius; i < xcenter + radius; i++) {
    for (int j = ycenter - radius; j < ycenter + radius; j++) {
      for (int k = zcenter - radius; k < zcenter + radius; k++) {
        if (std::pow(i - xcenter, 2) + std::pow(j - ycenter, 2) +
                std::pow(k - zcenter, 2) <
            std::pow(radius, 2)) {
          cutVoxel(i, j, k);
        }
      }
    }
  }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx,
                            int ry, int rz) {
  if (xcenter < 0) {
    xcenter = 0;
  }

  if (ycenter < 0) {
    ycenter = 0;
  }

  if (zcenter < 0) {
    zcenter = 0;
  }

  if (xcenter > this->nx - 1) {
    xcenter = this->nx - 1;
  }

  if (ycenter > this->ny - 1) {
    ycenter = this->ny - 1;
  }

  if (zcenter > this->nz - 1) {
    zcenter = this->nz - 1;
  }

  for (int i = xcenter - rx; i < xcenter + rx; i++) {
    for (int j = ycenter - ry; j < ycenter + ry; j++) {
      for (int k = zcenter - rz; k < zcenter + rz; k++) {
        if (std::pow(i - xcenter, 2) / std::pow(rx, 2) +
                std::pow(j - ycenter, 2) / std::pow(ry, 2) +
                std::pow(k - zcenter, 2) / std::pow(rz, 2) <
            1) {
          putVoxel(i, j, k);
        }
      }
    }
  }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx,
                            int ry, int rz) {
  if (xcenter < 0) {
    xcenter = 0;
  }

  if (ycenter < 0) {
    ycenter = 0;
  }

  if (zcenter < 0) {
    zcenter = 0;
  }

  if (xcenter > this->nx - 1) {
    xcenter = this->nx - 1;
  }

  if (ycenter > this->ny - 1) {
    ycenter = this->ny - 1;
  }

  if (zcenter > this->nz - 1) {
    zcenter = this->nz - 1;
  }

  for (int i = xcenter - rx; i < xcenter + rx; i++) {
    for (int j = ycenter - ry; j < ycenter + ry; j++) {
      for (int k = zcenter - rz; k < zcenter + rz; k++) {
        if (std::pow(i - xcenter, 2) / std::pow(rx, 2) +
                std::pow(j - ycenter, 2) / std::pow(ry, 2) +
                std::pow(k - zcenter, 2) / std::pow(rz, 2) <
            1) {
          cutVoxel(i, j, k);
        }
      }
    }
  }
}