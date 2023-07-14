/*
  Name: Nick Avalani
  Course: CSC 352, Fall 2022, Benjamin Dicken
  Description: This program creates 2 figures using
  the 3d.h library. The first figure creates 2 faces
  adjacent to each other. The second figure develops
  a star using triangles
*/
#include <stdio.h>
#include <stdlib.h>
#include "3d.h"

int main(){
	Scene3D* star = Scene3D_create();
	char* directions[] = {"up", "down", "left", "right", "forward", "backward"};
	Coordinate3D origin = (Coordinate3D){100, 100, 100};
	for (int i = 0; i <= 5; i ++) {
		Scene3D_add_pyramid(star, origin, 20, 30, directions[i]);
	}
	for (int i = 0; i <= 5; i ++) {
                Scene3D_add_pyramid(star, origin, 20, 30, directions[i]);
        }
	Scene3D_write_stl_text(star, "star.stl");
	Scene3D_destroy(star);
	Scene3D* face = Scene3D_create();
	Coordinate3D coordinate;
	// Head
	coordinate = (Coordinate3D){25, 25, 25};
	Scene3D_add_cuboid(face, coordinate, 50, 50, 50);
	// Eye
	coordinate = (Coordinate3D){15, 40, 0};
	Scene3D_add_cuboid(face, coordinate, 10, 10, 10);
	// Eye
	coordinate = (Coordinate3D){35, 40, 0};
	Scene3D_add_cuboid(face, coordinate, 10, 10, 10);
	// Mouth
	coordinate = (Coordinate3D){25, 15, 0};
	Scene3D_add_cuboid(face, coordinate, 30, 7, 10);
	Scene3D_write_stl_text(face, "face.stl");
	Scene3D_destroy(face);
}
